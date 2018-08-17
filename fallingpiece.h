#ifndef FALLINGPIECE_H
#define FALLINGPIECE_H

#include "piece.h"

#include <QWidget>

class fallingPiece : public piece
{
public:
    fallingPiece(QWidget *parent);
    void fall();
private:
    QPoint velocity;
};

#endif // FALLINGPIECE_H
