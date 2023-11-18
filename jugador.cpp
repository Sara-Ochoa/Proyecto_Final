#include "jugador.h"

Jugador::Jugador()
{

}

Jugador::Jugador(int x, int y, int ancho, int alto)
{
    posX = x;
    posY = y;
    velocidad = 5;
    this->ancho = ancho;
    this->alto = alto;

    setPos(posX, posY);
}

void Jugador::moverArriba()
{
    posY -= velocidad;
    setPos(posX, posY);
}

void Jugador::moverAbajo()
{
    posY += velocidad;
    setPos(posX, posY);
}

void Jugador::moverDerecha()
{
    posX += velocidad;
    setPos(posX, posY);
}

void Jugador::moverIzquierda()
{
    posX -= velocidad;
    setPos(posX, posY);
}

QRectF Jugador::boundingRect() const
{
    return QRect(0, 0, ancho,alto);
}

void Jugador::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
