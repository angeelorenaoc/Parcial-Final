#include "proyectil_grafico.h"

Proyectil_grafico::Proyectil_grafico(float px, float py, float ang, float v, int id_, float d_)
{
    float posx,posy,r;
    id = id_;
    posx = px;
    posy = py;
    setPos(posx,posy);
    d=d_-30;//Distancia entre los caniones
    /* El id es usado para identificar si lo que debe graficarse es un rango de danio o la bala.
     * Además tambien se usa para saber cuál es el rango de danio especifico y a qué canion pertenece la bala*/
    if(id == 0 || id == 1)
        r = 2;
    else if (id == 2)
        r = 0.05*d;
    else if (id==3)
        r=0.025*d;
    else
        r = 0.005*d;
    //Se crea un instacia de la clase bala_parabolica
    bala = new Proyectil(posx,posy,ang,v,r);
}

void Proyectil_grafico::actualizar(float v_limit)
{
    //Se actualiza la posicion de la bala en la pantalla
    bala->ActualizarPosicion();
    setPos(bala->getPx(),v_limit-bala->getPy());
}

Proyectil_grafico::~Proyectil_grafico()
{
    delete bala;
}

QRectF Proyectil_grafico::boundingRect() const
{
    return QRectF(-bala->getR(),-bala->getR(),2*bala->getR(),2*bala->getR());
}

void Proyectil_grafico::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (id==2 || id == 4)
        painter->setBrush(Qt::darkMagenta);
    else if (id == 3)
        painter->setBrush(Qt::darkBlue);
    painter->drawEllipse(boundingRect());
}

int Proyectil_grafico::getId() const
{
    return id;
}

void Proyectil_grafico::setId(int value)
{
    id = value;
}

Proyectil *Proyectil_grafico::getBala() const
{
    return bala;
}
