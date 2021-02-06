#include "mainwindow.h"
#include "ui_mainwindow.h"
#define pi 3.1416
#define G 9.8

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
    ui->graphicsView->resize(900,650);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->Iniciar->hide();
    ui->AnguloD->hide();
    ui->AnguloO->hide();
    ui->VelocidadD->hide();
    ui->VelocidadO->hide();
    ui->TEXTOAD->hide();
    ui->TEXTOAO->hide();
    ui->TEXTOVD->hide();
    ui->TEXTOVO->hide();

    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
bool MainWindow::Impacto(float XO, float YO, float XD, float YD, float Rang)
{
    bool flag= false;

    if(sqrt(pow((XO - XD),2)+pow((YO - YD),2)) < Rang){
        flag = true;
    }

    return flag;
}

void MainWindow::DisparoOfensivo(float XD, float YD, float R)
{
    int flag = 0;
        float xf,yf;
        float Vxo,Vy0;
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
                    xf = 10+Vxo*t;
    //                qDebug()<<Canones.at(0)->getPosy() + Vy0*t -(0.5*G*t*t)<<v_limit-Canones.at(0)->getPosy() + Vy0*t -(0.5*G*t*t)<<v_limit-(Canones.at(0)->getPosy() + Vy0*t -(0.5*G*t*t));
                    yf = (v_limit-caniones.at(0)->getPosy()) + Vy0*t -(0.5*G*t*t);
                    if(Impacto(xf,yf,XD,YD,R)){
                        qDebug()<<xf<<yf<<XD<<YD;
                        qDebug()<<R;
                        Proyectiles.push_back(new Proyectil_grafico(10,ui->YO->value(),angulo,V0o,0, XD));
                        scene->addItem(Proyectiles.back());
                        Proyectiles.push_back(new Proyectil_grafico(10,ui->YO->value(),angulo,V0o,1,XD));
                        scene->addItem(Proyectiles.back());
                        flag += 1;
                        V0o += 50;
                        break;
                    }
                    if(yf < 0 || xf>XD+R){
                        break;
                    }
                }
                if(flag == 3) break;

            }
            if(flag == 3) break;
        }
        if(flag < 3){
            msgBox.setText("No se encontraron al menos 3 disparos efectivos");
            msgBox.exec();
        }
}

