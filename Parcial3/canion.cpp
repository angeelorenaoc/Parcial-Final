#include "canion.h"

float Canion::getR() const
{
    return r;
}

void Canion::setR(float value)
{
    r = value;
}

Canion::Canion(float px_, float py_, int id_, float rd, float d_)
{
    id =id_;
    rango=rd;
    distancia = d_;
    if (id == 0 || id ==1)
        r=10;
    else
        r = rango*distancia;
    if (id == 0 || id == 2){
        posx=0;
    }
    else
        posx = px_;
    posy = py_;
    setPos(posx,posy);
}

QRectF Canion::boundingRect() const
{
    return QRectF(-r,-r,2*r,2*r);
}

void Canion::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (id==0)
        painter->setBrush(Qt::black);
    else if (id == 1)
        painter->setBrush(Qt::darkBlue);
    else if (id == 2)
        painter->setBrush(Qt::green);
    else if (id == 3)
        painter->setBrush(Qt::cyan);
    painter->drawEllipse(boundingRect());
}

float Canion::getDistancia() const
{
    return distancia;
}

void Canion::setDistancia(float value)
{
    distancia = value;
}

float Canion::getPosx() const
{
    return posx;
}

void Canion::setPosx(float value)
{
    posx = value;
}

float Canion::getPosy() const
{
    return posy;
}

void Canion::setPosy(float value)
{
    posy = value;
}

int Canion::getId() const
{
    return id;
}

void Canion::setId(int value)
{
    id = value;
}

