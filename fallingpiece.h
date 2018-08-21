#ifndef FALLINGPIECE_H
#define FALLINGPIECE_H

#include "piece.h"

#include <QWidget>

class fallingPiece : public piece
{
public:
    fallingPiece(QWidget *parent, int t);
    fallingPiece(QWidget *parent, int t, QPoint position);
    void fall();
    bool toBeDeleted() {return toDelete;}
    int getType() {return type;}
private:
    QPoint velocity;
    bool toDelete;
    int type;
    void setFallingShape(int noShape);
};

#endif // FALLINGPIECE_H
