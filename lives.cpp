#include "lives.h"

lives::lives(QWidget *parent) : QWidget(parent)
{
    maxLives = 3;
    noLives = 1;
    int width = 20;
    int offsetX = 0;
    for(int i=0; i < maxLives; i++){
        piece p(offsetX, 0, width, Qt::red);
        livePieces.push_back(p);
        offsetX += width;
        offsetX += 10;
    }
    this->move(530,10);
}

void lives::paintEvent(QPaintEvent * )
{
    QPainter painter;
    painter.begin( this );
    for(int i=0; i < maxLives;i++){//maxLives = 3    noLives = 1
        if(i < noLives) {
            livePieces[i].setFilled(true);
        } else {
            livePieces[i].setFilled(false);
        }
        livePieces[i].paint(&painter);
    }
    painter.end();
}

int lives::changeLives(int d)
{
    noLives += d;
    update();
    if(noLives <= 0) return -1;
    return noLives;
}
