#include <QtGui>
#include <QString>
#include <QMessageBox>
#include <cstdlib> //rand

#include <iostream>
#include "spielFeld.h"

int spawnTimer = 0;
int hitTimer = 0;
int invincibleTimer = 0;
const int hitTimeout = 10;
bool hit = false;
bool invincible = false;
int invincibleTimeout = 10;

spielFeld::spielFeld(QWidget *parent)
    : QWidget(parent)
{
    player = new piece(this, this->width()/2-10, 375, 30, Qt::blue);
    player->setFillPattern(Qt::BDiagPattern);
    setFocusPolicy(Qt::StrongFocus); //FocusPolicy to accept keyboard input

    setActive(false);

    points = 0;
    playerLives = new lives(this);

    timeToSpawn = 10;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateEvent()));
    timer->start(100);
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
        for(int i=0; i<fallingPieces.size(); i++){
            fallingPieces[i]->fall();
            //Collision detection
            int collidingDistance = player->getWidth() / 2 + fallingPieces[i]->getWidth() / 2;
            if(fallingPieces[i]->getCenter().y() > (player->getCenter().y() - collidingDistance) &&
               fallingPieces[i]->getCenter().y() < (player->getCenter().y() + collidingDistance) &&
               fallingPieces[i]->getCenter().x() > (player->getCenter().x() - collidingDistance) &&
               fallingPieces[i]->getCenter().x() < (player->getCenter().x() + collidingDistance))
            {
                if(!invincible) {
                    hit = true;
                    setActive(false);
                    playerLives->changeLives(-1);
                }
            }
        }
        points += 20;
        update();
        spawnTimer += 1;

        if(invincible) {
            invincibleTimer++;
            if(invincibleTimer >= invincibleTimeout) {
                invincibleTimer = 0;
                invincible = false;
            }
        }

        pointsLabel->setText(QString::number(points) + " Punkte");

    } else if (hit) {
        hitTimer++;
        if(hitTimer >= hitTimeout) {
            invincible = true;
            setActive(true);
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
    std::vector<int> weights {5, 3, 1}; //weights for piece types 0, 1 and 2
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
    fallingPieces.back()->move(rand()%(width()-50), 10);
    //fallingPieces.back()->setActive(active);
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
        } else if (event->key() == Qt::Key_Left) {
            player->moveBy(-25, 0);
        }
        update();
    }
}
void spielFeld::setActive(bool a)
{
    active = a;
    emit signalActive(a); //Fire signalActive signal to "setActive"-Slot in all piece-Objects

    if(a) {
        setPalette(QPalette(QColor(211, 250, 200)));
        setAutoFillBackground(true);
    }else{
        setPalette(QPalette(QColor(241, 255, 237)));
        setAutoFillBackground(true);
    }
}
void spielFeld::serialize(QFile &file)
{
    QTextStream out(&file);

    out << "stII-savegame" << endl;
    out << "playerPos x " << player->x() << endl;
    out << "noLives " << playerLives->getLives() << endl;
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
                             " (Unbekanntes Steuerzeichen für noLives", QMessageBox::Ok);
        return;
    } else {
        playerLivesString.remove("noLives ");
        playerLives->setLives(playerLivesString.toInt());
    }

    //Read fallingPieces
    for(int i=0; i<fallingPieces.size(); i++)
    {
        fallingPieces[i]->hide(); //Hide all fallingPieces
    }
    fallingPieces.clear(); //Flush vector
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

