#include "fallingpiece.h"
#include <cstdlib> //rand


fallingPiece::fallingPiece(QWidget *parent)
    : piece(parent)
{
    velocity = QPoint(0,10);
    toDelete = false;
}

void fallingPiece::fall()
{
    moveBy(velocity.x(), velocity.y());
    if(pos().y() > parentWidget()->height()) {
        toDelete = true;
    }
}
