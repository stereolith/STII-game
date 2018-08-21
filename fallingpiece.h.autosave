#ifndef FALLINGPIECE_H
#define FALLINGPIECE_H

#include "piece.h"

#include <QWidget>

class fallingPiece : public piece
{
Q_OBJECT
public:
    fallingPiece(QWidget *parent, int t);
    fallingPiece(QWidget *parent, int t, QPoint position);
    void fall();
    bool toBeDeleted() {return toDelete;}
    int getType() {return type;}
private:
    QPoint velocity;
    QPoint altVelocity;
    bool alternateVelocity;
    int alternateRate;
    int alternateTimer = 0;
    bool toDelete;
    int type;
    QTimer *timer; //timer for alternating velocities
    void setFallingShape(int noShape);
private slots:
    void updateEvent();
};

#endif // FALLINGPIECE_H
