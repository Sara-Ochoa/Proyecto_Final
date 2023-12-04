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
    if(ev->key()==Qt::Key_W && jugador->getNivel() == 1){
        jugador->setFilas(504.75);
        jugador->moverArriba();
    }
    else if(ev->key()==Qt::Key_S && jugador->getNivel() == 1){
        jugador->moverAbajo();
        jugador->setFilas(0);
    }
    else if(ev->key()==Qt::Key_D){
        if(jugador->getNivel()==1){
            jugador->moverDerecha();
            jugador->setFilas(336.5);
        }
        else
        {
            jugador->moverDerecha();
            jugador->setPath(":/Imagenes/Rick-right.png");
        }
    }
    else if(ev->key()==Qt::Key_A){
        if(jugador->getNivel() == 1)
        {
            jugador->moverIzquierda();
            jugador->setFilas(168.25);
        }
        else
        {
            jugador->moverIzquierda();
            jugador->setPath(":/Imagenes/Rick-Left.png");
        }
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
    ui->lbl_over->hide();

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
            portales.push_back(new Portal(x,y,r,1));
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

    jugador = new Jugador(this, 1);
    scene2->addItem(jugador);
    jugador->posicion(300,100);
    jugador->setScale(0.5);

    ui->lbl_vida->show();
    ui->lbl_vida->setText(" VIDA: " +QVariant(jugador->getSalud()).toString());
    ui->lbl_puntaje->show();
    ui->lbl_puntaje->setText(" PUNTAJE: " +QVariant(jugador->getPuntos()).toString());

    timer = new QTimer();
    timer1 = new QTimer();
    timer->start(200);
    timer1->start(200);
    connect(timer, SIGNAL(timeout()),this,SLOT(seguimiento()));
    connect(timer1, SIGNAL(timeout()),this,SLOT(colPortal()));
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
    ui->lbl_over->hide();
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
    ui->lbl_over->hide();
}

void MainWindow::nivel2()
{
    jugador->setNivel(2);
    QImage imagenF(":/Imagenes/fondo.jpg");
    QBrush brochaF(imagenF);
    ui->graphicsView->setBackgroundBrush(brochaF);
    ui->lbl_vida->show();
    ui->lbl_puntaje->hide();
    ui->btn_Jugar->hide();
    ui->btb_Instrucciones->hide();
    ui->btb_Salir->hide();
    ui->btn_Regresar->hide();
    ui->lbl_over->hide();
}

