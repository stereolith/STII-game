#include <QtGui>
#include <QString>
#include <QMessageBox>
#include <cstdlib> //rand

#include <iostream>
#include "spielFeld.h"

int spawnTimer = 0;
int hitTimer = 0;
int invincibleTimer = 0;
int gameOverTimer = 0;

spielFeld::spielFeld(QWidget *parent)
    : QWidget(parent)
{
    player = new piece(this, this->width()/2-10, 375, 30, "#66D9EF");
    player->setFillPattern(Qt::BDiagPattern);
    setFocusPolicy(Qt::StrongFocus); //FocusPolicy to accept keyboard input

    setActive(false);

    points = 0;
    playerLives = new lives(this);

    playerHit = false;
    invincible = false;
    gameIsOver = false;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateEvent()));
    timer->start(30);
    srand(time(0));
}

void spielFeld::updateEvent()
{
    if(active)
    {
        if(spawnTimer >= timeToSpawn) {
            spawnFallingPiece();
            spawnTimer = 0;
        }
        //Change player filling when not on max health/ lives, and when on last live
        if(playerLives->getLives() == playerLives->getMaxLives()) {
            player->setFillPattern(Qt::BDiagPattern);
            player->setFilled(true);
        } else if (playerLives->getLives() == 1){
            player->setFilled(false);
        } else {
            player->setFilled(true);
            player->setFillPattern(Qt::Dense7Pattern);
        }
        for(int i=0; i<fallingPieces.size(); i++){
            fallingPieces[i]->fall();
            //Collision detection for each fallingPiece
            int collidingDistance = player->getWidth() / 2 + fallingPieces[i]->getWidth() / 2;
            if(fallingPieces[i]->getCenter().y() > (player->getCenter().y() - collidingDistance) &&
               fallingPieces[i]->getCenter().y() < (player->getCenter().y() + collidingDistance) &&
               fallingPieces[i]->getCenter().x() > (player->getCenter().x() - collidingDistance) &&
               fallingPieces[i]->getCenter().x() < (player->getCenter().x() + collidingDistance))
            {
                if(!invincible) {
                    playerHit = true; //activate timeout an any collision
                    setActive(false);
                    if(fallingPieces[i]->getType() == 5) { //Check if fallingPiece is health power-up
                        playerLives->changeLives(1); //Add a Life
                    } else {
                        if(playerLives->changeLives(-1) == -1) {
                            //Game Over
                            gameOver();
                        };
                    }
                }
            }
        }
        points += 1;
        update();
        spawnTimer += 1;

        if(invincible) {
            invincibleTimer++;
            if(invincibleTimer >= invincibleTimeout) {
                invincibleTimer = 0;
                invincible = false;
                player->setActive(true);
            }
        }

        pointsLabel->setText(QString::number(points) + " Punkte");

    } else if (gameIsOver) { //Game Over screen
        gameOverTimer++;
        if(gameOverTimer >= gameOverTimeout) {
            //remove game over screen text
            delete gameOverLabel;
            delete gameOverPointsLabel;
            gameOverTimer = 0;
            gameIsOver = false;
            setActive(true);
        }
    } else if (playerHit) { //Player hit: timeout
        hitTimer++;
        if(hitTimer >= hitTimeout) {
            playerHit = false;
            invincible = true;
            setActive(true);
            player->setActive(false); //Leve player grey for the duration of invincibility
            hitTimer = 0;
        }
    }
}
void spielFeld::spawnFallingPiece()
{
    for(int i=0; i<fallingPieces.size(); i++) //check if any fallingPieces need to be deleted
    {
        if(fallingPieces[i]->toBeDeleted()) fallingPieces.erase(fallingPieces.begin()+i);
    }

    //Weighted random choice of fallingPieces-Types (see https://stackoverflow.com/a/1761646)
    std::vector<int> weights {5, 4, 3, 3, 2, 2}; //weights for piece types 0, 1, 2, 3, 4 and 5(health power-up)
    int sumOfWeights = 0;
    for(int i=0; i<weights.size(); i++)
    {
        sumOfWeights += weights[i];
    }
    int randomNo = rand() % sumOfWeights;
    int randomWeighted;
    for(int i=0; i<weights.size(); i++)
    {
        if(randomNo < weights[i])
        {
            randomWeighted = i;
            break;
        }
        randomNo -= weights[i];
    }

    fallingPieces.push_back(new fallingPiece(this, randomWeighted));
    fallingPieces.back()->move(rand()%(width()-50), -30);
    fallingPieces.back()->show();
}

void spielFeld::paintEvent(QPaintEvent * )
{
}

