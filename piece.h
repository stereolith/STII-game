#ifndef PIECE_H
#define PIECE_H

#include <QtGui>
#include <QWidget>

// Grundbaustein/ Superklasse für alle Elemente auf dem Spielfeld: player, lives, fallingPieces
// Definiert Farbe, Füllmuster, Form und implementiert entsprechend ein PaintEvent
// Eine inactiveColor-Version der Farbe, fpr

class piece : public QWidget {
Q_OBJECT
public:
    piece(QWidget *parent = 0);
    piece(QWidget *parent, int x, int y, int width);
    piece(QWidget *parent, int x, int y, int w, QColor c);
    void moveBy(int dx, int dy);

    void setWidth(int w);
    void setShape(QPolygon s);
    void setColor(QColor c);
    int getWidth(){return width;}
    QPointF getCenter(){return QPointF(pos().x()+(width/2), pos().y()+(width/2));}
    void setFilled(bool f){filled = f;}
    void setFillPattern(Qt::BrushStyle f){fillPattern = f;}
    void paint();
public slots:
    void setActive(bool a);

private:
    QPolygon shape;

    void setRectShape();
    QColor getColor();
    QColor activeColor;
    QColor inactiveColor;

    int width;
    int edges;
    bool filled;
    Qt::BrushStyle fillPattern;
    bool active;
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // PIECE_H
