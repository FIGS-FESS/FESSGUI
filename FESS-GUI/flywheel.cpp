#include "flywheel.h"
#include "serial.h"

Flywheel::Flywheel()
{
    setDefaults();
}

Flywheel::Flywheel(Serial &swsettings)
{
    setDefaults();
    serial = swsettings;
}

Flywheel::~Flywheel()
{}

// Setters

void Flywheel::setV(float vel)
{
    setVP(vel);
}

void Flywheel::setA(float acc)
{
    setAP(acc);
}

void Flywheel::setJ(float jer)
{
    setJP(jer);
}

void Flywheel::setVA(float vel, float acc)
{
    setVAP(vel,acc);
}

void Flywheel::setVJ(float vel, float jer)
{
    setVJP(vel,jer);
}

void Flywheel::setAJ(float acc, float jer)
{
    setAJP(acc,jer);
}

void Flywheel::setVAJ(float vel, float acc, float jer)
{
    setVAJP(vel,acc,jer);
}

// Getters

float Flywheel::getV()
{
    return vel;
}

float Flywheel::getA()
{
    return acc;
}

float Flywheel::getJ()
{
    return jer;
}

float Flywheel::getLDX()
{
    return ldx;
}

float Flywheel::getLDY()
{
    return ldy;
}

float Flywheel::getUPX()
{
    return udx;
}

float Flywheel::getUPY()
{
    return udy;
}

// Private Setters

void Flywheel::setDefaults()
{
    vel = 0.0;
    acc = 0.0;
    jer = 0.0;
    udx = 0.0;
    udy = 0.0;
    ldx = 0.0;
    ldy = 0.0;
}

void Flywheel::setVP(float x)
{
    serial.append(0x29);
    serial.append(((((char)x) & 0x0F) >> 0x0));
    serial.append(((((char)x) & 0xF0) >> 0x8));
}

void Flywheel::setAP(float x)
{
    serial.append(0x2A);
    serial.append(((((char)x) & 0x0F) >> 0x0));
    serial.append(((((char)x) & 0xF0) >> 0x8));
}

void Flywheel::setJP(float x)
{
    serial.append(0x2B);
    serial.append(((((char)x) & 0x0F) >> 0x0));
    serial.append(((((char)x) & 0xF0) >> 0x8));
}

void Flywheel::setVAP(float x, float y)
{
    serial.append(0x2C);
    serial.append(((((char)x) & 0x0F) >> 0x0));
    serial.append(((((char)x) & 0xF0) >> 0x8));
    serial.append(((((char)y) & 0x0F) >> 0x0));
    serial.append(((((char)y) & 0xF0) >> 0x8));
}

void Flywheel::setVJP(float x, float y)
{
    serial.append(0x2D);
    serial.append(((((char)x) & 0x0F) >> 0x0));
    serial.append(((((char)x) & 0xF0) >> 0x8));
    serial.append(((((char)y) & 0x0F) >> 0x0));
    serial.append(((((char)y) & 0xF0) >> 0x8));
}

void Flywheel::setAJP(float x, float y)
{
    serial.append(0x2E);
    serial.append(((((char)x) & 0x0F) >> 0x0));
    serial.append(((((char)x) & 0xF0) >> 0x8));
    serial.append(((((char)y) & 0x0F) >> 0x0));
    serial.append(((((char)y) & 0xF0) >> 0x8));
}

void Flywheel::setVAJP(float x, float y, float z)
{
    serial.append(0x2C);
    serial.append(((((char)x) & 0x0F) >> 0x0));
    serial.append(((((char)x) & 0xF0) >> 0x8));
    serial.append(((((char)y) & 0x0F) >> 0x0));
    serial.append(((((char)y) & 0xF0) >> 0x8));
    serial.append(((((char)z) & 0x0F) >> 0x0));
    serial.append(((((char)z) & 0xF0) >> 0x8));
}
