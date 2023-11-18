#ifndef ENEMIGO_H
#define ENEMIGO_H
//#include <QGraphicsItem>

class Enemigo
{
    int salud;
    int posX;
    int posY;
    int velocidad;
    int puntos;
public:
    Enemigo(int x, int y, int v, int p);
    Enemigo(int x, int y, int v);
    void actualizarPosicion(int jugadorX,int jugadorY);
    void morir();
    void recibirDano();
    //QRectF boundingRect() const;
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    int getSalud() const;
    void setSalud(int newSalud);
};

#endif // ENEMIGO_H
