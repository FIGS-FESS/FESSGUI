// THIS Header
#include "flywheel.h"

// Custom Libraries
#include "commands.h"

Flywheel::Flywheel(Interface *inter)
{
   interface = inter;
   //setDefaults();
}

Flywheel::~Flywheel()
{}

// Setters

void Flywheel::setV(float x)
{
    interface->push(COMMAND_SET_V);
    interface->push(x);
}

void Flywheel::setA(float x)
{
    interface->push(COMMAND_SET_A);
    interface->push(x);
}

void Flywheel::setJ(float x)
{
    interface->push(COMMAND_SET_J);
    interface->push(x);
}

void Flywheel::setVA(float x, float y)
{
    interface->push(COMMAND_SET_VA);
    interface->push(x);
    interface->push(y);
}

void Flywheel::setVJ(float x, float y)
{
    interface->push(COMMAND_SET_VJ);
    interface->push(x);
    interface->push(y);
}

void Flywheel::setAJ(float x, float y)
{
    interface->push(COMMAND_SET_AJ);
    interface->push(x);
    interface->push(y);
}

void Flywheel::setVAJ(float x, float y, float z)
{
    interface->push(COMMAND_SET_VAJ);
    interface->push(x);
    interface->push(y);
    interface->push(z);
}

// Getters

float Flywheel::getV()
{
    sync();

    float val = vel.front();

    if (!(vel.empty()-1))
    {
        vel.pop();
    }

    return val;
}

float Flywheel::getA()
{
    sync();

    float val = acc.front();

    if (!(acc.empty()-1))
    {
        acc.pop();
    }

    return val;
}

float Flywheel::getJ()
{
    sync();

    float val = jer.front();

    if (!(jer.empty()-1))
    {
        jer.pop();
    }

    return val;
}

float Flywheel::getLDX()
{
    sync();

    float val = ldx.front();

    if (!(ldx.empty()-1))
    {
        ldx.pop();
    }

    return val;
}

float Flywheel::getLDY()
{
    sync();

    float val = ldy.front();

    if (!(ldy.empty()-1))
    {
        ldy.pop();
    }

    return val;
}

float Flywheel::getUPX()
{
    sync();

    float val = udx.front();

    if (!(udx.empty()-1))
    {
        udx.pop();
    }

    return val;
}

float Flywheel::getUPY()
{
    sync();

    float val = udy.front();

    if (!(udy.empty()-1))
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
    char cod = 1;
    char len = 1;

    while(cod)
    {
        cod = interface->pop();
        len = (cod >> 5);
        cod = cod & 0x1F;

        switch(cod)
        {
            case 0x10: // Emergency Stop
            {
                break;
            }

            case 0x11: // FIFO Full
            {
                break;
            }

            case 0x19: // Velocity
            {
                for (int i = 0; i<len; i++)
                {
                    vel.push(getData());
                }
                break;
            }

            case 0x1A: // Acceleration
            {
                for (int i = 0; i<len; i++)
                {
                    acc.push(getData());
                }
                break;
            }

            case 0x1B: // Jerk
            {
                for (int i = 0; i<len; i++)
                {
                    jer.push(getData());
                }
                break;
            }

            case 0x1C: // Lower Displacement
            {
                for (int i = 0; i<len; i++)
                {
                    ldx.push(getData());
                    ldy.push(getData());
                }
                break;
            }

            case 0x1D: // Upper Displacement
            {
                for (int i = 0; i<len; i++)
                {
                    udx.push(getData());
                    udy.push(getData());
                }
                break;
            }

            case 0x1E:  // All
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

    return *reinterpret_cast<float *>(&val);
}
