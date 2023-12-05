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
    int posX;
    int posY;
    int puntos;
    int velocidad;
    int nivel;
    float filas,columnas;
    float ancho,alto;
    QString path;

public:
    explicit Jugador(QObject *parent = nullptr, int nivel = 0);

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
    void pararTimer();

    int getSalud() const;
    void setSalud(int newSalud);
    int getPosX() const;
    void setPosX(int newPosX);
    int getPosY() const;
    void setPosY(int newPosY);
    int getPuntos() const;
    void setPuntos(int newPuntos);
    int getVelocidad() const;
    void setVelocidad(int newVelocidad);
    int getNivel() const;
    void setNivel(int newNivel);
    float getFilas() const;
    void setFilas(float newFilas);
    float getColumnas() const;
    void setColumnas(float newColumnas);
    float getAncho() const;
    void setAncho(float newAncho);
    float getAlto() const;
    void setAlto(float newAlto);
    QString getPath() const;
    void setPath(const QString &newPath);

signals:

public slots:
    void Actualizacion();

};

#endif // JUGADOR_H
