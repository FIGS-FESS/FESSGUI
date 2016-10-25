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

void Demo::startDevice()
{
}

void Demo::stopDevice()
{
}

void Demo::setDefaults()
{
}

uint8_t Demo::popCommand()
{
    return rx.popByte();
}

void Demo::pushInt(int32_t val)
{
    tx.pushInt(val);
}

void Demo::pushFloat(float val)
{
    tx.pushFloat(val);
}

void Demo::pushCommand(uint8_t byte)
{
    tx.pushByte(byte);
}

void Demo::pushCommandImmediate(uint8_t byte)
{
    tx.pushByteFront(byte);
}


void Demo::flush()
{
    rx.flush();
}

bool Demo::empty()
{
    return rx.empty();
}
