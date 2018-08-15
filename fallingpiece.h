#ifndef FALLINGPIECE_H
#define FALLINGPIECE_H

#include <QWidget>

class fallingPiece : public piece
{
public:
    fallingPiece();
    void fall();
private:
    QPoint velocity;
};

#endif // FALLINGPIECE_H
