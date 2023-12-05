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

int Enemigo::getPosX() const
{
    return posX;
}

void Enemigo::setPosX(int newPosX)
{
    posX = newPosX;
}

int Enemigo::getPosY() const
{
    return posY;
}

void Enemigo::setPosY(int newPosY)
{
    posY = newPosY;
}

int Enemigo::getVelocidad() const
{
    return velocidad;
}

void Enemigo::setVelocidad(int newVelocidad)
{
    velocidad = newVelocidad;
}

double Enemigo::getAce() const
{
    return ace;
}

void Enemigo::setAce(double newAce)
{
    ace = newAce;
}

double Enemigo::getTiempo() const
{
    return tiempo;
}

void Enemigo::setTiempo(double newTiempo)
{
    tiempo = newTiempo;
}

float Enemigo::getColumnas() const
{
    return columnas;
}

void Enemigo::setColumnas(float newColumnas)
{
    columnas = newColumnas;
}

float Enemigo::getAncho() const
{
    return ancho;
}

void Enemigo::setAncho(float newAncho)
{
    ancho = newAncho;
}

float Enemigo::getAlto() const
{
    return alto;
}

void Enemigo::setAlto(float newAlto)
{
    alto = newAlto;
}

Enemigo::Enemigo(QObject *parent, int t) : QObject{parent}, tipo(t)
{
    timer = new QTimer();
    columnas = 0;
    filas = 0;

    //dimensiones de cada una de las imagenes
    if(tipo == 4)
    {
        ancho = 125;
        alto = 150;
        timer1 = new QTimer();
    }
    else
    {
        ancho = 50;
        alto = 75;
    }

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

void Enemigo::Actualizacion()
{
    columnas += 50;
    if(columnas >= 150){
        columnas = 0;
    }
    this->update(-ancho/2, -alto/2, ancho, alto);
}

void Enemigo::salto()
{
    if(posY >=250 && posY <= 410)
    {
        double desplazamiento = velocidad*tiempo+0.5*ace*pow(tiempo, 2);
        int salto = posY-desplazamiento;
        posicion(posX, salto);
    }
    else if(posY >= 250)
    {
        double desplazamiento = velocidad*tiempo+0.5*ace*pow(tiempo, 2);
        int salto = posY + desplazamiento;
        posicion(posX, salto);
    }
    tiempo += 0.1;

    if(posY > 410)
    {
        posicion(posX, 410);
        tiempo = 0;
        disconnect(timer1, SIGNAL(timeout()),this,SLOT(salto()));
        timer1->stop();
    }
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
    else if(tipo == 4){
        pixmap = new QPixmap(":/Imagenes/Butch.png");
        painter->drawPixmap(boundingRect(), *pixmap, pixmap->rect());
    }
}

void Enemigo::actualizarPosicion(int jugadorX, int jugadorY)
{
    if(tipo == 4)
    {
        // Calcular el vector de dirección hacia el jugador
        int dx = jugadorX - posX;
        int dy = jugadorY - posY;

        // Calcular la magnitud del vector
        double distancia = sqrt(dx * dx + dy * dy);

        posX += (velocidad * dx) / distancia;

        if(distancia/10 < velocidad)
        {
            timer1->start(200);
            connect(timer1, SIGNAL(timeout()),this,SLOT(salto()));
        }
    }
    else
    {
        // Calcular el vector de dirección hacia el jugador
        int dx = jugadorX - posX;
        int dy = jugadorY - posY;

        // Calcular la magnitud del vector
        double distancia = sqrt(dx * dx + dy * dy);

        // Si el enemigo está lo suficientemente cerca del jugador, persigue al jugador
        if (distancia/9 < velocidad)
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
    }

    setPos(posX, posY);
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
    else if(tipo == 4)
    {
        velocidad = 20;
        dano = 5;
    }
    setPos(posX, posY);
}

void Enemigo::pararTimer()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(Actualizacion()));
    timer->stop();
    delete timer;
}