void MainWindow::colPortal()
{
    if(jugador->getPuntos()>=0)
    {
        disconnect(timer, SIGNAL(timeout()), this, SLOT(seguimiento()));
        disconnect(timer1, SIGNAL(timeout()), this, SLOT(colPortal()));
        timer->stop();
        timer1->stop();
        delete timer;
        delete timer1;
        for(const auto it : enemigos)
            delete it;
        enemigos.clear();
        for(const auto it : portales)
            delete it;
        portales.clear();
        ui->lbl_vida->hide();
        ui->lbl_puntaje->hide();

        mt19937 generador(random_device{}());
        uniform_int_distribution<int> distribucion(1, 3);
        int orden = distribucion(generador);

        if(orden == 1)
        {
            portal1 = new Portal(175, 200, 60, 2);
            scene2->addItem(portal1);
            portal2 = new Portal(375, 200, 60, 2);
            scene2->addItem(portal2);
            portal3 = new Portal(575, 200, 60, 2);
            scene2->addItem(portal3);
        }
        else if(orden == 2)
        {
            portal1 = new Portal(375, 200, 60, 2);
            scene2->addItem(portal1);
            portal2 = new Portal(575, 200, 60, 2);
            scene2->addItem(portal2);
            portal3 = new Portal(175, 200, 60, 2);
            scene2->addItem(portal3);
        }
        else if(orden == 3)
        {
            portal1 = new Portal(575, 200, 60, 2);
            scene2->addItem(portal1);
            portal2 = new Portal(175, 200, 60, 2);
            scene2->addItem(portal2);
            portal3 = new Portal(375, 200, 60, 2);
            scene2->addItem(portal3);
        }
        else if(orden == 4)
        {
            portal1 = new Portal(375, 200, 60, 2);
            scene2->addItem(portal1);
            portal2 = new Portal(175, 200, 60, 2);
            scene2->addItem(portal2);
            portal3 = new Portal(575, 200, 60, 2);
            scene2->addItem(portal3);
        }
        else if(orden == 5)
        {
            portal1 = new Portal(575, 200, 60, 2);
            scene2->addItem(portal1);
            portal2 = new Portal(375, 200, 60, 2);
            scene2->addItem(portal2);
            portal3 = new Portal(175, 200, 60, 2);
            scene2->addItem(portal3);
        }
        else if(orden == 6)
        {
            portal1 = new Portal(175, 200, 60, 2);
            scene2->addItem(portal1);
            portal2 = new Portal(575, 200, 60, 2);
            scene2->addItem(portal2);
            portal3 = new Portal(375, 200, 60, 2);
            scene2->addItem(portal3);
        }

        timer2 = new QTimer();
        timer2->start(200);
        connect(timer2, SIGNAL(timeout()),this,SLOT(portalesC()));
    }

    if(jugador->getSalud() > 0)
    {
        for(const auto& itP : portales)
        {
            for(const auto& itE : enemigos)
            {
                if(itE->collidesWithItem(itP))
                {
                    jugador->setPuntos(jugador->getPuntos() + itE->getTipo());
                    ui->lbl_puntaje->setText(" PUNTAJE: " +QVariant(jugador->getPuntos()).toString());
                    QGraphicsItem* item = itE;

                    enemigos.removeOne(item);
                    scene2->removeItem(item);
                    delete item;
                }
            }
        }
    }

    if(jugador->getSalud() > 0)
    {
        for(const auto& it : portales)
        {
            if(jugador->collidesWithItem(it))
            {
                jugador->setSalud(0);
                ui->lbl_vida->setText(" VIDA: " +QVariant(jugador->getSalud()).toString());
            }
        }
    }


    if(jugador->getSalud() > 0)
    {
        for(const auto& it : enemigos)
        {
            if(jugador->collidesWithItem(it))
            {
                if(jugador->getSalud() > 0)
                {
                    jugador->setSalud(jugador->getSalud()-it->getDano());
                    ui->lbl_vida->setText(" VIDA: " +QVariant(jugador->getSalud()).toString());
                    if(jugador->getSalud()>0)
                    {
                        jugador->posicion(300,100);
                    }
                }
            }
        }
    }

    if(jugador->getSalud() <= 0)
    {
        disconnect(timer, SIGNAL(timeout()), this, SLOT(seguimiento()));
        disconnect(timer1, SIGNAL(timeout()), this, SLOT(colPortal()));
        timer->stop();
        timer1->stop();
        delete timer;
        delete timer1;
        scene2->removeItem(jugador);
        jugador->deleteLater();
        for(const auto it : enemigos)
            delete it;
        enemigos.clear();
        for(const auto it : portales)
            delete it;
        portales.clear();
        ui->lbl_vida->hide();
        ui->lbl_puntaje->hide();
        QBrush brochaF(Qt::black);
        ui->graphicsView->setBackgroundBrush(brochaF);
        ui->lbl_over->setText("GAME OVER");
        ui->lbl_over->show();
        ui->btn_Regresar->show();
    }
}

void MainWindow::portalesC()
{
    if(jugador->collidesWithItem(portal1))
    {
        disconnect(timer2, SIGNAL(timeout()), this, SLOT(portalesC()));
        timer2->stop();
        delete timer2;

        scene2->removeItem(portal1);
        delete portal1;

        scene2->removeItem(portal2);
        delete portal2;

        if(portal3)
        {
            scene2->removeItem(portal3);
            delete portal3;
        }

        jugador->pararTimer();

        nivel2();
    }
    else if(jugador->collidesWithItem(portal2))
    {
        disconnect(timer2, SIGNAL(timeout()), this, SLOT(portalesC()));
        timer2->stop();
        delete timer2;
        scene2->removeItem(jugador);
        jugador->deleteLater();

        scene2->removeItem(portal1);
        delete portal1;

        scene2->removeItem(portal2);
        delete portal2;

        if(portal3)
        {
            scene2->removeItem(portal3);
            delete portal3;
        }

        QBrush brochaF(Qt::black);
        ui->graphicsView->setBackgroundBrush(brochaF);
        ui->lbl_over->setText("BAD LUCK");
        ui->lbl_over->show();
        ui->btn_Regresar->show();
    }
}
