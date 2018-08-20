#include "piece.h"

piece::piece(QWidget *parent)
    : QWidget(parent)
{
    connect( parent, SIGNAL(signalActive(bool)), this, SLOT(setActive(bool)) );
    move(0,0);
    width = 30;
    setRectShape(); //set default rect shape
    filled = true;
    fillPattern = Qt::SolidPattern;
    setColor(QColor(207, 201, 255));
    //setActive(true);
}
piece::piece(QWidget *parent, int x, int y, int w)
    : QWidget(parent)
{
    connect( parent, SIGNAL(signalActive(bool)), this, SLOT(setActive(bool)) );
    move(x,y);
    width = w;
    setRectShape();
    filled = true;
    fillPattern = Qt::SolidPattern;
}
piece::piece(QWidget *parent, int x, int y, int w, QColor c)
    : QWidget(parent)
{
    connect( parent, SIGNAL(signalActive(bool)), this, SLOT(setActive(bool)) );
    move(x,y);
    width = w;
    shape = new QPointF[4];
    setRectShape();
    setColor(c);
    filled = true;
    fillPattern = Qt::SolidPattern;
}

void piece::moveBy(int dx, int dy)
{
    move(pos().x() + dx, pos().y() + dy);
}

void piece::setColor(QColor c)
{
    //Piece color in HSL, für Modifiktaion des saturation-Wertes für ausgegrautes pausiertes Spielfeld
    activeColor = c;
    activeColor.toHsl();
    inactiveColor.setHsl(activeColor.hslHue(), 20, activeColor.lightness(), activeColor.alpha() );
}
void piece::setShape(QPointF* s) {
    shape = s;
}
QColor piece::getColor()
{
    if(active) {
        return activeColor;
    } else {
        return inactiveColor;
    }
}

void piece::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin( this );

    QPen pen(getColor());
    pen.setWidth(3);
    painter.setPen(pen);
    if(filled) {
        QBrush brush(getColor(), fillPattern);
        painter.setBrush(brush);
        painter.drawPolygon(shape, 4);
    } else {
        painter.drawPolygon(shape, 4);
    }
    painter.end();
}
void piece::paint()
{
    update();
}

void piece::setRectShape()
{
    shape = new QPointF[4];
    shape[0] = QPointF(0, 0); //default shape: rectangle, width variable considered
    shape[1] = QPointF(width, 0);
    shape[2] = QPointF(width, width);
    shape[3] = QPointF(0, width);
}
void piece::setWidth(int w)
{
    width = w;
    setRectShape(); //update default rect shape
}
void piece::setActive(bool a)
{
    active = a;
}
