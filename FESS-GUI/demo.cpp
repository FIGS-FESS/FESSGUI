// C/C++ Libraries
#include <cmath>

// Custom Libraries
#include "demo.h"
#include "commands.h"


float derivative(float value, float prev)
{
    return value-prev;
}

Demo::Demo()
{
    type = RANDOM;
    ve_rate = 0.1;
    key = 0;
}

void Demo::sync()
{
//---------------------------------------------------------------------
// Command Interpertation
//---------------------------------------------------------------------

    bool loop = true;

    while(!emptyTX() && loop)
    {
        char val = popTX();

        switch(val)
        {
            case COMMAND_SET_EMER_STOP: // Emergency Stop
            {
                loop = false;
                type = STOP;
                pushRXChar(COMMAND_ERR_EMER_STOP);
                break;
            }

            default: // Error: Unknown Commands
            {
                loop = false;
                flushTX();
                break;
            }
        }
    }

//---------------------------------------------------------------------
// Value Generation
//---------------------------------------------------------------------

    switch(type)
    {
        case RANDOM:
        {
            vel = sin(key*1.6+cos(key*1.7)*2)*10 + sin(key*1.2+0.56)*20 + 26;
            acc = derivative(vel,prev_vel);
            jer = derivative(acc,prev_acc);
            break;
        }

        case STOP:
        {
            if ((ve_rate > vel) && (vel > -ve_rate))
            {
                vel = 0;
            }
            else if (vel > 0)
            {
                vel -= ve_rate;
            }
            else
            {
                vel += ve_rate;
            }

            acc = derivative(vel,prev_vel);
            jer = derivative(acc,prev_acc);

            break;
        }

        case COMMAND:
        {

        }
    }

    position += vel;

    udx = 2*cos(key) - cos(2*key);
    udy = 2*sin(key) - sin(2*key);
    ldx = 2*cos(key + 0.1) - cos(2*key + 0.1);
    ldy = 2*sin(key + 0.1) - sin(2*key + 0.1);
    rpx = sin(position/1000);
    rpy = cos(position/1000);

    key += 0.01;
    prev_vel = vel;
    prev_acc = acc;

//---------------------------------------------------------------------
// Data Broadcasting
//---------------------------------------------------------------------

    pushRXChar(COMMAND_RES_ALLD_FLOA);
    pushRXFloat(vel);
    pushRXFloat(acc);
    pushRXFloat(jer);
    pushRXFloat(ldx);
    pushRXFloat(ldy);
    pushRXFloat(udx);
    pushRXFloat(udy);
    pushRXFloat(rpx);
    pushRXFloat(rpy);
}

void Demo::startDevice(){}
void Demo::stopDevice(){}
