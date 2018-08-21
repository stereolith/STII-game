#include "lives.h"
#include <QDebug>

lives::lives(QWidget *parent) : QWidget(parent)
{
    maxLives = 3;
    noLives = 3;
    int width = 30;
    int offsetX = 0;
    QPolygon shp;
    shp << QPoint(width/2, 0) << QPoint(width, width/2) << QPoint(width/2, width) << QPoint(0, width/2);

    for(int i=0; i < maxLives; i++){
        livePieces.push_back(new piece(this, offsetX, 0, width, Qt::red));
        livePieces.back()->setShape(shp);
        offsetX += width;
        offsetX += 10;
    }
    this->move(500,10);
}


void lives::paintEvent(QPaintEvent * event)
{
    QPainter painter;
    painter.begin( this );
    for(int i=0; i < maxLives;i++){
        if(i < noLives) {
            livePieces[i]->setFilled(true);
        } else {
            livePieces[i]->setFilled(false);
        }
    }
    painter.end();
}

int lives::changeLives(int d)
{
    noLives += d;
    if(noLives > maxLives) noLives = maxLives;
    if(noLives <= 0) return -1;
    return noLives;
}
