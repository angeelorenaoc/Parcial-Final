#include "proyectil.h"
#define pi 3.1416

float Proyectil::getV() const
{
    return v;
}

Proyectil::Proyectil(float posx_, float posy_, float a_, float v_)
{
    px =posx_;
    py = posy_;
    r=10;
    angulo = (a_*pi)/180;
    v = v_;
    vx=0;
    vy=0;
    a= 0;
    g = 9.8;
    dt = 0.1;
}

Proyectil::~Proyectil()
{

}

//*******Ecuaciones de movimiento parabolico********
void Proyectil::ActualizarPosicion()
{
    CalcularVelocidad();
    px=px+vx*dt;
    py=py+vy*dt-(0.5*g*dt+dt);
}

void Proyectil::CalcularVelocidad()
{
    vx=v*cos(angulo);
    vy=v*sin(angulo)-g*dt;
    angulo=atan2(vy,vx);
    v=sqrt(pow(vy,2)+pow(vx,2));
}

void Proyectil::set_vel(float vx_, float vy_, float px_, float py_)
{
    vx = vx_;
    vy = vy_;
    px = px_;
    py= py_;
}
//**************************************************

float Proyectil::getPx() const
{
    return px;
}

void Proyectil::setPx(float value)
{
    px = value;
}

float Proyectil::getPy() const
{
    return py;
}

void Proyectil::setPy(float value)
{
    py = value;
}

float Proyectil::getR() const
{
    return r;
}

float Proyectil::getVx() const
{
    return vx;
}

float Proyectil::getVy() const
{
    return vy;
}

float Proyectil::getAngulo() const
{
    return angulo;
}

void Proyectil::setAngulo(float value)
{
    angulo = value;
}

