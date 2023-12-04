#include "portal.h"
#include <QPainter>
#include <QPixmap>
#include <random>


using namespace std;

Portal::Portal(int x, int y,  int r, int t)
{
    posx=x;
    posy=y;
    radio=r;
    tipo = t;
    setPos(posx,posy);
}

QRectF Portal::boundingRect() const
{
    return QRect(-radio, -radio, 2*radio,2*radio);
}

void Portal::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(tipo == 1)
    {
        QPixmap pixmap(":/Imagenes/portal.png");
        painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
    }
    else if(tipo == 2)
    {
        QPixmap pixmap(":/Imagenes/portal4.png");
        painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
    }
}
