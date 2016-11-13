//QT Libraries
#include <QtGui>
#include <QString>

// C Libraries
#include <cmath>

// Custom Libraries
#include "conversions.h"
#include "demodevice.h"

DemoDevice::DemoDevice()
{    
    setDefaults();
}

DemoDevice::~DemoDevice()
{
}


//---------------------------------------------------------------------
// Command Interpretation
//---------------------------------------------------------------------

void DemoDevice::syncRX()
{
    while(!tx.empty())
    {
        FlyPacket* val = tx.popPacket();

        switch(val->getCommand())
        {
            case ICM_EMERGENCY_STOP: // Emergency Stop
            {
                //loop = false;
                type = STOP;
                //rx.pushByte(CCM_EMERGENCY_STOP);
                break;
            }

            case ICM_SET_VELOCITY:
            {
                qDebug() << "CHANGING VELOCITY";
            }

            default: // Error: Unknown Commands
            {
                //loop = false;
                tx.flush();
                break;
            }
        }
    }
}

//---------------------------------------------------------------------
// Value Generation
//---------------------------------------------------------------------

void DemoDevice::syncTX()
{
    switch(type)
    {
        case RANDOM:
        {
            vel = sin(key*1.6+cos(key*1.7)*2)*10 + sin(key*1.2+0.56)*20 + 26;
            acc = derivative(vel,prevVel);
            jer = derivative(acc,prevAcc);
            break;
        }

        case STOP:
        {
            if ((velRate > vel) && (vel > -velRate))
            {
                vel = 0;
            }
            else if (vel > 0)
            {
                vel -= velRate;
            }
            else
            {
                vel += velRate;
            }

            acc = derivative(vel,prevVel);
            jer = derivative(acc,prevAcc);

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
    prevVel = vel;
    prevAcc = acc;

//---------------------------------------------------------------------
// Data Broadcasting
//---------------------------------------------------------------------

    FlyPacket* dataPacket;

    dataPacket = new FlyPacket(IDM_SEND_VELOCITY,vel);
    rx.pushPacket(dataPacket);

    qDebug()<< dataPacket->getCommand();

    dataPacket = new FlyPacket(IDM_SEND_ACCELERATION,acc);
    rx.pushPacket(dataPacket);

    dataPacket = new FlyPacket(IDM_SEND_JERK,jer);
    rx.pushPacket(dataPacket);

    dataPacket = new FlyPacket(IDM_SEND_LOWER_DISPLACEMENT_X,ldx);
    rx.pushPacket(dataPacket);

    dataPacket = new FlyPacket(IDM_SEND_LOWER_DISPLACEMENT_Y,ldy);
    rx.pushPacket(dataPacket);

    dataPacket = new FlyPacket(IDM_SEND_UPPER_DISPLACEMENT_X,udx);
    rx.pushPacket(dataPacket);

    dataPacket = new FlyPacket(IDM_SEND_UPPER_DISPLACEMENT_Y,udy);
    rx.pushPacket(dataPacket);

    dataPacket = new FlyPacket(IDM_SEND_ROTATIONAL_POSITION_X,rpx);
    rx.pushPacket(dataPacket);

    dataPacket = new FlyPacket(IDM_SEND_ROTATIONAL_POSITION_Y,rpy);
    rx.pushPacket(dataPacket);
}

//--------------------------------------------------------------------
// Interface Overload Functions
//--------------------------------------------------------------------

bool DemoDevice::isReady()
{
    return statusReady;
}

bool DemoDevice::startDevice()
{
    statusReady = true;
    return true;
}

void DemoDevice::stopDevice()
{
    statusReady = false;
}

void DemoDevice::setDefaults()
{
    statusReady = false;
    type = RANDOM;
    velRate = 0.1;
    key = 0;
}

FlyPacket* DemoDevice::popPacket()
{
    return rx.popPacket();
}

void DemoDevice::pushPacket(FlyPacket* dataPacket)
{
    tx.pushPacket(dataPacket);
}

void DemoDevice::pushPacketImmediate(FlyPacket* dataPacket)
{
    tx.pushPacketFront(dataPacket);
}

void DemoDevice::flush()
{
    rx.flush();
}

bool DemoDevice::empty()
{
    return rx.empty();
}

QString DemoDevice::name()
{
    return QString("Demo Device");
}
