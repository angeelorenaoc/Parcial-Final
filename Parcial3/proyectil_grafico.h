#ifndef PROYECTIL_GRAFICO_H
#define PROYECTIL_GRAFICO_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <stdlib.h>
#include <time.h>
#include <QObject>
#include <QTimer>
#include <QPixmap>
#include <QDebug>
#include "proyectil.h"

//Parte grafica del proyectil y el rando de este

class Proyectil_grafico: public QObject, public QGraphicsItem
{
public:
    Proyectil_grafico(float px, float py,float ang,float v, int id_, float d_);
    ~Proyectil_grafico();
    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);
    void actualizar(float v_limit);
    int getId() const;
    void setId(int value);
    Proyectil *getBala() const;

private:
    Proyectil *bala;
    float d;
    int id;
};

#endif // PROYECTIL_GRAFICO_H
