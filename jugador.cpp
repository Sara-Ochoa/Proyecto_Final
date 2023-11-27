#include "jugador.h"

float Jugador::getFilas() const
{
    return filas;
}

void Jugador::setFilas(float newFilas)
{
    filas = newFilas;
}

QString Jugador::getPath() const
{
    return path;
}

void Jugador::setPath(const QString &newPath)
{
    path = newPath;
}

Jugador::Jugador(QObject *parent) : QObject{parent}
{//constructor
    timer = new QTimer();
    columnas = 0;
    filas = 0;
    pixmap = new QPixmap(":/Imagenes/Morty.png");

    //dimensiones de cada una de las imagenes
    ancho = 131.25;
    alto = 168.25;

    timer->start(250); //modifica la velocidad en que itera entre las imagenes
    connect(timer, &QTimer::timeout, this,&Jugador::Actualizacion);
}


/*
Jugador::Jugador(int w, int h){
    path = ":/Imagenes/Rick_Right.png";
    pixmap_N2 = new QPixmap(path);
    this->w = w;
    this->h = h;
}
*/

void Jugador::Actualizacion()
{
    columnas += 131.25;
    if(columnas >= 525){
        columnas = 0;
    }
    this->update(-ancho/2, -alto/2, ancho, alto);
}

QRectF Jugador::boundingRect() const
{
    return QRect(-ancho/2, -alto/2, ancho, alto);
}

void Jugador::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2, -alto/2, *pixmap, columnas, filas, ancho, alto);
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

void Jugador::posicion(int x, int y)
{
    posX = x;
    posY = y;
    velocidad = 20;
    setPos(posX, posY);
}