void MainWindow::DisparoDefensivo(int Do, int Dd, int rd)
{
    int flag = 0;
    float e = 0;
    float Vxo,Vy0,xf,yf;
    int V0o = 0;
    int t = 0;
    int angulo = 0;
    for(V0o = 0;V0o > -500; V0o+=5){
        for(angulo = 180; angulo > 90; angulo--){
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

void MainWindow::DisparoDefensivo2(int anguloo, int vo0)
{
    int flag = 0;
    float Vxo,Vy0,xf,yf;
    int V0o = 0;
    int t = 0;
    int angulo = 0;
    for(V0o = 0;V0o < 500; V0o+=5){
        for(angulo = 0; angulo < 90; angulo++){
            Vxo = V0o*cos((angulo+90)*pi/180);
            Vy0 = V0o*sin((angulo+90)*pi/180);
            xf = 0.0;
            yf = 0.0;
            for(t = 0; ; t++){
                xf = caniones.at(1)->getPosx()+Vxo*t;
                yf = (v_limit-caniones.at(1)->getPosy()) + Vy0*t -(0.5*G*t*t);
                if(Impacto(xf,yf,10,YO,R)){
                    qDebug()<<xf<<yf<<10<<YO<<R;
                    Disparos.push_back(new Proyectil_Graph(XD,YD,angulo+90,V0o,XD,2));
                    scene->addItem(Disparos.back());
                    Disparos.push_back(new Proyectil_Graph(XD,YD,angulo+90,V0o,XD,4));
                    scene->addItem(Disparos.back());
                    flag += 1;
                    V0o += 50;
                    break;
                }
                if(yf < 0 || xf>XD+R){
                    break;
                }
            }
            if(flag == 3) break;

        }
        if(flag == 3) break;
    }
    if(flag < 3){
        msgBox.setText("No se encontraron al menos 3 disparos efectivos");
        msgBox.exec();
    }
}

void MainWindow::DisparoDefensivo3(int DO, int DD, int anguloo, int vo0)
{
    int flag = 0;
    bool flag2 = 0;
    float x2,y2;
    float aux,auy, xf,yf;
    float Vxo,Vy0, Vxoo,Vyoo;
    int V0o = 0;
    float t = 2.5;
    Vxoo = vo0*cos((anguloo)*pi/180);
    Vyoo = vo0*sin((anguloo)*pi/180);
    for(V0o = 0; ; V0o +=5){
        for(int angulo = 0; angulo < 90; angulo++){
            Vxo = V0o*cos((angulo+90)*pi/180);
            Vy0 = V0o*sin((angulo+90)*pi/180);
            xf = 0.0;
            yf = 0.0;
            x2 = 0.0;
            y2 = 0.0;
            for(t = 0; ; t++){
                x2 = Vxoo*(t);
                y2 = DO.getY0() + Vyoo*(t) -(0.5*G*(t)*(t));
                xf = DD.getX0()+Vxo*t;
                yf = DD.getY0() + Vy0*t -(0.5*G*t*t);
                for(int t2 = t; ;t2++){
                    aux = DD.getX0()+Vxo*t2;
                    auy = DD.getY0() + Vy0*t2 -(0.5*G*t2*t2);
                    if(sqrt(pow((DO.getX0() - aux),2)+pow((DO.getY0() - auy),2)) < DD.getD0()){
                        flag2 = 1;
                        break;
                    }
                    if(auy < 0){
                        break;
                    }
                }
                if(flag2){
                    flag2 = 0;
                    break;
                }
                if(sqrt(pow((DD.getX0() - x2),2)+pow((DD.getY0() - y2),2)) < DO.getD0()){
                    break;
                }
                if(sqrt(pow((x2 - xf),2)+pow((y2 - yf),2)) < DD.getD0()){
                    if(yf<0) yf = 0;
                    flag += 1;
                    cout << "Disparo numero " << flag << endl;
                    ImprimirResultados(anguloo,vo0,x2,y2,t);
                    cout << "_________________________________"<<endl;
                    ImprimirResultados(angulo, V0o, xf, yf, t);
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
        cout << "No impacto en los disparos esperados"<< endl;
    }
}

void MainWindow::DisparoOfensivo1(int DO, int DD, int anguloo, int vo0, int angulod, int vd0)
{

}

void MainWindow::Creacion_caniones()
{
    //Caniones
    //canion ofensivo
    caniones.push_back(new Canion(10,v_limit-ui->YO->value(),0,0,ui->YD->value()));
    scene->addItem(caniones.back());
    //canion defensivo
    caniones.push_back(new Canion(ui->XD->value(),ui->YD->value(),1,0,ui->YD->value()));//Organizar el spinbox
    scene->addItem(caniones.back());
    //Circulo de rango de daño
    //Rango ofensivo
    caniones.push_back(new Canion(10,ui->YO->value(),2,0.025,ui->YD->value()));//Organizar el spinbox
    scene->addItem(caniones.back());
    //Rango defensivo
    caniones.push_back(new Canion(ui->XD->value(),ui->YD->value(),3,0.05,ui->YD->value()));//Organizar el spinbox
    scene->addItem(caniones.back());
}

bool MainWindow::Verificacion_impacto(int b, int rd)
{
    if (Proyectiles.at(b)->collidesWithItem(caniones.at(rd))){
        return true;
    }
    return false;
}

void MainWindow::move()
{
    for(int i=0;i<Proyectiles.size();i++){
        Proyectiles.at(i)->actualizar(v_limit);
    }
}


void MainWindow::on_Punto1_clicked()
{
    msgBox.setText("Generar disparos ofensivos que comprometan la integridad del cañón defensivo.");
    msgBox.exec();
    Creacion_caniones();
    ui->Iniciar->show();
    punto = 1;
}

void MainWindow::on_Punto2_clicked()
{
    msgBox.setText("Generar disparos defensivos que comprometan la integridad del cañón ofensivo.");
    msgBox.exec();
    Creacion_caniones();
    ui->Iniciar->show();
    punto = 2;
}

void MainWindow::on_Punto3_clicked()
{
    msgBox.setText("Dado un disparo ofensivo, generar disparos defensivos que impida que "
                   "el cañón defensivo sea destruido sin importar si el cañón ofensivo pueda ser destruido.");
    msgBox.exec();
    Creacion_caniones();
    ui->TEXTOAO->show();
    ui->TEXTOVO->show();
    ui->AnguloO->show();
    ui->VelocidadO->show();
    ui->Iniciar->show();
    punto = 3;
}

void MainWindow::on_Punto4_clicked()
{
    msgBox.setText("Dado un disparo ofensivo, generar disparo defensivos que impidan que los cañones "
                   "defensivo y ofensivo puedan ser destruidos.");
    msgBox.exec();
    Creacion_caniones();
    ui->TEXTOAO->show();
    ui->TEXTOVO->show();
    ui->AnguloO->show();
    ui->VelocidadO->show();
    ui->Iniciar->show();
    punto = 4;
}

void MainWindow::on_Punto5_clicked()
{
    msgBox.setText("Dado un disparo ofensivo efectivo y un disparo defensivo que comprometa la "
                   "efectividad del ataque ofensivo, generar disparos que neutralicen el ataque defensivo "
                   "y permitan que el ataque ofensivo sea efectivo.");
    msgBox.exec();
    Creacion_caniones();
    ui->TEXTOAO->show();
    ui->TEXTOVO->show();
    ui->AnguloO->show();
    ui->VelocidadO->show();
    ui->TEXTOAD->show();
    ui->TEXTOVD->show();
    ui->AnguloD->show();
    ui->VelocidadD->show();
    ui->Iniciar->show();
    punto = 5;
}

void MainWindow::on_Iniciar_clicked()
{
    if(punto==1){
            DisparoOfensivo(caniones.at(1)->getPosx(),v_limit-caniones.at(1)->getPosy(),caniones.at(0)->getR());
            timer->start(200);
        }
}
