#ifndef FALLINGPIECE_H
#define FALLINGPIECE_H

#include "piece.h"

#include <QWidget>

class fallingPiece : public piece
{
public:
    fallingPiece(QWidget *parent);
    void fall();
    bool toBeDeleted() {return toDelete;}
private:
    QPoint velocity;
    bool toDelete;
};

#endif // FALLINGPIECE_H
