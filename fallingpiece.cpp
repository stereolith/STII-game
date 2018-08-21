#include "fallingpiece.h"
#include <cstdlib> //rand

int alternateTimer = 0;

fallingPiece::fallingPiece(QWidget *parent, int t)
    : piece(parent)
{
    type = t;
    alternateVelocity = false; //default
    switch(type) //type defines color, shape and (alternating) velocity
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
    case 3: setColor(Qt::cyan); //cyan spike
            alternateVelocity = true;
            alternateRate = 8;
            velocity = QPoint(4, 7);
            altVelocity = QPoint(-4, 7);
            setFallingShape(3);
            break;
    case 4: setColor("#A6E22E"); //green hourglass
            alternateVelocity = true;
            alternateRate = 4;
            velocity = QPoint(6, 2);
            altVelocity = QPoint(-6, 2);
            setFallingShape(4);
            break;
    case 5: setColor(Qt::red); //red health power up
            velocity = QPoint(0, 6);
            setFallingShape(5);
            break;
    }
    show();
    toDelete = false;
    timer = new QTimer(this); //start timer for alternating velocity interval
    connect(timer, SIGNAL(timeout()), this, SLOT(updateEvent()));
    timer->start(100);
}
fallingPiece::fallingPiece(QWidget *parent, int t, QPoint position) //Constructor to initialize with position (from deserialization)
    : piece(parent)
{
    type = t;
    alternateVelocity = false; //default
    switch(type)
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
    case 3: setColor(Qt::cyan); //cyan spike
            alternateVelocity = true;
            alternateRate = 8;
            velocity = QPoint(4, 7);
            altVelocity = QPoint(-4, 7);
            setFallingShape(3);
            break;
    case 4: setColor("#A6E22E"); //green hourglass
            alternateVelocity = true;
            alternateRate = 4;
            velocity = QPoint(6, 2);
            altVelocity = QPoint(-6, 2);
            setFallingShape(4);
            break;
    case 5: setColor(Qt::red); //red health power up
            velocity = QPoint(0, 6);
            setFallingShape(5);
            break;
    }
    toDelete = false;
    show();
    setActive(false);
    move(position);
    timer = new QTimer(this); //start timer for alternating velocity interval
    connect(timer, SIGNAL(timeout()), this, SLOT(updateEvent()));
    timer->start(100);
    srand(time(0));
}

void fallingPiece::fall() //Move according to velocity
{
    moveBy(velocity.x(), velocity.y());
    if(pos().y() > parentWidget()->height()) {
        toDelete = true;
    }
}
void fallingPiece::updateEvent() //timed interval event for alternating velocities
{
    if(alternateVelocity)
    {
        alternateTimer++;
        if(alternateTimer >= alternateRate) {
            QPoint inter = altVelocity; //Switch alt/ velocity values, so alternative velocity val is used as velocity in fall()
            altVelocity = velocity;
            velocity = inter;
            alternateTimer = 0;
        }
    }
}
void fallingPiece::setFallingShape(int shapeNo) //shape polygons
{
    QPolygon shape;
    int width = getWidth();
    switch(shapeNo)
    {
        case 1: //triangle
                shape << QPoint(0, 0)
                      << QPoint(width, 0)
                      << QPoint(width/2, width);
                break;
        case 2: //octagon
                shape << QPoint(width/3, 0)
                      << QPoint(width*.66, 0)
                      << QPoint(width, width/3)
                      << QPoint(width, width*.66)
                      << QPoint(width*.66, width)
                      << QPoint(width/3, width)
                      << QPoint(0, width*.66)
                      << QPoint(0, width/3);
                break;
        case 3: //spike
                shape << QPoint(0, 0)
                      << QPoint(width*.5, width*.6)
                      << QPoint(width, 0)
                      << QPoint(width*.5, width);
                break;

        case 4: //small rectangle
                shape << QPoint(0,0)
                      << QPoint(width, 0)
                      << QPoint(width*.6, width*.5)
                      << QPoint(width, width)
                      << QPoint(0, width)
                      << QPoint(width*.4, width*.5);
                break;
        case 5: //power-up cross
                shape << QPoint(width*.4, 0)
                      << QPoint(width*.6, 0)
                      << QPoint(width*.6, width*.4)
                      << QPoint(width, width*.4)
                      << QPoint(width, width*.6)
                      << QPoint(width*.6, width*.6)
                      << QPoint(width*.6, width)
                      << QPoint(width*.4, width)
                      << QPoint(width*.4, width*.6)
                      << QPoint(0, width*.6)
                      << QPoint(0, width*.4)
                      << QPoint(width*.4, width*.4);
                break;
    }
    setShape(shape);
}
