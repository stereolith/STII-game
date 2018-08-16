#include "fallingpiece.h"

fallingPiece::fallingPiece()
{
    velocity = QPoint(0,-10);
    setPos(200, 20);
}

void fallingPiece::fall()
{
    move(velocity.x(), velocity.y());
}
