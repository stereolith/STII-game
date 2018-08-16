#ifndef PIECE_H
#define PIECE_H

#include <QtGui>
#include <QWidget>

class piece
{
public:
    piece();
    piece(int x, int y, int width);
    piece(int x, int y, int w, QColor c);
    void move(int dx, int dy);
    void setPos(int x, int y);
    int x(){return pos.x();}
    int y(){return pos.y();}
    void setX(int x){pos.setX(x);}
    void setY(int y){pos.setY(y);}

    void setWidth(int w){width = w;}
    void setColor(QColor c);
    int getWidth(){return width;}
    void setFilled(bool f){filled = f;}
    void setActive(bool a){active = a;}
    void paint(QPainter* painter);
private:
    QPoint pos;

    QColor activeColor;
    QColor inactiveColor;
    QColor getColor();

    int width;
    int edges;
    bool filled;
    bool active;
};

#endif // PIECE_H
