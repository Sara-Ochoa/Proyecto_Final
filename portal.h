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
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    int getPosx() const;
    void setPosx(int newPosx);
    int getPosy() const;
    void setPosy(int newPosy);
    int getRadio() const;
    void setRadio(int newRadio);
    int getTipo() const;
    void setTipo(int newTipo);
};

#endif // PORTAL_H
