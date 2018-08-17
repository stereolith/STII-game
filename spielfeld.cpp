#include <QtGui>
#include <QString>
#include <QMessageBox>

#include <iostream>
#include "spielFeld.h"

spielFeld::spielFeld(QWidget *parent)
    : QWidget(parent)
{
    player.setParent(this);
    player.move(this->width()/2-10, 375);
    player.setWidth(10);
    setFocusPolicy(Qt::StrongFocus); //FocusPolicy to accept keyboard input
    setActive(false);

    points = 0;
    playerLives = new lives(this);

    spawnFallingPiece();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateEvent()));
    timer->start(1000);
}

void spielFeld::updateEvent()
{
    if(active)
    {
        for(int i=0; i<fallingPieces.size(); i++){
            fallingPieces[i]->fall();
        }
        points += 20;
        update();
    }
}
void spielFeld::spawnFallingPiece()
{
    fallingPieces.push_back(new fallingPiece(this));
    fallingPieces.back()->setColor(Qt::red);
    fallingPieces.back()->setActive(false);
}

void spielFeld::paintEvent(QPaintEvent * )
{
    pointsLabel->setText(QString::number(points) + " Punkte");
    for(int i=0; i<fallingPieces.size(); i++){
        fallingPieces[i]->paint();
    }
    player.paint();
}

void spielFeld::keyPressEvent(QKeyEvent *event)
{
    if(active) {
        if(event->key() == Qt::Key_Right) {
            player.moveBy(25, 0);
        } else if (event->key() == Qt::Key_Left) {
            player.moveBy(-25, 0);
        }
        update();
    }
}
void spielFeld::setActive(bool a)
{
    active = a;
    player.setActive(a);
    for(int i=0; i<fallingPieces.size(); i++){
        fallingPieces[i]->setActive(a);
    }
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
    out << "playerPos x " << player.x() << endl;
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

    QString playerPosSting = in.readLine();

    if (!playerPosSting.contains("playerPos x "))
    {
        QMessageBox::warning(this, tr("Objektfehler"),
                             tr("Unbekanntes Steuerzeichen"),QMessageBox::Ok);
        return;
    } else {
        playerPosSting.remove("playerPos x ");
        //player.setX(playerPosSting.toInt());
    }
    update();
}

