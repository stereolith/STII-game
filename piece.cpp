#include "piece.h"

piece::piece()
{
    pos.setX(0);
    pos.setY(0);
    width = 10;
    setColor(QColor(207, 201, 255));
}
piece::piece(int x, int y, int w)
{
    pos.setX(x);
    pos.setY(y);
    width = w;
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
    activeColor = c;

    activeColor.toHsl();
    int lightness = activeColor.lightness() + 40;
    if(lightness > 240) lightness = 240;
    inactiveColor.setHsl(activeColor.hslHue(), activeColor.hslSaturation(), lightness, activeColor.alpha() );
    if(active) {
        color = &activeColor;
    }else{
        color = &inactiveColor;
    }
}

void piece::paint(QPainter* painter, QWidget *context)
{
    painter->begin( context );
    painter->fillRect ( pos.x(), pos.y(), width, width, *color );
    painter->end();
}
void piece::setActive(bool a)
{
    active = a;
    if(active) {
        color = &activeColor;
    }else{
        color = &inactiveColor;
    }
}

