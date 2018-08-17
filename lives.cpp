#include "lives.h"

lives::lives(QWidget *parent) : QWidget(parent)
{
    maxLives = 3;
    noLives = 3;
    int width = 30;
    int offsetX = 0;
    for(int i=0; i < maxLives; i++){
        livePieces.push_back(new piece(this, offsetX, 0, width, Qt::red));
        offsetX += width;
        offsetX += 10;
    }
    this->move(500,10);
}

void lives::paintEvent(QPaintEvent * )
{
    QPainter painter;
    painter.begin( this );
    for(int i=0; i < maxLives;i++){
        if(i < noLives) {
            livePieces[i]->setFilled(true);
        } else {
            livePieces[i]->setFilled(false);
        }
        livePieces[i]->paint();
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
