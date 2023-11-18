#ifndef JUGADOR_H
#define JUGADOR_H
#include <QGraphicsItem>

class Jugador: public QGraphicsItem
{
    int salud;
    int puntos;
    int cantidadBalas;
    int posX;
    int posY;
    int velocidad;
    int alto;
    int ancho;

public:
    Jugador();
    Jugador(int x, int y, int ancho, int alto);
    void moverArriba();
    void moverAbajo();
    void moverDerecha();
    void moverIzquierda();
    void disparar();
    void recogerVida();
    void recogerBalas();
    void morir();
    void recibirDano();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // JUGADOR_H
