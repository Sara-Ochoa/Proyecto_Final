#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QDebug>

class Enemigo : public QObject, public QGraphicsItem
{
    Q_OBJECT
private:
    int salud;
    int posX;
    int posY;
    int velocidad;
    int dano;
    int tipo;
    double ace = -18.75;
    double tiempo = 0.1;

    float filas,columnas;
    float ancho,alto;
public:
    explicit Enemigo(QObject *parent = nullptr, int tipo = 0);

    QTimer *timer;
    QTimer *timer1;
    QPixmap *pixmap;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    void actualizarPosicion(int jugadorX,int jugadorY);
    void posicion(int x, int y);
    void pararTimer();

    int getSalud() const;
    void setSalud(int newSalud);
    int getPuntos() const;
    void setPuntos(int newPuntos);
    float getFilas() const;
    void setFilas(float newFilas);
    int getTipo() const;
    void setTipo(int newTipo);
    int getDano() const;
    void setDano(int newDano);
    int getPosX() const;
    void setPosX(int newPosX);
    int getPosY() const;
    void setPosY(int newPosY);
    int getVelocidad() const;
    void setVelocidad(int newVelocidad);
    double getAce() const;
    void setAce(double newAce);
    double getTiempo() const;
    void setTiempo(double newTiempo);
    float getColumnas() const;
    void setColumnas(float newColumnas);
    float getAncho() const;
    void setAncho(float newAncho);
    float getAlto() const;
    void setAlto(float newAlto);

signals:

public slots:
    void Actualizacion();
    void salto();
};

#endif // ENEMIGO_H
