#include "enemigo.h"
#include <math.h>
#include <random>

using namespace std;

float Enemigo::getFilas() const
{
    return filas;
}

void Enemigo::setFilas(float newFilas)
{
    filas = newFilas;
}

int Enemigo::getTipo() const
{
    return tipo;
}

void Enemigo::setTipo(int newTipo)
{
    tipo = newTipo;
}

int Enemigo::getDano() const
{
    return dano;
}

void Enemigo::setDano(int newDano)
{
    dano = newDano;
}

Enemigo::Enemigo(QObject *parent) : QObject{parent}
{
    timer = new QTimer();
    columnas = 0;
    filas = 0;

    mt19937 generador(random_device{}());
    uniform_int_distribution<int> distribucion(1, 3);
    tipo = distribucion(generador);

    //dimensiones de cada una de las imagenes
    ancho = 50;
    alto = 75;

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
    if(tipo == 1){
        pixmap = new QPixmap(":/Imagenes/dogs1.png");
        painter->drawPixmap(-ancho/2, -alto/2, *pixmap, columnas, filas, ancho, alto);
    }
    else if(tipo == 2){
        pixmap = new QPixmap(":/Imagenes/dogs2.png");
        painter->drawPixmap(-ancho/2, -alto/2, *pixmap, columnas, filas, ancho, alto);
    }
    else if(tipo == 3){
        pixmap = new QPixmap(":/Imagenes/dogs3.png");
        painter->drawPixmap(-ancho/2, -alto/2, *pixmap, columnas, filas, ancho, alto);
    }
}

void Enemigo::actualizarPosicion(int jugadorX, int jugadorY)
{
    // Calcular el vector de dirección hacia el jugador
    int dx = jugadorX - posX;
    int dy = jugadorY - posY;

    // Calcular la magnitud del vector
    double distancia = sqrt(dx * dx + dy * dy);

    // Si el enemigo está lo suficientemente cerca del jugador, persigue al jugador
    if (distancia/8 < velocidad)
    {
        posX += (velocidad * dx) / distancia;
        posY += (velocidad * dy) / distancia;
        if(dx < 0 && dy < 0)
        {
            // mueve izq arr, sprite izq
            setFilas(75);
        }
        else if(dx > 0 && dy < 0)
        {
            // mueve derecha arr, sprite der
            setFilas(150);
        }
        else if(dx < 0 && dy > 0)
        {
            // mueve izq ab, sprite
            setFilas(225);
        }
        else if(dx > 0 && dy > 0)
        {
            // mueve derecha ab
            setFilas(0);
        }
        else if(dx == 0 && dy > 0)
        {
            setFilas(0);
        }
        else if(dx == 0 && dy < 0)
        {
            setFilas(225);
        }
        else if(dx > 0 && dy == 0)
        {
            setFilas(150);
        }
        else if(dx < 0 && dy == 0)
        {
            setFilas(75);
        }
    }
    else{
        mt19937 generador(random_device{}());
        uniform_int_distribution<int> distribucion(0, 3);
        int d = distribucion(generador);
        if(d==0 && x() >= 20 && x() <= 780)
        {
            posX += velocidad/2;
            setFilas(150);
        }
        else if(d==1 && x() >= 20 && x() <= 780)
        {
            posX -= velocidad/2;
            setFilas(75);
        }
        else if(d==2 && y() >= 20 && y() <= 480)
        {
            posY += velocidad/2;
            setFilas(0);
        }
        else if(d==3 && y() >= 20 && y() <= 480)
        {
            posY -= velocidad/2;
            setFilas(225);
        }
    }

    setPos(posX, posY);
}

void Enemigo::recibirDano()
{
    setSalud(getSalud()-1);
}

void Enemigo::posicion(int x, int y)
{
    posX = x;
    posY = y;
    if(tipo == 1)
    {
        velocidad = 20;
        dano = 5;
    }
    else if(tipo == 2)
    {
        velocidad = 10;
        dano = 15;
    }
    else if(tipo == 3)
    {
        velocidad = 15;
        dano = 10;
    }
    setPos(posX, posY);
}
