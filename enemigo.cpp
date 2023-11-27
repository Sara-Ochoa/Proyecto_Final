#include "enemigo.h"
#include <math.h>
#include <random>

using namespace std;

Enemigo::Enemigo(QObject *parent) : QObject{parent}
{
    timer = new QTimer();
    columnas = 0;
    filas = 0;
    pixmap = new QPixmap(imagen);

    //dimensiones de cada una de las imagenes
    ancho = 150;
    alto = 300;

    timer->start(250); //modifica la velocidad en que itera entre las imagenes
    connect(timer, &QTimer::timeout, this,&Enemigo::Actualizacion);
}

int Enemigo::getSalud() const
{
    return salud;
}

void Enemigo::setSalud(int newSalud)
{
    salud = newSalud;
}

QString Enemigo::getImagen() const
{
    return imagen;
}

void Enemigo::setImagen(const QString &newImagen)
{
    imagen = newImagen;
}

int Enemigo::getPuntos() const
{
    return puntos;
}

void Enemigo::setPuntos(int newPuntos)
{
    puntos = newPuntos;
}

void Enemigo::Actualizacion()
{
    columnas += 50;
    if(columnas >= 150){
        columnas = 0;
    }
    this->update(-ancho/2, -alto/2, ancho, alto);
}

QRectF Enemigo::boundingRect() const
{
    return QRect(-ancho/2, -alto/2, ancho, alto);
}

void Enemigo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //painter->drawPixmap(-ancho/2, -alto/2, *pixmap, columnas, filas, ancho, alto);
    mt19937 generador(random_device{}());
    uniform_int_distribution<int> distribucion(1, 3);
    int numeroAleatorio = distribucion(generador);

    if(numeroAleatorio ==1){
        setImagen(":/Imagenes/tipo1.png");
        //settearle los puntos
        painter->drawPixmap(-ancho/2, -alto/2, *pixmap, columnas, filas, ancho, alto);
    }
    else if(numeroAleatorio==2){
        setImagen(":/Imagenes/tipo2.png");
        painter->drawPixmap(-ancho/2, -alto/2, *pixmap, columnas, filas, ancho, alto);
    }
    else if(numeroAleatorio==3){
        setImagen(":/Imagenes/tipo3.png");
        painter->drawPixmap(-ancho/2, -alto/2, *pixmap, columnas, filas, ancho, alto);
    }
}

Enemigo::Enemigo(int x, int y, int v, int p)
{
    posX = x;
    posY = y;
    velocidad = v;
    puntos = p;
}


Enemigo::Enemigo(int x, int y, int v)
{
    posX = x;
    posY = y;
    velocidad = v;
    salud = 10;
}

void Enemigo::actualizarPosicion(int jugadorX, int jugadorY)
{
    // Calcular el vector de dirección hacia el jugador
    int dx = jugadorX - posX;
    int dy = jugadorY - posY;

    // Calcular la magnitud del vector
    double distancia = sqrt(dx * dx + dy * dy);

    // Si el enemigo está lo suficientemente cerca del jugador, persigue al jugador
    if (distancia < velocidad)
    {
        posX += (velocidad * dx) / distancia;
        posY += (velocidad * dy) / distancia;
    }
}

void Enemigo::recibirDano()
{
    setSalud(getSalud()-1);
}
