#include "enemigo.h"
#include <math.h>

int Enemigo::getSalud() const
{
    return salud;
}

void Enemigo::setSalud(int newSalud)
{
    salud = newSalud;
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

