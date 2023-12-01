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

    // Desactivar barras de desplazamiento
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    scene1 = new QGraphicsScene();
    principal();
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

void MainWindow::on_btn_Regresar_clicked()
{
    principal();
}

void MainWindow::on_btn_Jugar_clicked()
{
    scene2 = new QGraphicsScene();
    ui->graphicsView->setScene(scene2);
    QImage imagenF(":/Imagenes/textura1.jpg");
    QBrush brochaF(imagenF);
    ui->graphicsView->setBackgroundBrush(brochaF);
    scene2->setSceneRect(0,0,800,500);
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
    archivoLectura.close();
    archivoLectura2.open("perros.txt");
    if(archivoLectura2.is_open()){
        while(getline(archivoLectura2, linea2)){
            int x, y;
            istringstream ss(linea2);
            string token;
            int index = 0;
            while (getline(ss, token, ',')) {
                if (index == 0) {
                    x = stoi(token); // Convierte la cadena a entero
                } else if (index == 1) {
                    y = stoi(token);
                }
                index++;
            }
            enemigos.push_back(new Enemigo());
            scene2->addItem(enemigos.back());
            enemigos.back()->posicion(x,y);
        }
    }
    archivoLectura2.close();

    //hacer que se generen varios perros y colocarlos en diferentes posiciones, además de agregarlos a una lista

    jugador = new Jugador();
    scene2->addItem(jugador);
    jugador->posicion(300,100);
    jugador->setScale(0.5);

    ui->lbl_vida->show();
    ui->lbl_vida->setText("Vida: " +QVariant(jugador->getSalud()).toString());
    ui->lbl_puntaje->show();
    ui->lbl_puntaje->setText("Puntaje: " +QVariant(jugador->getPuntos()).toString());


    timer = new QTimer();
    timer1 = new QTimer();
    timer->start(200);
    timer1->start(200);
    connect(timer, SIGNAL(timeout()),this,SLOT(seguimiento()));
    connect(timer1, SIGNAL(timeout()),this,SLOT(colPortal()));

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
    scene4->setSceneRect(0, 0, imagenF.width(), imagenF.height());
    ui->graphicsView->resetTransform();
    ui->lbl_vida->hide();
    ui->lbl_puntaje->hide();
    ui->btn_Jugar->hide();
    ui->btb_Salir->hide();
    ui->btb_Instrucciones->hide();
    ui->btn_Regresar->show();
}

void MainWindow::on_btb_Salir_clicked()
{
    close();
}

void MainWindow::seguimiento()
{
    for(const auto& itE : enemigos)
    {
        itE->actualizarPosicion(jugador->getPosX(), jugador->getPosY());
    }
}

void MainWindow::principal()
{
    ui->graphicsView->setScene(scene1);
    QImage imagenF(":/Imagenes/portada.jpg");
    QBrush brochaF(imagenF);
    ui->graphicsView->setBackgroundBrush(brochaF);
    scene1->setSceneRect(0, 0, imagenF.width(), imagenF.height());
    ui->graphicsView->resetTransform();

    ui->lbl_vida->hide();
    ui->lbl_puntaje->hide();
    ui->btn_Jugar->show();
    ui->btb_Instrucciones->show();
    ui->btb_Salir->show();
    ui->btn_Regresar->hide();
}

void MainWindow::colPortal()
{
    for(const auto& itP : portales)
    {
        for(const auto& itE : enemigos)
        {
            if(itE->collidesWithItem(itP))
            {
                jugador->setPuntos(jugador->getPuntos() + itE->getTipo());
                ui->lbl_puntaje->setText("Puntaje: " +QVariant(jugador->getPuntos()).toString());
                QGraphicsItem* item = itE;

                enemigos.removeOne(item);
                scene2->removeItem(item);
                delete item;
            }
        }
    }

    for(const auto& it : portales)
    {
        if(jugador->collidesWithItem(it))
        {
            jugador->setSalud(0);
            ui->lbl_vida->setText("Vida: " +QVariant(jugador->getSalud()).toString());
            disconnect(timer, SIGNAL(timeout()), this, SLOT(seguimiento()));
            disconnect(timer1, SIGNAL(timeout()), this, SLOT(colPortal()));
            timer->stop();
            timer1->stop();
            scene2->removeItem(jugador);
            jugador->deleteLater();
            qDeleteAll(enemigos);
            enemigos.clear();
            qDeleteAll(portales);
            portales.clear();
            principal();
        }
    }

    for(const auto& it : enemigos)
    {
        if(jugador->collidesWithItem(it))
        {
            if(jugador->getSalud() > 0)
            {
                jugador->setSalud(jugador->getSalud()-it->getDano());
                ui->lbl_vida->setText("Vida: " +QVariant(jugador->getSalud()).toString());
                if(jugador->getSalud()>0)
                {
                    jugador->posicion(300,100);
                }
                else
                {
                    disconnect(timer, SIGNAL(timeout()), this, SLOT(seguimiento()));
                    disconnect(timer1, SIGNAL(timeout()), this, SLOT(colPortal()));
                    timer->stop();
                    timer1->stop();
                    scene2->removeItem(jugador);
                    jugador->deleteLater();
                    qDeleteAll(enemigos);
                    enemigos.clear();
                    qDeleteAll(portales);
                    portales.clear();
                    principal();
                }
            }
        }

    }
}
