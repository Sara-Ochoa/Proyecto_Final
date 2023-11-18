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

    botonSalir = new QPushButton("Salir", this);
    connect(botonSalir, &QPushButton::clicked, this, &MainWindow::on_BtnSalir_clicked);
    botonSalir->move(50,500);

    botonJugar = new QPushButton("Jugar", this);
    connect(botonJugar, &QPushButton::clicked, this, &MainWindow::on_BtnJugar_clicked);
    botonJugar->move(50,450);


    /*
    scene3 = new QGraphicsScene();
    ui->graphicsView->setScene(scene3);
    QImage imagenF(":/Imagenes/fondo.jpg");
    QBrush brochaF(imagenF);
    ui->graphicsView->setBackgroundBrush(brochaF);
    ui->graphicsView->scale(3.5,4);
    scene3->setSceneRect(700,100,100,100);
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_BtnSalir_clicked()
{
    close();
}


void MainWindow::on_BtnJugar_clicked()
{
    scene2 = new QGraphicsScene();
    ui->graphicsView->setScene(scene2);
    QImage imagenF(":/Imagenes/textura1.jpg");
    QBrush brochaF(imagenF);
    ui->graphicsView->setBackgroundBrush(brochaF);
    //botonJugar->deleteLater();
    //botonSalir->deleteLater();
    botonJugar->hide();
    botonSalir->hide();

    string linea;
    ifstream archivoLectura;
    archivoLectura.open("coordenadas.txt");
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
}

