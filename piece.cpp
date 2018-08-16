#include "piece.h"

piece::piece()
{
    pos.setX(0);
    pos.setY(0);
    width = 10;
    filled = true;
    setColor(QColor(207, 201, 255));
    setActive(true);
}
piece::piece(int x, int y, int w)
{
    pos.setX(x);
    pos.setY(y);
    width = w;
    filled = true;
}
piece::piece(int x, int y, int w, QColor c)
{
    pos.setX(x);
    pos.setY(y);
    width = w;
    setColor(c);
    filled = true;
}

void piece::move(int dx, int dy)
{
    pos.rx() += dx;
    pos.ry() -= dy;
}
void piece::setPos(int x, int y)
{
    pos.setX(x);
    pos.setY(y);
}
void piece::setColor(QColor c)
{
    //Piece color in HSL, für Modifiktaion des saturation-Wertes für ausgegrautes pausiertes Spielfeld
    activeColor = c;
    activeColor.toHsl();
    inactiveColor.setHsl(activeColor.hslHue(), 20, activeColor.lightness(), activeColor.alpha() );
}
QColor piece::getColor()
{
    if(active) {
        return activeColor;
    } else {
        return inactiveColor;
    }
}

void piece::paint(QPainter* painter)
{
    if(filled) {
        painter->fillRect ( pos.x(), pos.y(), width, width, getColor() );
    } else {
        painter->setPen(getColor());
        painter->drawRect ( pos.x(), pos.y(), width, width );
    }
}

