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

public slots:

    void move();//Metodo que permite la actualizacion de  la posicion de las balas
    void ruta();//Metodo que grafica la trayectoria de las balas

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
    //-------------------------Metodos de simulacion----------------------------
    void DisparoOfensivo();//Punto 1
    void DisparoDefensivo();//Punto 2
    void DisparoDefensivo2(int anguloo, int vo0);//Punto 3
    void DisparoDefensivo3(int anguloo, int vo0);//Punto 4
    void DisparoOfensivo1(int anguloo, int vo0, int angulod, int vd0);//Punto 5
    //---------------------------------------------------------------------------
    void Creacion_caniones();
    bool Impacto(float XO, float YO, float XD, float YD, float Rang);

    float dt;
    int punto;
    int h_limit;
    int v_limit;

    QTimer *timer;
    QTimer *Camino;

    QList <Canion*> caniones;// Lista de caniones y rangos de danio
    QList <Proyectil_grafico*> Proyectiles;//Lista de balas
    QList <Proyectil_grafico*> Respaldo;/* Lista de Respaldo para que la trayectoria
                                           de la bala aparezca en escena*/
};
#endif // MAINWINDOW_H
