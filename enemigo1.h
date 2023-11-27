/*
#ifndef ENEMIGO1_H
#define ENEMIGO1_H
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

class Enemigo : public QObject, public QGraphicsItem
{
    Q_OBJECT
private:
    int salud;
    int posX;
    int posY;
    int velocidad;
    int puntos;
    float filas,columnas;
    float ancho,alto;
    QString imagen;
public:
    explicit Enemigo(QObject *parent = nullptr);
    Enemigo(int x, int y, int v, int p);
    Enemigo(int x, int y, int v);

    QTimer *timer;
    QPixmap *pixmap;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    void actualizarPosicion(int jugadorX,int jugadorY);
    void morir();
    void recibirDano();
    int getSalud() const;
    void setSalud(int newSalud);

    QString getImagen() const;
    void setImagen(const QString &newImagen);

    int getPuntos() const;
    void setPuntos(int newPuntos);

signals:

public slots:
    void Actualizacion();
};

#endif // ENEMIGO1_H
*/
