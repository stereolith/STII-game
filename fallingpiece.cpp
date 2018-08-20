#include "fallingpiece.h"
#include <cstdlib> //rand


fallingPiece::fallingPiece(QWidget *parent, int t)
    : piece(parent)
{
    type = t;
    switch(type) //fallingPiece Type defines color, shape and velocity
    {
        case 0: setColor(Qt::red);
                velocity = QPoint(0,10);
                break;
        case 1: setColor(Qt::magenta);
                velocity = QPoint(0,15);
                break;
        case 2: setColor(Qt::cyan);
                velocity = QPoint(0,20);
                break;
    }
    show();
    toDelete = false;
}
fallingPiece::fallingPiece(QWidget *parent, int t, QPoint position) //Constructor to initialize with position (from deserialization)
    : piece(parent)
{
    type = t;
    switch(type)
    {
        case 0: setColor(Qt::red);
                velocity = QPoint(0,10);
                break;
        case 1: setColor(Qt::magenta);
                velocity = QPoint(0,15);
                break;
        case 2: setColor(Qt::cyan);
                velocity = QPoint(0,20);
                break;
    }
    toDelete = false;
    show();
    setActive(false);
    move(position);
}

void fallingPiece::fall()
{
    moveBy(velocity.x(), velocity.y());
    if(pos().y() > parentWidget()->height()) {
        toDelete = true;
    }
}
