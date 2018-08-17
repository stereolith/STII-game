#include "fallingpiece.h"

fallingPiece::fallingPiece(QWidget *parent)
    : piece(parent)
{
    velocity = QPoint(0,-10);
    move(200, 20);
}

void fallingPiece::fall()
{
    moveBy(velocity.x(), velocity.y());
}
