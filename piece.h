#ifndef PIECE_H
#define PIECE_H

#include <QtGui>
#include <QWidget>

class piece
{
public:
    piece();
    piece(int x, int y, int width);
    void move(int dx, int dy);
    void setPos(int x, int y);
    int x(){return pos.x();}
    int y(){return pos.y();}
    void setX(int x){pos.setX(x);}
    void setY(int y){pos.setY(y);}

    void setWidth(int w){width = w;}
    void setColor(QColor c);
    int getWidth(){return width;}
    void setActive(bool a);
    void paint(QPainter* painter, QWidget* context);
private:
    QPoint pos;
    QColor *color;
    QColor activeColor;
    QColor inactiveColor;
    int width;
    int edges;
    bool active;
};

#endif // PIECE_H
