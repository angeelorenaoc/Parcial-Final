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

    void move();

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

    void DisparoOfensivo(float XD, float YD, float R);
    void DisparoDefensivo(int Do, int Dd, int rd);
    void DisparoDefensivo2(int anguloo, int vo0);
    void DisparoDefensivo3(int DO,int DD, int anguloo, int vo0);
    void DisparoOfensivo1(int DO,int DD, int anguloo, int vo0, int angulod, int vd0);
    void Creacion_caniones();
    bool Verificacion_impacto(int b, int rd);
    bool Impacto(float XO, float YO, float XD, float YD, float Rang);

    float dt;
    int punto;
    int h_limit;
    int v_limit;

    QTimer *timer;

    QList <Canion*> caniones;
    QList <Proyectil_grafico*> Proyectiles;
};
#endif // MAINWINDOW_H
