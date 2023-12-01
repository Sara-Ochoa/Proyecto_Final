#ifndef ENEMIGO_H
#define ENEMIGO_H

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
    int dano;
    float filas,columnas;
    float ancho,alto;
    QString imagen;
    int tipo;
public:
    explicit Enemigo(QObject *parent = nullptr);
    QTimer *timer;
    QPixmap *pixmap;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    void actualizarPosicion(int jugadorX,int jugadorY);
    void morir();
    void recibirDano();
    int getSalud() const;
    void setSalud(int newSalud);
    void posicion(int x, int y);

    QString getImagen() const;
    void setImagen(const QString &newImagen);

    int getPuntos() const;
    void setPuntos(int newPuntos);

    float getFilas() const;
    void setFilas(float newFilas);

    int getTipo() const;
    void setTipo(int newTipo);

    int getDano() const;
    void setDano(int newDano);

signals:

public slots:
    void Actualizacion();
};

#endif // ENEMIGO_H
