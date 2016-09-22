#include <queue>

#include "flywheel.h"

Flywheel::Flywheel()
{
    setDefaults();
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
    float val = vel.front();

    if (!(vel.empty()-1))
    {
        vel.pop();
    }

    return val;
}

float Flywheel::getA()
{
    float val = acc.front();

    if (!(acc.empty()-1))
    {
        acc.pop();
    }

    return val;
}

float Flywheel::getJ()
{
    float val = jer.front();

    if (!(jer.empty()-1))
    {
        jer.pop();
    }

    return val;
}

float Flywheel::getLDX()
{
    float val = ldx.front();

    if (!(ldx.empty()-1))
    {
        ldx.pop();
    }

    return val;
}

float Flywheel::getLDY()
{
    float val = ldy.front();

    if (!(ldy.empty()-1))
    {
        ldy.pop();
    }

    return val;
}

float Flywheel::getUPX()
{
    float val = udx.front();

    if (!(udx.empty()-1))
    {
        udx.pop();
    }

    return val;
}

float Flywheel::getUPY()
{
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

void Flywheel::setVP(float x)
{
    serial.push(0x29);
    serial.push(((((char)x) & 0x0F) >> 0x0));
    serial.push(((((char)x) & 0xF0) >> 0x8));
}

void Flywheel::setAP(float x)
{
    serial.push(0x2A);
    serial.push(((((char)x) & 0x0F) >> 0x0));
    serial.push(((((char)x) & 0xF0) >> 0x8));
}

void Flywheel::setJP(float x)
{
    serial.push(0x2B);
    serial.push(((((char)x) & 0x0F) >> 0x0));
    serial.push(((((char)x) & 0xF0) >> 0x8));
}

void Flywheel::setVAP(float x, float y)
{
    serial.push(0x2C);
    serial.push(((((char)x) & 0x0F) >> 0x0));
    serial.push(((((char)x) & 0xF0) >> 0x8));
    serial.push(((((char)y) & 0x0F) >> 0x0));
    serial.push(((((char)y) & 0xF0) >> 0x8));
}

void Flywheel::setVJP(float x, float y)
{
    serial.push(0x2D);
    serial.push(((((char)x) & 0x0F) >> 0x0));
    serial.push(((((char)x) & 0xF0) >> 0x8));
    serial.push(((((char)y) & 0x0F) >> 0x0));
    serial.push(((((char)y) & 0xF0) >> 0x8));
}

void Flywheel::setAJP(float x, float y)
{
    serial.push(0x2E);
    serial.push(((((char)x) & 0x0F) >> 0x0));
    serial.push(((((char)x) & 0xF0) >> 0x8));
    serial.push(((((char)y) & 0x0F) >> 0x0));
    serial.push(((((char)y) & 0xF0) >> 0x8));
}

void Flywheel::setVAJP(float x, float y, float z)
{
    serial.push(0x2C);
    serial.push(((((char)x) & 0x0F) >> 0x0));
    serial.push(((((char)x) & 0xF0) >> 0x8));
    serial.push(((((char)y) & 0x0F) >> 0x0));
    serial.push(((((char)y) & 0xF0) >> 0x8));
    serial.push(((((char)z) & 0x0F) >> 0x0));
    serial.push(((((char)z) & 0xF0) >> 0x8));
}

void Flywheel::sync()
{
    char len = serial.pop();
    char cod = serial.pop();

    if ((len << 3) == 8)
    {
        len = len >> 1;

        switch(cod)
        {
            case 0x0: // Emergency Stop
            {
                break;
            }

            case 0x5: // FIFO Full
            {
                break;
            }

            case 0x9: // Velocity
            {
                for (int i = 0; i<len; i++)
                {
                    vel.push((float)((serial.pop() << 8) & (serial.pop())));
                }
                break;
            }

            case 0xA: // Acceleration
            {
                for (int i = 0; i<len; i++)
                {
                    acc.push((float)((serial.pop() << 8) & (serial.pop())));
                }
                break;
            }

            case 0xB: // Jerk
            {
                for (int i = 0; i<len; i++)
                {
                    jer.push((float)((serial.pop() << 8) & (serial.pop())));
                }
                break;
            }

            case 0xC:  // Lower Displacement
            {
                for (int i = 0; i<len; i++)
                {
                    ldx.push((float)((serial.pop() << 8) & (serial.pop())));
                    ldy.push((float)((serial.pop() << 8) & (serial.pop())));
                }
                break;
            }

            case 0xD: // Upper Displacement
            {
                for (int i = 0; i<len; i++)
                {
                    udx.push((float)((serial.pop() << 8) & (serial.pop())));
                    udy.push((float)((serial.pop() << 8) & (serial.pop())));
                }
                break;
            }

            case 0xE:  // All
            {
                vel.push((float)((serial.pop() << 8) & (serial.pop())));
                acc.push((float)((serial.pop() << 8) & (serial.pop())));
                jer.push((float)((serial.pop() << 8) & (serial.pop())));
                ldx.push((float)((serial.pop() << 8) & (serial.pop())));
                ldy.push((float)((serial.pop() << 8) & (serial.pop())));
                udx.push((float)((serial.pop() << 8) & (serial.pop())));
                udy.push((float)((serial.pop() << 8) & (serial.pop())));
                break;
            }

            default: // Error: Unknown Commands
            {
                break;
            }
        }
    }
    else
    {
        // Error: Invalid Data
    }
}
