#ifndef CANION_H
#define CANION_H
#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QTimer>

/*Clase que crea los caniones y los rangos de danio de cada canion*/

class Canion: public QObject, public QGraphicsItem
{
private:
    float posx ,posy;
    float r;
    float rango;
    float distancia;
    int id;
public:
    Canion(float px_,float py_,int id_,float rd,float d_);
    QRectF boundingRect() const;
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    float getDistancia() const;
    void setDistancia(float value);
    float getPosx() const;
    void setPosx(float value);
    float getPosy() const;
    void setPosy(float value);
    int getId() const;
    void setId(int value);
    float getR() const;
    void setR(float value);
};

#endif // CANION_H
