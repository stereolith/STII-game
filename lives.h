#ifndef LIVES_H
#define LIVES_H

#include <QWidget>
#include <vector>
#include "piece.h"

class lives : public QWidget
{
    Q_OBJECT
public:
    explicit lives(QWidget *parent = 0);
    int changeLives(int d); //Change no of lives by d
    void show();
private:
    int maxLives;
    int noLives;
    std::vector<piece*> livePieces;
protected:
    void paintEvent(QPaintEvent * event);
};

#endif // LIVES_H
