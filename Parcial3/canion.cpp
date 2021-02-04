#include "canion.h"

Canion::Canion(float px_, float py_, int id_)
{
    id =id_;
    if (id == 0){
        posx=0;
    }
    else
        posx = px_;
    posy = py_;
}

QRectF Canion::boundingRect() const
{
    return QRectF(-r,-r,2*r,2*r);
}

void Canion::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawEllipse(boundingRect());
    if (id==0)
        painter->setBrush(Qt::black);
    else
        painter->setBrush(Qt::darkBlue);
}

float Canion::getD() const
{
    return d;
}

void Canion::setD(float value)
{
    d = value;
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

