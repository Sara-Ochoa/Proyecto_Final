#include "portal.h"
#include <QPainter>
#include <QPixmap>

Portal::Portal(int x, int y, int r)
{
    posx=x;
    posy=y;
    radio=r;
    setPos(posx,posy);
}

QRectF Portal::boundingRect() const
{
    return QRect(-radio, -radio, 2*radio,2*radio);
}

void Portal::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap(":/Imagenes/portal.png");
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
}
