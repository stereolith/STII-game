#ifndef LIVES_H
#define LIVES_H

#include <QWidget>
#include <vector>
#include "piece.h"

class lives : public QWidget //Bereich für (dynamisch) viele Leben/ Herzen
{
    Q_OBJECT
public:
    explicit lives(QWidget *parent = 0);
    int changeLives(int d); //Change no of lives by d
    void setLives(int l){noLives = l;}
    int getLives(){return noLives;}
    int getMaxLives(){return maxLives;}
private:
    int maxLives;
    int noLives;
    std::vector<piece*> livePieces;
protected:
    void paintEvent(QPaintEvent * event);
};

#endif // LIVES_H
