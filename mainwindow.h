#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter>
#include <QPushButton>
#include "portal.h"
#include <QList>
#include <QKeyEvent>

#include "jugador.h"
#include "enemigo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void keyPressEvent(QKeyEvent *ev);
    //void keyPressEvent_N2(QKeyEvent *ev);

    void on_btn_Regresar_clicked();

    void on_btn_Jugar_clicked();

    void on_btb_Instrucciones_clicked();

    void on_btb_Salir_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene1;
    QGraphicsScene *scene2;
    QGraphicsScene *scene3;
    QGraphicsScene *scene4;
    QPixmap *fondoInicio;
    QPixmap *fondoNivel1;
    QList<Portal*> portales;
    QList<Enemigo*> enemigos;
    Enemigo *perro;

    Jugador *jugador;
};
#endif // MAINWINDOW_H
