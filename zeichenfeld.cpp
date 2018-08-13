#include <QtGui>
#include <iostream>
#include <QMessageBox>

#include <iostream>
#include "zeichenFeld.h"

zeichenFeld::zeichenFeld(QWidget *parent)
    : QWidget(parent)
{
    posPlayer.setX(this->width()/2-10);
    posPlayer.setY(375);
    setFocusPolicy(Qt::StrongFocus); //FocusPolicy to accept keyboard input
    setActive(false);
    active = false;
}

void zeichenFeld::paintEvent(QPaintEvent * )
{
    QPainter painter;

    painter.begin( this );
    painter.fillRect ( posPlayer.x(), posPlayer.y(), 20, 20, playerColor );
    painter.end();
}

void zeichenFeld::keyPressEvent(QKeyEvent *event)
{
    if(active) {
        if(event->key() == Qt::Key_Right) {
            posPlayer.rx() += 25;
        } else if (event->key() == Qt::Key_Left) {
            posPlayer.rx() -= 25;
        }
        update();
    }
}
void zeichenFeld::setActive(bool a)
{
    active = a;
    if(a) {
        playerColor.setRgb(101, 81, 255);
        setPalette(QPalette(QColor(211, 250, 200)));
        setAutoFillBackground(true);
    }else{
        playerColor.setRgb(207, 201, 255);
        setPalette(QPalette(QColor(241, 255, 237)));
        setAutoFillBackground(true);
    }
}
void zeichenFeld::serialize(QFile &file)
{
    QTextStream out(&file);

    out << "PositionXFormat" << endl;
    out << "x " << posPlayer.x() << endl;
}

void zeichenFeld::deserialize(QFile &file)
{
    QTextStream in(&file);
    char c;
    QString header;

    in >> header;
    if (header != "PositionXFormat")
    {
        QMessageBox::warning(this, tr("Formatfehler"),
                             tr("Das ist keine PositionXFormat-Datei."),QMessageBox::Ok);
        return;
    }

    in >> c; //Zeilenumbruch

    in >> c; //Steuerzeichen (x) einlesen

    if (c!='x')
    {
        QMessageBox::warning(this, tr("Objektfehler"),
                             tr("Unbekanntes Steuerzeichen"),QMessageBox::Ok);
        return;
    }
    int x;
    in >> x;
    posPlayer.setX(x);

    update();
}

