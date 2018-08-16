#include <QtGui>
#include <QString>
#include <QMessageBox>

#include <iostream>
#include "spielFeld.h"

spielFeld::spielFeld(QWidget *parent)
    : QWidget(parent)
{
    player.setPos(this->width()/2-10, 375);
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
        for(std::vector<fallingPiece>::iterator i=fallingPieces.begin(); i!=fallingPieces.end(); ++i){
            i->fall();
        }
        points += 20;
        update();
    }
}
void spielFeld::spawnFallingPiece()
{
    fallingPiece pc;
    pc.setActive(false);
    pc.setColor(Qt::red);
    fallingPieces.push_back(pc);
}

void spielFeld::paintEvent(QPaintEvent * )
{
    QPainter painter;
    painter.begin( this );
    player.paint(&painter);
    for(std::vector<fallingPiece>::iterator i=fallingPieces.begin(); i!=fallingPieces.end(); ++i){
        i->paint(&painter);
    }
    painter.end();
    pointsLabel->setText(QString::number(points) + " Punkte");
}

void spielFeld::keyPressEvent(QKeyEvent *event)
{
    if(active) {
        if(event->key() == Qt::Key_Right) {
            player.move(25, 0);
        } else if (event->key() == Qt::Key_Left) {
            player.move(-25, 0);
        }
        update();
    }
}
void spielFeld::setActive(bool a)
{
    active = a;
    player.setActive(a);
    for(std::vector<fallingPiece>::iterator i=fallingPieces.begin(); i!=fallingPieces.end(); ++i){
        i->setActive(a);
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
        player.setX(playerPosSting.toInt());
    }
    update();
}

