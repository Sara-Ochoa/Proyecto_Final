#ifndef JUGADOR_H
#define JUGADOR_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

class Jugador : public QObject, public QGraphicsItem
{
    Q_OBJECT

private:
    int salud;
    int puntos;
    int cantidadBalas;
    int posX;
    int posY;
    int velocidad;
    float filas,columnas;
    float ancho,alto;
    //int w,h;
    QString path;

public:
    explicit Jugador(QObject *parent = nullptr);
    //Jugador(int w, int h);

    QTimer *timer;
    QPixmap *pixmap;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    void moverArriba();
    void moverAbajo();
    void moverDerecha();
    void moverIzquierda();
    void saltar();
    void posicion(int x, int y);
    void disparar();
    void recogerVida();
    void recogerBalas();
    void morir();
    void recibirDano();

    float getFilas() const;
    void setFilas(float newFilas);

    QString getPath() const;
    void setPath(const QString &newPath);

signals:

public slots:
    void Actualizacion();

};

#endif // JUGADOR_H
