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

int Jugador::getPosX() const
{
    return posX;
}

void Jugador::setPosX(int newPosX)
{
    posX = newPosX;
}

int Jugador::getPosY() const
{
    return posY;
}

void Jugador::setPosY(int newPosY)
{
    posY = newPosY;
}

int Jugador::getPuntos() const
{
    return puntos;
}

void Jugador::setPuntos(int newPuntos)
{
    puntos = newPuntos;
}

int Jugador::getSalud() const
{
    return salud;
}

void Jugador::setSalud(int newSalud)
{
    salud = newSalud;
}

int Jugador::getNivel() const
{
    return nivel;
}

void Jugador::setNivel(int newNivel)
{
    nivel = newNivel;
}

Jugador::Jugador(QObject *parent, int n) : QObject{parent}, nivel(n)
{//constructor
    timer = new QTimer();
    salud = 15;
    velocidad = 8;
    columnas = 0;
    filas = 0;
    puntos = 0;

    //dimensiones de cada una de las imagenes
    ancho = 131.25;
    alto = 160.25;

    timer->start(250); //modifica la velocidad en que itera entre las imagenes
    connect(timer, &QTimer::timeout, this,&Jugador::Actualizacion);
}

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
    if(nivel == 1)
    {
        pixmap = new QPixmap(":/Imagenes/Morty.png");
        painter->drawPixmap(-ancho/2, -alto/2, *pixmap, columnas, filas, ancho, alto);
    }
    else if(nivel == 2)
    {
        pixmap = new QPixmap(path);
        painter->drawPixmap(boundingRect(), *pixmap, pixmap->rect());
    }
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
    setPos(posX, posY);
}

void Jugador::pararTimer()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(Actualizacion()));
    timer->stop();
    delete timer;
}
