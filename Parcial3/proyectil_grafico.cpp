#include "proyectil_grafico.h"

Proyectil_grafico::Proyectil_grafico(float px, float py, float ang, float v, int id_, float d_)
{
    float posx,posy,r;
    id = id_;
    posx = px;
    posy = py;
    setPos(posx,posy);
    d=d_;
    if(id == 0 || id == 1)
        r = 1;
    else if (id == 2)
        r = 0.05*d;
    else
        r=0.025*d;

    //Se crea un instacia de la clase bala_parabolica
    bala = new Proyectil(posx,posy,ang,v);
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
    painter->drawEllipse(boundingRect());
    if (id==0)
        painter->setBrush(Qt::black);
    else
        painter->setBrush(Qt::darkBlue);
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
