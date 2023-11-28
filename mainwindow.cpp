#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene1 = new QGraphicsScene();
    ui->graphicsView->setScene(scene1);
    QImage imagenF(":/Imagenes/portada.jpg");
    QBrush brochaF(imagenF);
    ui->graphicsView->setBackgroundBrush(brochaF);
    scene1->setSceneRect(800,450,100,190);
    ui->graphicsView->scale(0.47,0.5);


    ui->label->hide();
    ui->label_2->hide();
    ui->btn_Regresar->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_W){
        jugador->setFilas(504.75);
        jugador->moverArriba();
    }
    else if(ev->key()==Qt::Key_S){
        jugador->moverAbajo();
        jugador->setFilas(0);
    }
    else if(ev->key()==Qt::Key_D){
        jugador->moverDerecha();
        jugador->setFilas(336.5);
    }
    else if(ev->key()==Qt::Key_A){
        jugador->moverIzquierda();
        jugador->setFilas(168.25);
    }
}

/*
void MainWindow::keyPressEvent_N2(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_D){
        jugador_N2->moverDerecha();
        jugador_N2->setPath(":/Imagenes/Rick_Right.png");
    }
    else if(ev->key()==Qt::Key_A){
        jugador_N2->moverIzquierda();
        jugador_N2->setPath(":/Imagenes/Rick_Left.png");
    }
}
*/


void MainWindow::on_btn_Regresar_clicked()
{
    //ui->setupUi(this);
    //scene1 = new QGraphicsScene();
    ui->graphicsView->setScene(scene1);
    QImage imagenF(":/Imagenes/portada.jpg");
    QBrush brochaF(imagenF);
    ui->graphicsView->setBackgroundBrush(brochaF);
    scene1->setSceneRect(800,450,100,190);
    ui->graphicsView->scale(0.47,0.5);

    ui->label->hide();
    ui->label_2->hide();
    ui->btn_Jugar->show();
    ui->btb_Instrucciones->show();
    ui->btb_Salir->show();
    ui->btn_Regresar->hide();
}


void MainWindow::on_btn_Jugar_clicked()
{
    scene2 = new QGraphicsScene();
    ui->graphicsView->setScene(scene2);
    QImage imagenF(":/Imagenes/textura1.jpg");
    QBrush brochaF(imagenF);
    ui->graphicsView->setBackgroundBrush(brochaF);
    scene2->setSceneRect(0,0,769,529);
    ui->btn_Jugar->hide();
    ui->btb_Instrucciones->hide();
    ui->btb_Salir->hide();
    ui->btn_Regresar->hide();

    string linea, linea2;
    ifstream archivoLectura, archivoLectura2;
    archivoLectura.open("portales.txt");
    if(archivoLectura.is_open()){
        while(getline(archivoLectura, linea)){
            int x, y, r;
            istringstream ss(linea);
            string token;
            int index = 0;
            while (getline(ss, token, ',')) {
                if (index == 0) {
                    x = stoi(token); // Convierte la cadena a entero
                } else if (index == 1) {
                    y = stoi(token);
                } else if (index == 2) {
                    r = stoi(token);
                }
                index++;
            }
            portales.push_back(new Portal(x,y,r));
            scene2->addItem(portales.back());
        }
    }

    //hacer que se generen varios perros y colocarlos en diferentes posiciones, además de agregarlos a una lista

    jugador = new Jugador();
    scene2->addItem(jugador);
    jugador->posicion(300,100);

    perro = new Enemigo();
    scene2->addItem(perro);
    perro->posicion(200,50);

    ui->label->show();
    ui->label_2->show();



    /*
    scene3 = new QGraphicsScene();
    ui->graphicsView->setScene(scene3);
    QImage imagenF(":/Imagenes/fondo.jpg");
    QBrush brochaF(imagenF);
    ui->graphicsView->setBackgroundBrush(brochaF);
    ui->graphicsView->scale(3.5,4);
    scene3->setSceneRect(700,100,100,100);
    botonJugar->hide();
    botonSalir->hide();
    botonInstrucciones->hide();

    ui->label->show();
    ui->label_2->show();

    jugador_N2 = new Jugador(100,100);
    scene3->addItem(jugador_N2);
    jugador_N2->posicion(550,160);*/
    //perro = new Portal(700,150,100,100);
    //scene3->addItem(perro);

    //rick = new Jugador1(550,160,100,100);
    //scene3->addItem(rick);
}


void MainWindow::on_btb_Instrucciones_clicked()
{
    scene4 = new QGraphicsScene();
    ui->graphicsView->setScene(scene4);
    QImage imagenF(":/Imagenes/Teclas.png");
    QBrush brochaF(imagenF);
    ui->graphicsView->setBackgroundBrush(brochaF);
    scene4->setSceneRect(140,340,200,300);
    ui->graphicsView->scale(3.5,3.5);
    ui->label->hide();
    ui->label_2->hide();
    ui->btn_Jugar->hide();
    ui->btb_Salir->hide();
    ui->btb_Instrucciones->hide();
    ui->btn_Regresar->show();
}


void MainWindow::on_btb_Salir_clicked()
{
    close();
}

