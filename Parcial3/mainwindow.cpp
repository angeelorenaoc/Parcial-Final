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
    Camino = new QTimer;
    connect(Camino,SIGNAL(timeout()),this,SLOT(ruta()));
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

void MainWindow::DisparoOfensivo()
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
                xf = caniones.at(0)->getPosx()+Vxo*t;
                yf = (v_limit-caniones.at(0)->getPosy()) + Vy0*t -(0.5*G*t*t);
                if(Impacto(xf,yf,caniones.at(1)->getPosx(),caniones.at(1)->getPosy(),caniones.at(2)->getR())){
                    qDebug() << "Se crea el disparo";
                    Proyectiles.push_back(new Proyectil_grafico(caniones.at(0)->getPosx(),v_limit-caniones.at(0)->getPosy(),angulo,V0o,2,caniones.at(1)->getPosx()));
                    scene->addItem(Proyectiles.back());
                    Proyectiles.push_back(new Proyectil_grafico(caniones.at(0)->getPosx(),v_limit-caniones.at(0)->getPosy(),angulo,V0o,0,caniones.at(1)->getPosx()));
                    scene->addItem(Proyectiles.back());
                    flag += 1;
                    V0o += 50;
                    break;
                }
                if(yf < 0 || xf>caniones.at(1)->getPosx()+caniones.at(3)->getR()){
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

void MainWindow::DisparoDefensivo()
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
                if(Impacto(xf,yf,caniones.at(0)->getPosx(),caniones.at(0)->getPosy(),caniones.at(2)->getR())){
                    Proyectiles.push_back(new Proyectil_grafico(caniones.at(1)->getPosx(),v_limit-caniones.at(1)->getPosy(),angulo+90,V0o,3,caniones.at(1)->getPosx()));
                    scene->addItem(Proyectiles.back());
                    Proyectiles.push_back(new Proyectil_grafico(caniones.at(1)->getPosx(),v_limit-caniones.at(1)->getPosy(),angulo+90,V0o,1,caniones.at(1)->getPosx()));
                    scene->addItem(Proyectiles.back());
                    flag += 1;
                    V0o += 50;
                    break;
                }
                if(yf < 0 || xf>caniones.at(1)->getPosx()+caniones.at(2)->getR()){
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

void MainWindow::DisparoDefensivo2(int anguloo, int vo0)
{
    int flag = 0;
    float xf,yf, x2,y2;
    float Vxo,Vy0, Vxoo,Vyoo;
    float aux,auy;
    bool flag2;
    int V0o = 0;
    int Time = 2;
    float angulo = 0;
    Vxoo = vo0*cos((anguloo)*pi/180);
    Vyoo = vo0*sin((anguloo)*pi/180);
    for(V0o = 0;V0o<500; V0o +=5){
        for(angulo = 0; angulo < 90; angulo++){
            Vxo = V0o*cos((angulo+90)*pi/180);
            Vy0 = V0o*sin((angulo+90)*pi/180);
            xf = 0.0;
            yf = 0.0;
            x2 = 0.0;
            y2 = 0.0;
            for(int t=0; ; t++){
                xf = caniones.at(1)->getPosx()+Vxo*t;
                yf = (v_limit-caniones.at(1)->getPosy()) + Vy0*t -(0.5*G*t*t);
                x2 = caniones.at(0)->getPosx()+Vxoo*(t+Time);
                y2 = (v_limit-caniones.at(0)->getPosy()) + Vyoo*(t+Time) -(0.5*G*(t+Time)*(t+Time));
                for(int t2 = t; ;t2++){
                    aux = caniones.at(1)->getPosx()+Vxo*t2;
                    auy = caniones.at(1)->getPosy() + Vy0*t2 -(0.5*G*t2*t2);
                    if(Impacto(x2,y2,aux,auy,caniones.at(2)->getR())){
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
                if(Impacto(xf,yf,x2,y2,caniones.at(2)->getR())){
                    Proyectiles.push_back(new Proyectil_grafico(caniones.at(1)->getPosx(),v_limit-caniones.at(1)->getPosy(),angulo+90,V0o,1,caniones.at(1)->getPosx()));
                    scene->addItem(Proyectiles.back());
                    Proyectiles.push_back(new Proyectil_grafico(caniones.at(1)->getPosx(),v_limit-caniones.at(1)->getPosy(),angulo+90,V0o,3,caniones.at(1)->getPosx()));
                    scene->addItem(Proyectiles.back());
                    flag += 1;
                    V0o += 50;
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
    if(flag < 3){
        msgBox.setText("No se encontraron al menos 3 disparos efectivos");
        msgBox.exec();
    }

}

void MainWindow::DisparoDefensivo3(int anguloo, int vo0)
{
//    int flag = 0;
//    bool flag2 = 0;
//    float x2,y2;
//    float aux,auy, xf,yf;
//    float Vxo,Vy0, Vxoo,Vyoo;
//    int V0o = 0;
//    float t = 2.5;
//    Vxoo = vo0*cos((anguloo)*pi/180);
//    Vyoo = vo0*sin((anguloo)*pi/180);
//    for(V0o = 0; ; V0o +=5){
//        for(int angulo = 0; angulo < 90; angulo++){
//            Vxo = V0o*cos((angulo+90)*pi/180);
//            Vy0 = V0o*sin((angulo+90)*pi/180);
//            xf = 0.0;
//            yf = 0.0;
//            x2 = 0.0;
//            y2 = 0.0;
//            for(t = 0; ; t++){
//                x2 = Vxoo*(t);
//                y2 = DO.getY0() + Vyoo*(t) -(0.5*G*(t)*(t));
//                xf = DD.getX0()+Vxo*t;
//                yf = DD.getY0() + Vy0*t -(0.5*G*t*t);
//                for(int t2 = t; ;t2++){
//                    aux = DD.getX0()+Vxo*t2;
//                    auy = DD.getY0() + Vy0*t2 -(0.5*G*t2*t2);
//                    if(sqrt(pow((DO.getX0() - aux),2)+pow((DO.getY0() - auy),2)) < DD.getD0()){
//                        flag2 = 1;
//                        break;
//                    }
//                    if(auy < 0){
//                        break;
//                    }
//                }
//                if(flag2){
//                    flag2 = 0;
//                    break;
//                }
//                if(sqrt(pow((DD.getX0() - x2),2)+pow((DD.getY0() - y2),2)) < DO.getD0()){
//                    break;
//                }
//                if(sqrt(pow((x2 - xf),2)+pow((y2 - yf),2)) < DD.getD0()){
//                    if(yf<0) yf = 0;
//                    flag += 1;
//                    cout << "Disparo numero " << flag << endl;
//                    ImprimirResultados(anguloo,vo0,x2,y2,t);
//                    cout << "_________________________________"<<endl;
//                    ImprimirResultados(angulo, V0o, xf, yf, t);
//                    break;
//                }
//                if(yf < 0){
//                    break;
//                }
//            }
//            if(flag == 3) break;

//        }
//        if(flag == 3) break;
//    }
//    if(flag != 3){
//        cout << "No impacto en los disparos esperados"<< endl;
//    }
}

void MainWindow::DisparoOfensivo1(int anguloo, int vo0, int angulod, int vd0)
{
    int flag = 0;
    bool flag2;
    float xf,yf, x,y, x2,y2;
    float aux,auy;
    float Vxo,Vy0, Vxoo,Vyoo,Vxd,Vyd;
    int V0o = 0;
    int Time = 2, time3=3, t2;
    float angulo = 0;
    Vxoo = vo0*cos((anguloo)*pi/180);
    Vyoo = vo0*sin((anguloo)*pi/180);
    Vxd= vd0*cos((angulod+90)*pi/180);
    Vyd= vd0*sin((angulod+90)*pi/180);
    for(V0o = 0;V0o<500; V0o +=5){
        for(angulo = 0; angulo < 90; angulo++){
            Vxo = V0o*cos((angulo)*pi/180);
            Vy0 = V0o*sin((angulo)*pi/180);
            xf = 0.0;
            yf = 0.0;
            x2 = 0.0;
            y2 = 0.0;
            x = 0.0;
            y = 0.0;
            for(int t=0; ; t++){
                x2 = caniones.at(1)->getPosx()+Vxd*t;
                y2 = (v_limit-caniones.at(1)->getPosy()) + Vyd*t -(0.5*G*t*t);
                x = caniones.at(0)->getPosx()+Vxoo*(t+Time);
                y = (v_limit-caniones.at(0)->getPosy()) + Vyoo*(t+Time) -(0.5*G*(t+Time)*(t+Time));
                xf = caniones.at(0)->getPosx()+Vxo*(t+time3);
                yf = (v_limit-caniones.at(0)->getPosy()) + Vy0*(t+time3) -(0.5*G*(t+time3)*(t+time3));

                if(!Impacto(x2,y2,x,y,caniones.at(2)->getR())){
                    for(t2 = t; ;t2++){
                        aux = caniones.at(0)->getPosx()+Vxo*t2;
                        auy = caniones.at(0)->getPosy() + Vy0*t2 -(0.5*G*t2*t2);
                        if(Impacto(x,y,aux,auy,caniones.at(2)->getR())){
                            flag2 = 1;
                            break;
                        }
                        if(flag2){
                            flag2 = 0;
                            break;
                        }
                        if(auy < 0){
                            break;
                        }
                    }
                    if (Impacto(xf,yf,x2,y2,caniones.at(3)->getR())){
                        Proyectiles.push_back(new Proyectil_grafico(caniones.at(0)->getPosx(),v_limit-caniones.at(0)->getPosy(),angulo,V0o,0,caniones.at(1)->getPosx()));
                        scene->addItem(Proyectiles.back());
                        Proyectiles.push_back(new Proyectil_grafico(caniones.at(0)->getPosx(),v_limit-caniones.at(0)->getPosy(),angulo,V0o,4,caniones.at(1)->getPosx()));
                        scene->addItem(Proyectiles.back());
                        flag += 1;
                        V0o += 50;
                        break;
                    }

                }
                if(yf < 0){
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
void MainWindow::ruta()
{
    for(int i=0;i<Proyectiles.size();i++){
        Respaldo.push_back(new Proyectil_grafico(Proyectiles.at(i)->getBala()->getPx(),v_limit-Proyectiles.at(i)->getBala()->getPy(),Proyectiles.at(i)->getBala()->getAngulo(),Proyectiles.at(i)->getBala()->getV(),Proyectiles.at(i)->getId(),caniones.at(1)->getPosx()));
        scene->addItem(Respaldo.back());
    }
}

void MainWindow::Creacion_caniones()
{
    //Caniones
    //canion ofensivo
    caniones.push_back(new Canion(30,v_limit-ui->YO->value(),0,0,ui->YD->value()));
    //canion defensivo
    caniones.push_back(new Canion(ui->XD->value(),v_limit-ui->YD->value(),1,0,ui->YD->value()));//Organizar el spinbox
    //Circulo de rango de daño
    //Rango ofensivo
    caniones.push_back(new Canion(30,v_limit-ui->YO->value(),2,0.025,ui->YD->value()));//Organizar el spinbox
    //Rango defensivo
    caniones.push_back(new Canion(ui->XD->value(),v_limit-ui->YD->value(),3,0.05,ui->YD->value()));//Organizar el spinbox
    for (int i=3; i>=0; i--){
        scene->addItem(caniones.at(i));
    }
    ui->XD->clear();
    ui->YD->clear();
    ui->YO->clear();
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
    scene->clear();
    caniones.clear();
    Proyectiles.clear();
    msgBox.setText("Generar disparos ofensivos que comprometan la integridad del cañón defensivo.");
    msgBox.exec();
    Creacion_caniones();
    ui->Iniciar->show();
    punto = 1;
}

void MainWindow::on_Punto2_clicked()
{
    scene->clear();
    caniones.clear();
    Proyectiles.clear();
    msgBox.setText("Generar disparos defensivos que comprometan la integridad del cañón ofensivo.");
    msgBox.exec();
    Creacion_caniones();
    ui->Iniciar->show();
    punto = 2;
}

void MainWindow::on_Punto3_clicked()
{
    scene->clear();
    caniones.clear();
    Proyectiles.clear();
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
    scene->clear();
    caniones.clear();
    Proyectiles.clear();
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
    scene->clear();
    caniones.clear();
    Proyectiles.clear();
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
    ui->Iniciar->hide();
    if(punto==1){
        DisparoOfensivo();
        timer->start(50);
    }
    else if(punto==2){
        DisparoDefensivo();
        timer->start(50);
    }
    else if(punto==3){
        DisparoDefensivo2(ui->AnguloO->value(),ui->VelocidadO->value());
        Proyectiles.push_back(new Proyectil_grafico(caniones.at(0)->getPosx(),v_limit-caniones.at(0)->getPosy(),ui->AnguloO->value(),ui->VelocidadO->value(),0,caniones.at(1)->getPosx()));
        scene->addItem(Proyectiles.back());
        Proyectiles.push_back(new Proyectil_grafico(caniones.at(0)->getPosx(),v_limit-caniones.at(0)->getPosy(),ui->AnguloO->value(),ui->VelocidadO->value(),2,caniones.at(1)->getPosx()));
        scene->addItem(Proyectiles.back());
        timer->start(100);
    }
    else if (punto == 4){
        DisparoDefensivo3(ui->AnguloO->value(),ui->VelocidadO->value());
        Proyectiles.push_back(new Proyectil_grafico(caniones.at(0)->getPosx(),v_limit-caniones.at(0)->getPosy(),ui->AnguloO->value(),ui->VelocidadO->value(),0,caniones.at(1)->getPosx()));
        scene->addItem(Proyectiles.back());
        Proyectiles.push_back(new Proyectil_grafico(caniones.at(0)->getPosx(),v_limit-caniones.at(0)->getPosy(),ui->AnguloO->value(),ui->VelocidadO->value(),2,caniones.at(1)->getPosx()));
        scene->addItem(Proyectiles.back());
        timer->start(100);
    }
    else if (punto == 5){
        DisparoOfensivo1(ui->AnguloO->value(),ui->VelocidadO->value(), ui->AnguloD->value(), ui->VelocidadD->value());
        Proyectiles.push_back(new Proyectil_grafico(caniones.at(0)->getPosx(),v_limit-caniones.at(0)->getPosy(),ui->AnguloO->value(),ui->VelocidadO->value(),0,caniones.at(1)->getPosx()));
        scene->addItem(Proyectiles.back());
        Proyectiles.push_back(new Proyectil_grafico(caniones.at(0)->getPosx(),v_limit-caniones.at(0)->getPosy(),ui->AnguloO->value(),ui->VelocidadO->value(),2,caniones.at(1)->getPosx()));
        scene->addItem(Proyectiles.back());
        Proyectiles.push_back(new Proyectil_grafico(caniones.at(1)->getPosx(),v_limit-caniones.at(1)->getPosy(),ui->AnguloD->value(),ui->VelocidadD->value(),1,caniones.at(1)->getPosx()));
        scene->addItem(Proyectiles.back());
        Proyectiles.push_back(new Proyectil_grafico(caniones.at(3)->getPosx(),v_limit-caniones.at(3)->getPosy(),ui->AnguloD->value(),ui->VelocidadD->value(),3,caniones.at(1)->getPosx()));
        scene->addItem(Proyectiles.back());
        timer->start(100);
    }
    Camino->start(500);
}
