#include "portal.h"
#include <QPainter>
#include <QPixmap>
#include <random>


using namespace std;

Portal::Portal(int x, int y,  int r)
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

/*
#include <random>
    mt19937 generador(random_device{}());
    uniform_int_distribution<int> distribucion(1, 3);
    int numeroAleatorio = distribucion(generador);

if(numeroAleatorio ==1)
*pixmap = new (:/perro1)
else if(numeroAleatorio==2)
*pixmap = new (:/perro2)
else if(numeroAleatorio==3)
*pixmap = new (:/perro2)
*/
