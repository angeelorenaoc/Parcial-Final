#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <QObject>
#include <math.h>
#include <cmath>
#include <QDebug>

class Proyectil: public QObject
{
    Q_OBJECT
    float px;
    float py;
    float r; //Radio
    float vx;
    float vy;
    float angulo;
    float a;
    float g; //Gravedad
    float v;
    float dt; //Delta de tiempo

public:
    Proyectil(float posx_, float posy_,float a_,float v_);
    ~Proyectil();
    void ActualizarPosicion();
    void CalcularVelocidad();
    float getPx() const;
    void setPx(float value);
    float getPy() const;
    void setPy(float value);
    float getR() const;
    float getAngulo() const;
    void setAngulo(float value);
    void set_vel(float vx_,float vy_, float px_,float py_);
    float getV() const;
};

#endif // PROYECTIL_H
