// C/C++ Libraries
#include <cmath>

// Custom Libraries
#include "commands.h"
#include "demodevice.h"
#include "conversions.h"


DemoDevice::DemoDevice()
{
    type = RANDOM;
    ve_rate = 0.1;
    key = 0;
}

void DemoDevice::sync()
{
//---------------------------------------------------------------------
// Command Interpertation
//---------------------------------------------------------------------

    bool loop = true;

    while(!tx.empty() && loop)
    {
        char val = tx.popByte();

        switch(val)
        {
            case ICM_EMERGENCY_STOP: // Emergency Stop
            {
                loop = false;
                type = STOP;
                //rx.pushFrontChar(COMMAND_ERR_EMER_STOP);
                break;
            }

            default: // Error: Unknown Commands
            {
                loop = false;
                tx.flush();
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
    rpx = sin(position/100);
    rpy = cos(position/100);

    key += 0.01;
    prev_vel = vel;
    prev_acc = acc;

//---------------------------------------------------------------------
// Data Broadcasting
//---------------------------------------------------------------------

    rx.pushByte(IDM_SEND_VELOCITY);
    rx.pushFloat(vel);
    rx.pushByte(CDM_SEND_VELOCITY);

    rx.pushByte(IDM_SEND_ACCELERATION);
    rx.pushFloat(acc);
    rx.pushByte(CDM_SEND_ACCELERATION);

    rx.pushByte(IDM_SEND_JERK);
    rx.pushFloat(jer);
    rx.pushByte(CDM_SEND_JERK);

    rx.pushByte(IDM_SEND_LOWER_DISPLACEMENT_X);
    rx.pushFloat(ldx);
    rx.pushByte(CDM_SEND_LOWER_DISPLACEMENT_X);

    rx.pushByte(IDM_SEND_LOWER_DISPLACEMENT_Y);
    rx.pushFloat(ldy);
    rx.pushByte(CDM_SEND_LOWER_DISPLACEMENT_Y);

    rx.pushByte(IDM_SEND_UPPER_DISPLACEMENT_X);
    rx.pushFloat(udx);
    rx.pushByte(CDM_SEND_UPPER_DISPLACEMENT_X);

    rx.pushByte(IDM_SEND_UPPER_DISPLACEMENT_Y);
    rx.pushFloat(udy);
    rx.pushByte(CDM_SEND_UPPER_DISPLACEMENT_Y);

    rx.pushByte(IDM_SEND_ROTATIONAL_POSITION_X);
    rx.pushFloat(rpx);
    rx.pushByte(CDM_SEND_ROTATIONAL_POSITION_X);

    rx.pushByte(IDM_SEND_ROTATIONAL_POSITION_Y);
    rx.pushFloat(rpy);
    rx.pushByte(CDM_SEND_ROTATIONAL_POSITION_Y);
}

//--------------------------------------------------------------------
// Interface Overedload Functions
//--------------------------------------------------------------------

void DemoDevice::startDevice()
{
}

void DemoDevice::stopDevice()
{
}

void DemoDevice::setDefaults()
{
}

flybyte DemoDevice::popCommand()
{
    return rx.popByte();
}

void DemoDevice::pushInt(int val)
{
    tx.pushInt(val);
}

void DemoDevice::pushFloat(float val)
{
    tx.pushFloat(val);
}

void DemoDevice::pushCommand(flybyte byte)
{
    tx.pushByte(byte);
}

void DemoDevice::pushCommandImmediate(flybyte byte)
{
    tx.pushByteFront(byte);
}


void DemoDevice::flush()
{
    rx.flush();
}

bool DemoDevice::empty()
{
    return rx.empty();
}
