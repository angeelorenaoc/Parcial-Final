#ifndef CANION_H
#define CANION_H
#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QTimer>

class Canion
{
private:
    float posx ,posy;
    float r=10;
    float d;
    int id;
public:
    Canion(float px_,float py_,int id_);
    QRectF boundingRect() const;
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    float getD() const;
    void setD(float value);
    float getPosx() const;
    void setPosx(float value);
    float getPosy() const;
    void setPosy(float value);
    int getId() const;
    void setId(int value);
};

#endif // CANION_H
