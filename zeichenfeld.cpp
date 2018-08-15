#include <QtGui>
#include <iostream>
#include <QMessageBox>

#include <iostream>
#include "zeichenFeld.h"

zeichenFeld::zeichenFeld(QWidget *parent)
    : QWidget(parent)
{
    player.setPos(this->width()/2-10, 375);
    player.setWidth(10);
    setFocusPolicy(Qt::StrongFocus); //FocusPolicy to accept keyboard input
    setActive(false);
    active = false;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePieces()));
    timer->start(1000);
}

void zeichenFeld::updatePieces()
{
    player.move(12,0);
    update();
}

void zeichenFeld::paintEvent(QPaintEvent * )
{
    QPainter painter;
    player.paint(&painter, this);

}

void zeichenFeld::keyPressEvent(QKeyEvent *event)
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
void zeichenFeld::setActive(bool a)
{
    active = a;
    player.setActive(a);
    if(a) {
        setPalette(QPalette(QColor(211, 250, 200)));
        setAutoFillBackground(true);
    }else{
        setPalette(QPalette(QColor(241, 255, 237)));
        setAutoFillBackground(true);
    }
}
void zeichenFeld::serialize(QFile &file)
{
    QTextStream out(&file);

    out << "stII-savegame" << endl;
    out << "playerPos x " << player.x() << endl;
}

void zeichenFeld::deserialize(QFile &file)
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

