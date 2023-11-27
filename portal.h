#ifndef PORTAL_H
#define PORTAL_H
#include <QGraphicsItem>

class Portal: public QGraphicsItem
{
    char tipo;
    int posx;
    int posy;
    int radio;

public:
    Portal(int x, int y,  int r);
    void abrirPortal();
    void llevarInicio();
    void eliminarPersonaje();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // PORTAL_H
