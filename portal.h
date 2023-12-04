#ifndef PORTAL_H
#define PORTAL_H
#include <QGraphicsItem>

class Portal: public QGraphicsItem
{
    int posx;
    int posy;
    int radio;
    int tipo;

public:
    Portal(int x, int y,  int r, int t);
    void abrirPortal();
    void llevarInicio();
    void eliminarPersonaje();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // PORTAL_H
