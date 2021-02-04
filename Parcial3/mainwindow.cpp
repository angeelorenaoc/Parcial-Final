#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Punto1_clicked()
{

}

void MainWindow::on_Punto2_clicked()
{

}

void MainWindow::on_Punto3_clicked()
{

}

void MainWindow::on_Punto4_clicked()
{

}

void MainWindow::on_Punto5_clicked()
{

}

void MainWindow::on_Iniciar_clicked()
{

}
