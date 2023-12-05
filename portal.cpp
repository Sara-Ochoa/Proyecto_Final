#include "portal.h"
#include <QPainter>
#include <QPixmap>
#include <random>


using namespace std;

int Portal::getPosx() const
{
    return posx;
}

void Portal::setPosx(int newPosx)
{
    posx = newPosx;
}

int Portal::getPosy() const
{
    return posy;
}

void Portal::setPosy(int newPosy)
{
    posy = newPosy;
}

int Portal::getRadio() const
{
    return radio;
}

void Portal::setRadio(int newRadio)
{
    radio = newRadio;
}

int Portal::getTipo() const
{
    return tipo;
}

void Portal::setTipo(int newTipo)
{
    tipo = newTipo;
}

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
