#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPixmap>
#include <QPushButton>
#include "portal.h"
#include <QList>

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
    void on_BtnSalir_clicked();

    void on_BtnJugar_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene1;
    QGraphicsScene *scene2;
    QGraphicsScene *scene3;
    QPixmap *fondoInicio;
    QPixmap *fondoNivel1;
    QPushButton *botonSalir;
    QPushButton *botonJugar;
    QList<Portal*> portales;
};
#endif // MAINWINDOW_H
