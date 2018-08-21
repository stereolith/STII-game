#include "fallingpiece.h"
#include <cstdlib> //rand

fallingPiece::fallingPiece(QWidget *parent, int t)
    : piece(parent)
{
    type = t;
    switch(type) //fallingPiece Type defines color, shape and velocity
    {
        case 0: setColor("#F92672"); //red square
                velocity = QPoint(0,5);
                break;
        case 1: setColor("#66D9EF"); //blue triangle
                velocity = QPoint(0,10);
                setFallingShape(1);
                break;
        case 2: setColor("#FD971F"); //orange octagon
                velocity = QPoint(0,15);
                setFallingShape(2);
                break;
        case 3: setColor(Qt::red); //red health power up
                velocity = QPoint(0, 6);
                setFallingShape(3);
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
                setFallingShape(1);
                break;
        case 2: setColor(Qt::cyan);
                velocity = QPoint(0,20);
                setFallingShape(2);
                break;
        case 3: setColor(Qt::red); //red health power up
                velocity = QPoint(0, 6);
                setFallingShape(3);
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

void fallingPiece::setFallingShape(int shapeNo)
{
    QPolygon shape;
    switch(shapeNo)
    {
        case 1: //triangle
                shape << QPoint(0, 0)
                      << QPoint(getWidth(), 0)
                      << QPoint(getWidth()/2, getWidth());
                setShape(shape);
                break;
        case 2: //octagon
                shape << QPoint(getWidth()/3, 0)
                      << QPoint(getWidth()*.66, 0)
                      << QPoint(getWidth(), getWidth()/3)
                      << QPoint(getWidth(), getWidth()*.66)
                      << QPoint(getWidth()*.66, getWidth())
                      << QPoint(getWidth()/3, getWidth())
                      << QPoint(0, getWidth()*.66)
                      << QPoint(0, getWidth()/3);
                setShape(shape);
                break;
        case 3: //power-up cross
                shape << QPoint(getWidth()*.4, 0)
                      << QPoint(getWidth()*.6, 0)
                      << QPoint(getWidth()*.6, getWidth()*.4)
                      << QPoint(getWidth(), getWidth()*.4)
                      << QPoint(getWidth(), getWidth()*.6)
                      << QPoint(getWidth()*.6, getWidth()*.6)
                      << QPoint(getWidth()*.6, getWidth())
                      << QPoint(getWidth()*.4, getWidth())
                      << QPoint(getWidth()*.4, getWidth()*.6)
                      << QPoint(0, getWidth()*.6)
                      << QPoint(0, getWidth()*.4)
                      << QPoint(getWidth()*.4, getWidth()*.4);
                setShape(shape);
    }
}
