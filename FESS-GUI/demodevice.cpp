//QT Libraries
#include <QtGui>
#include <QString>

// C Libraries
#include <cmath>

// Custom Libraries
#include "conversions.h"
#include "demodevice.h"

/*! \brief DemoDevice::DemoDevice Configures a new DemoDevice with its default values.
 */
DemoDevice::DemoDevice()
{    
    setDefaults();
}

/*! \brief DemoDevice::~DemoDevice Provided if needed in the future, currently no functionality.
 */
DemoDevice::~DemoDevice(){}

//---------------------------------------------------------------------
// Command Interpretation
//---------------------------------------------------------------------

/*! \brief DemoDevice::syncRX Is the demo interface's implementation of syncRX.
 * Reacts to the interfaces commands (Only Emergency Stop currently)
 */
void DemoDevice::syncTX()
{
    if(loop == true)
    {
        while(tx.packetsAvailable() == true)
        {
            FlyPacket incomingPacket = tx.popPacket();

            switch(incomingPacket.getCommand())
            {
                case ICM_EMERGENCY_STOP: // Emergency Stop
                {
                    loop = false;
                    type = STOP;
                    FlyPacket emergencyStopAckPacket(CCM_EMERGENCY_STOP,0);
                    rx.pushPacket(emergencyStopAckPacket);
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
    }
}

//---------------------------------------------------------------------
// Value Generation
//---------------------------------------------------------------------


/*! \brief DemoDevice::syncRX Is the demo interface's implementation of syncRX.
 * Generates values for testing and pushes them into the interface's RX Transmit Buffer
 */
void DemoDevice::syncRX()
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

    FlyPacket dataPacket(IDM_SEND_VELOCITY,vel);
    rx.pushPacket(dataPacket);

    FlyPacket dataPacket0(IDM_SEND_ACCELERATION,acc);
    rx.pushPacket(dataPacket0);

    FlyPacket dataPacket1(IDM_SEND_JERK,jer);
    rx.pushPacket(dataPacket1);

    FlyPacket dataPacket2(IDM_SEND_LOWER_DISPLACEMENT_X,ldx);
    rx.pushPacket(dataPacket2);

    FlyPacket dataPacket3(IDM_SEND_LOWER_DISPLACEMENT_Y,ldy);
    rx.pushPacket(dataPacket3);

    FlyPacket dataPacket4(IDM_SEND_UPPER_DISPLACEMENT_X,udx);
    rx.pushPacket(dataPacket4);

    FlyPacket dataPacket5(IDM_SEND_UPPER_DISPLACEMENT_Y,udy);
    rx.pushPacket(dataPacket5);

    FlyPacket dataPacket6(IDM_SEND_ROTATIONAL_POSITION_X,rpx);
    rx.pushPacket(dataPacket6);

    FlyPacket dataPacket7(IDM_SEND_ROTATIONAL_POSITION_Y,rpy);
    rx.pushPacket(dataPacket7);

}

//--------------------------------------------------------------------
// Interface Overload Functions
//--------------------------------------------------------------------

/*! \brief DemoDevice::isReady Is the demo interface's implementation of isReady.
 * Get the status of the demo interface
 *  \return bool (true=Ready, false=Not Ready)
 */
bool DemoDevice::isReady()
{
    return statusReady;
}

/*! \brief DemoDevice::startDevice Is the demo interface's implementation of startDevice.
 * Starts the demo interface and updates status
 *  \return bool (true=Started, false=Not Ready)
 */
bool DemoDevice::startDevice()
{
    statusReady = true;
    return true;
}

/*! \brief DemoDevice::stopDevice Is the demo interface's implementation of stopDevice.
 * Stops the demo interface and updates status
 */
void DemoDevice::stopDevice()
{
    statusReady = false;
}

/*! \brief DemoDevice::stopDevice Is the demo interface's implementation of setDefaults.
 * Sets the serial devices to the default values.
 */
void DemoDevice::setDefaults()
{
    statusReady = false;
    type = RANDOM;
    velRate = 0.1;
    key = 0;
    loop = true;
}

/*! \brief DemoDevice::popByte Is the demo interface's implementation of popByte.
 *  \return FlyByte (From the RX Transmit Buffer).
 */
FlyByte DemoDevice::popByte()
{
    return rx.popByte();
}

/*! \brief DemoDevice::popByte Is the demo interface's implementation of popPacket.
 *  \return FlyPacket (From the RX Transmit Buffer).
 */
FlyPacket DemoDevice::popPacket()
{
    return rx.popPacket();
}

/*! \brief DemoDevice::popByte Is the demo interface's implementation of pushByte.
 *  \param FlyByte (Adds it to the TX Transmit Buffer).
 */
void DemoDevice::pushByte(FlyByte dataByte)
{
    tx.pushByte(dataByte);
}

/*! \brief DemoDevice::popByte Is the demo interface's implementation of pushPacket.
 *  \param FlyPacket (Adds to the TX Transmit Buffer).
 */
void DemoDevice::pushPacket(FlyPacket dataPacket)
{
    tx.pushPacket(dataPacket);
}

/*! \brief DemoDevice::flushRX Is the demo interface's implementation of flushRX.
 *  Empties the RX Transmit Buffer
 */
void DemoDevice::flushRX()
{
    rx.flush();
}

/*! \brief DemoDevice::flushTX Is the demo interface's implementation of flushTX.
 *  Empties the TX Transmit Buffer
 */
void DemoDevice::flushTX()
{
    tx.flush();
}

/*! \brief DemoDevice::empty Is the demo interface's implementation of empty.
 *  \return bool (true=Empty, false=Not Empty)
 */
bool DemoDevice::empty()
{
    return !rx.packetsAvailable();
}

/*! \brief DemoDevice::name Is the demo interface's implementation of name.
 *  \return Qstring ("Demo Device")
 */
QString DemoDevice::name()
{
    return QString("Demo Device");
}
