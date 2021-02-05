#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Dimensiones de la escena
    h_limit = 900;
    v_limit = 650;

    scene->setSceneRect(0,0,h_limit,v_limit);
    ui->graphicsView->setScene(scene);
    ui->centralwidget->adjustSize();
    scene->addRect(scene->sceneRect());
    ui->graphicsView->resize(1000,650);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->Iniciar->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DisparoOfensivo(int Do, int Dd, int ro)
{
    int flag = 0;
    float xf,yf;
    float Vxo,Vy0;
    float pi = 3.1416, G = 9.8;
    int V0o = 0;
    int t = 0;
    int angulo = 0;
    for(V0o = 0; V0o < 500 ; V0o+=5){
        for(angulo = 0; angulo < 90; angulo++){
            Vxo = V0o*cos(angulo*pi/180);
            Vy0 = V0o*sin(angulo*pi/180);
            xf = 0.0;
            yf = 0.0;
            for(t = 0; ; t++){
                xf = Vxo*t;
                yf = caniones.at(Do)->getPosy() + Vy0*t -(0.5*G*t*t);
                if(sqrt(pow((caniones.at(Dd)->getPosx() - xf),2)+pow((caniones.at(Dd)->getPosy() - yf),2)) < caniones.at(ro)->getR()){
                    if(yf<0) yf = 0;
//                    QString line = "";
//                    msgBox.setText(line);
                    //Mostrar o almacenar los datos y crear la bala.
                    flag += 1;
                    break;
                }
                if(yf < 0){
                    break;
                }
            }
            if(flag == 3) break;

        }
        if(flag == 3) break;
    }
    if(flag != 3){
        //cout << "No impacto en los disparos esperados"<< endl;
        //Imprimir un mensaje de que no se encontró los 3 disparos
    }
}

void MainWindow::DisparoDefensivo(int Do, int Dd, int rd)
{
    int flag = 0;
    float e = 0;
    float Vxo,Vy0,xf,yf;
    float pi = 3.1416, G = 9.8;
    int V0o = 0;
    int t = 0;
    int angulo = 0;
    for(V0o = 0;V0o > -500; V0o+=5){
        for(angulo = 0; angulo < 90; angulo++){
            Vxo = V0o*cos((angulo+90)*pi/180);
            Vy0 = V0o*sin((angulo+90)*pi/180);
            xf = 0.0;
            yf = 0.0;
            for(t = 0; ; t++){
                xf = caniones.at(Dd)->getPosx()+Vxo*t;
                yf = caniones.at(Dd)->getPosy() + Vy0*t -(0.5*G*t*t);
                e = (sqrt(pow((caniones.at(Do)->getPosx() - xf),2)+pow((caniones.at(Do)->getPosy() - yf),2)));
                if(e < caniones.at(rd)->getR()){
                   // ImprimirResultados(angulo, V0o, xf, yf, t);
                   //Imprimir o almacenar los datos del proyectil y crear la bala
                    flag += 1;
                    break;
                }
                if(yf < 0){
                    break;
                }
            }
            if(flag == 3) break;

        }
        if(flag == 3) break;
    }
    if(flag != 3){
        // cout << "No impacto en los disparos esperados"<< endl;
        //Imprimir un mensaje de que no se encontró los 3 disparos
    }
}

void MainWindow::DisparoDefensivo2(int DO, int DD, int anguloo, int vo0)
{
    int flag = 0;
    float x2,y2,xf,yf;
    float Vxo,Vy0, Vxoo,Vyoo;
    int V0o = 0;
    float t = 2.5;
    float G=9.8, pi=3.1416;
    int angulo = 0;
    Vxoo = vo0*cos((anguloo)*pi/180);
    Vyoo = vo0*sin((anguloo)*pi/180);
    for(V0o = 0; V0o < 500 ; V0o +=5){
        for(angulo = 0; angulo < 90; angulo++){
            Vxo = V0o*cos((angulo+90)*pi/180);
            Vy0 = V0o*sin((angulo+90)*pi/180);
            xf = 0.0;
            yf = 0.0;
            x2 = 0.0;
            y2 = 0.0;
            for(t = 0; ; t++){
                x2 = Vxoo*(t);
                y2 = caniones.at(DO)->getPosy() + Vyoo*(t) -(0.5*G*(t)*(t));
                xf = caniones.at(DD)->getPosx() + Vxo*t;
                yf = caniones.at(DD)->getPosy() + Vy0*t -(0.5*G*t*t);
                if(sqrt(pow((x2 - xf),2)+pow((y2 - yf),2)) < caniones.at(DD)->getR()){
                    if(yf>0 && y2>0){
//                    ImprimirResultados(anguloo,vo0,x2,y2,t);
//                    cout << "_________________________________"<<endl;
//                    ImprimirResultados(angulo, V0o, xf, yf, t);
                    //Imprimir los resultados y crear el disparo
                    flag += 1;
                    break;}
                }
                if(yf < 0){
                    break;
                }
            }
            if(flag == 3) break;

        }
        if(flag == 3) break;
    }
    if(flag != 3){
        //cout << "No impacto en los disparos esperados"<< endl;
        //Si no encuentra los disparos, imprima un mensaje
    }
}

void MainWindow::Creacion_caniones()
{
    //Caniones
    //canion ofensivo
    caniones.push_back(new Canion(10,0,0,0,0));//Organizar el spinbox
    scene->addItem(caniones.back());
    //canion defensivo
    caniones.push_back(new Canion(10,0,1,0,0));//Organizar el spinbox
    scene->addItem(caniones.back());
    //Circulo de rango de daño
    //Rango ofensivo
    caniones.push_back(new Canion(10,0,2,0.025,0));//Organizar el spinbox
    scene->addItem(caniones.back());
    //Rango defensivo
    caniones.push_back(new Canion(10,0,3,0.05,0));//Organizar el spinbox
    scene->addItem(caniones.back());
}


void MainWindow::on_Punto1_clicked()
{
    punto = 1;
}

void MainWindow::on_Punto2_clicked()
{
    punto = 2;
}

void MainWindow::on_Punto3_clicked()
{
    punto = 3;
}

void MainWindow::on_Punto4_clicked()
{
    punto = 4;
}

void MainWindow::on_Punto5_clicked()
{
    punto = 5;
}

void MainWindow::on_Iniciar_clicked()
{

}