void spielFeld::keyPressEvent(QKeyEvent *event)
{
    if(active) {
        if(event->key() == Qt::Key_Right) {
            player->moveBy(25, 0);
            if(player->pos().x() > width() - 30) player->move(width() -30, player->pos().y());
        } else if (event->key() == Qt::Key_Left) {
            player->moveBy(-25, 0);
            if(player->pos().x() < 10) player->move(0, player->pos().y());
        }
        update();
    }
}
void spielFeld::setActive(bool a)
{
    active = a;
    emit signalActive(a); //Fire signalActive signal to "setActive"-Slot in all piece-Objects

    if(a) {
        setPalette(QPalette(QColor("#272822")));
        setAutoFillBackground(true);
    }else{
        setPalette(QPalette(QColor("#6f706c")));
        setAutoFillBackground(true);
    }
}
void spielFeld::serialize(QFile &file)
{
    QTextStream out(&file);

    out << "stII-savegame" << endl;
    out << "playerPos x " << player->x() << endl;
    out << "noLives " << playerLives->getLives() << endl;
    out << "points " << points << endl;
    for(int i=0; i<fallingPieces.size(); i++)
    {
        out << "fallingPiece: x " << fallingPieces[i]->pos().x()
            << " y " << fallingPieces[i]->pos().y()
            << " pieceType " << fallingPieces[i]->getType() <<endl;
    }
}

void spielFeld::deserialize(QFile &file)
{
    QTextStream in(&file);
    char c;
    QString header;

    in >> header;
    if (header != "stII-savegame")
    {
        QMessageBox::warning(this, tr("Formatfehler"),
                             tr("Das ist kein stII-savegame."),QMessageBox::Ok);
        return;
    }

    in >> c; //Zeilenumbruch

    // Read player position
    QString playerPosSting = in.readLine();
    if (!playerPosSting.contains("playerPos x "))
    {
        QMessageBox::warning(this, tr("Objektfehler"),
                             tr("Unbekanntes Steuerzeichen für PlayerPos"), QMessageBox::Ok);
        return;
    } else {
        playerPosSting.remove("playerPos x ");
        player->move(playerPosSting.toInt(), player->pos().y());
    }

    //Read no of player lives
    QString playerLivesString = in.readLine();
    if (!playerLivesString.contains("noLives "))
    {
        QMessageBox::warning(this, tr("Objektfehler"),
                             "Unbekanntes Steuerzeichen für noLives", QMessageBox::Ok);
        return;
    } else {
        playerLivesString.remove("noLives ");
        playerLives->setLives(playerLivesString.toInt());
    }

    //Read points
    QString pointsString = in.readLine();
    if (!pointsString.contains("points "))
    {
        QMessageBox::warning(this, tr("Objektfehler"),
                             "Unbekanntes Steuerzeichen für points", QMessageBox::Ok);
        return;
    } else {
        pointsString.remove("points ");
        points = pointsString.toInt();
    }

    //Read fallingPieces
    deleteFallingPieces();
    while(true)
    {
        QString fallingPieceString = in.readLine();
        if(!fallingPieceString.contains("fallingPiece: x "))
        {
            //kein fallingPiece (optional)
            return;
        }
        //Get number-value substrings
        fallingPieceString.remove("fallingPiece: x ");
        QStringRef xVal(&fallingPieceString, 0, fallingPieceString.indexOf(" "));
        int beginOfYVal = fallingPieceString.indexOf("y") + 2;
        qDebug() << fallingPieceString.indexOf(" ", beginOfYVal);
        QStringRef yVal(&fallingPieceString, beginOfYVal, fallingPieceString.indexOf(" ", beginOfYVal) - beginOfYVal); //get y-SubString
        int beginOfTypeVal = fallingPieceString.indexOf("pieceType") + 10;
        QStringRef typeVal(&fallingPieceString, beginOfTypeVal, 1);//get type-SubString (1 digit long)

        qDebug() << fallingPieceString << "parsedX: " << xVal << " parsedY: " << yVal << " parsedType: " << typeVal;
        //Add found fallingPiece to vector
        fallingPieces.push_back(new fallingPiece(this, typeVal.toInt(), QPoint(xVal.toInt(), yVal.toInt())));
        //
        qDebug() << fallingPieces.back()->isVisible();
    }

    update();
}
void spielFeld::gameOver()
{
    gameIsOver = true;
    playerHit = false;

    gameOverLabel = new QLabel("Game Over!");
    gameOverLabel->setFont(QFont("TypeWriter", 20));
    gameOverLabel->setParent(this);
    gameOverLabel->move(width()/2 - 80, 120);
    gameOverLabel->show();

    gameOverPointsLabel = new QLabel(QString("Punkte: ").append(QString::number(points)));
    gameOverPointsLabel->setFont(QFont("TypeWriter", 18));
    gameOverPointsLabel->setParent(this);
    gameOverPointsLabel->move(width()/2 - 70, 170);
    gameOverPointsLabel->show();

    //Reset game
    deleteFallingPieces();
    points = 0;
    playerLives->setLives(3);
}
void spielFeld::deleteFallingPieces()
{
    for(int i=0; i<fallingPieces.size(); i++)
    {
        delete fallingPieces[i];
    }
    fallingPieces.clear(); //Flush vector
}

