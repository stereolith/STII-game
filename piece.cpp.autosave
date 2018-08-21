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
    setRectShape();
    setColor(c);
    filled = true;
    fillPattern = Qt::SolidPattern;
}

void piece::moveBy(int dx, int dy) // offset move
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
void piece::setShape(QPolygon s) {
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

    painter.setRenderHint(QPainter::Antialiasing); //Enable antialising
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    if(filled) {
        QBrush brush(getColor(), fillPattern);
        painter.setBrush(brush);
        painter.drawPolygon(shape);
    } else {
        painter.drawPolygon(shape);
    }
    painter.end();
}
void piece::paint()
{
    update();
}

void piece::setRectShape()
{
    shape << QPoint(0, 0) << QPoint(width, 0) << QPoint(width, width) << QPoint(0, width);
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
