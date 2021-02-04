#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMessageBox>
#include <QMainWindow>
#include <string.h>
#include <string>
#include <QDebug>
#include <QTimer>
#include <QList>
#include <QString>

#include "canion.h"
#include "proyectil.h"
#include "proyectil_grafico.h"


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
    void on_Punto1_clicked();
    void on_Punto2_clicked();
    void on_Punto3_clicked();
    void on_Punto4_clicked();
    void on_Punto5_clicked();
    void on_Iniciar_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene = new QGraphicsScene(this);

    QMessageBox msgBox;

    void DisparoOfensivo(Canion DO, Canion DD);

    float dt;
    int punto;
    int h_limit;
    int v_limit;

    QList <Canion*> caniones;
    QList <Proyectil_grafico*> Proyectiles;
};
#endif // MAINWINDOW_H