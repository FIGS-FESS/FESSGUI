#include <QtGui>
#include <QApplication>

// THIS Header
#include "flywheel.h"

// Custom Libraries
#include "commands.h"

Flywheel::Flywheel(Interface *inter)
{
   interface = inter;
   setDefaults();
}

Flywheel::~Flywheel()
{}

// Setters

void Flywheel::setV(float x)
{
    interface->pushChar(COMMAND_SET_VELO_FLOA);
    interface->pushFloat(x);
}

void Flywheel::setA(float x)
{
    interface->pushChar(COMMAND_SET_ACCE_FLOA);
    interface->pushFloat(x);
}

void Flywheel::setJ(float x)
{
    interface->pushChar(COMMAND_SET_JERK_FLOA);
    interface->pushFloat(x);
}

void Flywheel::setVAJ(float x, float y, float z)
{
    interface->pushChar(COMMAND_SET_ALLD_FLOA);
    interface->pushFloat(x);
    interface->pushFloat(y);
    interface->pushFloat(z);
}

// Getters

float Flywheel::getV()
{
    float val = vel.front();

    if (!vel.empty())
    {
        vel.pop();
    }

    return val;
}

float Flywheel::getA()
{
    float val = acc.front();

    if (!acc.empty())
    {
        acc.pop();
    }

    return val;
}

float Flywheel::getJ()
{
    float val = jer.front();

    if (!jer.empty())
    {
        jer.pop();
    }

    return val;
}

float Flywheel::getLDX()
{
    float val = ldx.front();

    if (!ldx.empty())
    {
        ldx.pop();
    }

    return val;
}

float Flywheel::getLDY()
{
    float val = ldy.front();

    if (!ldy.empty())
    {
        ldy.pop();
    }

    return val;
}

float Flywheel::getUPX()
{
    float val = udx.front();

    if (!udx.empty())
    {
        udx.pop();
    }

    return val;
}

float Flywheel::getUPY()
{
    float val = udy.front();

    if (!udy.empty())
    {
        udy.pop();
    }

    return val;
}

// Private Setters

void Flywheel::setDefaults()
{
    vel.push(0.0);
    acc.push(0.0);
    jer.push(0.0);
    udx.push(0.0);
    udy.push(0.0);
    ldx.push(0.0);
    ldy.push(0.0);
}

void Flywheel::sync()
{
    bool loop = true;
    interface->sync();

    while(!interface->empty() && loop)
    {
        switch(interface->pop())
        {
            case COMMAND_ERR_EMER_STOP: // Emergency Stop
            {
                loop = false;
                break;
            }

            case COMMAND_ERR_FIFO_FULL: // FIFO Full
            {
                loop = false;
                break;
            }

            case COMMAND_RES_VELO_FLOA: // Velocity
            {
                vel.push(getData());
                break;
            }

            case COMMAND_RES_ACCE_FLOA: // Acceleration
            {
                acc.push(getData());
                break;
            }

            case COMMAND_RES_JERK_FLOA: // Jerk
            {
                jer.push(getData());
                break;
            }

            case COMMAND_RES_LOWE_DISP: // Lower Displacement
            {
                ldx.push(getData());
                ldy.push(getData());
                break;
            }

            case COMMAND_RES_UPPE_DISP: // Upper Displacement
            {
                udx.push(getData());
                udy.push(getData());
                break;
            }

            case COMMAND_RES_ALLD_FLOA:  // All
            {
                vel.push(getData());
                acc.push(getData());
                jer.push(getData());
                ldx.push(getData());
                ldy.push(getData());
                udx.push(getData());
                udy.push(getData());
                break;
            }

            default: // Error: Unknown Commands
            {
                loop = false;
                interface->flush();
                break;
            }
        }
    }
}

float Flywheel::getData()
{
    unsigned char val[4];
    val[0] = interface->pop();
    val[1] = interface->pop();
    val[2] = interface->pop();
    val[3] = interface->pop();

    qDebug() << val[0]
             << " "
             << val[1]
             << " "
             << val[2]
             << " "
             << val[3]
             << "\n";

    return *reinterpret_cast<float*>(&val);
}
