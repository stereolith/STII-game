#ifndef PIECE_H
#define PIECE_H

#include <QtGui>
#include <QWidget>

class piece : public QWidget
{
Q_OBJECT
public:
    piece(QWidget *parent = 0);
    piece(QWidget *parent, int x, int y, int width);
    piece(QWidget *parent, int x, int y, int w, QColor c);
    void moveBy(int dx, int dy);
    /*void setPos(int x, int y);
    int x(){return pos.x();}
    int y(){return pos.y();}
    void setX(int x){pos.setX(x);}
    void setY(int y){pos.setY(y);}*/

    void setWidth(int w){width = w;}
    void setShape(QPointF* s);
    void setColor(QColor c);
    int getWidth(){return width;}
    void setFilled(bool f){filled = f;}
    void setActive(bool a){active = a;}
    void paint();

    //test
    int posX;
    int posY;
private:
    QPointF *shape;

    QColor getColor();
    QColor activeColor;
    QColor inactiveColor;

    int width;
    int edges;
    bool filled;
    bool active;
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // PIECE_H
