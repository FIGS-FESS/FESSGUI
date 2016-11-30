// Custom Libraries
#include <QtGui>
#include "flypacket.h"
#include "flywheeloperation.h"


FlywheelOperation::FlywheelOperation()
{
    upperDisplacement = new QPointF();
    lowerDisplacement = new QPointF();
    rotationalPosition = new QPointF();
    setDefaults();
}

FlywheelOperation::FlywheelOperation(CommonDeviceInterface* deviceInterface)
{
    upperDisplacement = new QPointF();
    lowerDisplacement = new QPointF();
    rotationalPosition = new QPointF();

    communicationDevice = deviceInterface;
    setDefaults();
}

FlywheelOperation::~FlywheelOperation()
{
    delete upperDisplacement;
    delete lowerDisplacement;
    delete rotationalPosition;
}

void FlywheelOperation::setDefaults()
{
    velocityValue = 0.0;
    accelerationValue = 0.0;
    jerkValue = 0.0;
    lowerDisplacementXValue = 0.0;
    lowerDisplacementYValue = 0.0;
    upperDisplacementXValue = 0.0;
    upperDisplacementYValue = 0.0;
    rotationalPositionXValue = 0.0;
    rotationalPositionYValue = 0.0;

    emergencyRetries = 0;
    emergencyTimeout = 100; //Attempts
    emergencyStopActivated = false;
}

void FlywheelOperation::setInterface(CommonDeviceInterface* deviceInterface)
{
    communicationDevice = deviceInterface;
}

void FlywheelOperation::setMotion(float velocityValue, float accelerationValue, float jerkValue)
{
    setVelocity(velocityValue);
    //setAcceleration(accelerationValue);
    //setJerk(jerkValue);
}

void FlywheelOperation::setVelocity(float velocityValue)
{
    if (communicationDevice->isReady())
    {
        FlyPacket dataPacket(ICM_SET_VELOCITY,velocityValue);
        communicationDevice->pushPacket(dataPacket);
    }
}

void FlywheelOperation::setAcceleration(float accelerationValue)
{
    if (communicationDevice->isReady())
    {
        FlyPacket dataPacket(ICM_SET_ACCELERATION,accelerationValue);
        communicationDevice->pushPacket(dataPacket);
    }
}

void FlywheelOperation::setJerk(float jerkValue)
{
    if (communicationDevice->isReady())
    {
        FlyPacket dataPacket(ICM_SET_JERK,jerkValue);
        communicationDevice->pushPacket(dataPacket);
    }
}

float FlywheelOperation::getVelocity()
{
    return velocityValue;
}

float FlywheelOperation::getAcceleration()
{
    return accelerationValue;
}

float FlywheelOperation::getJerk()
{
    return jerkValue;
}

QPointF FlywheelOperation::getUpperDisplacement()
{
    upperDisplacement->setX(upperDisplacementXValue);
    upperDisplacement->setY(upperDisplacementYValue);

    return *upperDisplacement;
}

QPointF FlywheelOperation::getLowerDisplacement()
{
    lowerDisplacement->setX(lowerDisplacementXValue);
    lowerDisplacement->setY(lowerDisplacementYValue);
    return *lowerDisplacement;
}

QPointF FlywheelOperation::getRotationalPosition()
{
    rotationalPosition->setX(rotationalPositionXValue);
    rotationalPosition->setY(rotationalPositionYValue);
    return *rotationalPosition;
}

void FlywheelOperation::emergencyStop() // Tells the controller to stop and checks to confirm it stopped
{
    emergencyStopActivated = true;
    emergencyStopAcknowlegded = false;
}

void FlywheelOperation::syncTX()
{

}

void FlywheelOperation::syncRX()
{
    while(!communicationDevice->empty())
    {
        FlyPacket rxPacket = communicationDevice->popPacket();

        //qDebug() << rxPacket.getCommand();

        switch(rxPacket.getCommand())
        {
            case IDM_SEND_VELOCITY:
            {
                velocityValue = rxPacket.getFloat();
                break;
            }

            case IDM_SEND_ACCELERATION:
            {
                accelerationValue = rxPacket.getFloat();
                break;
            }

            case IDM_SEND_JERK:
            {
                jerkValue = rxPacket.getFloat();
                break;
            }

            case IDM_SEND_LOWER_DISPLACEMENT_X:
            {
                lowerDisplacementXValue = rxPacket.getFloat();
                break;
            }

            case IDM_SEND_LOWER_DISPLACEMENT_Y:
            {
                lowerDisplacementYValue = rxPacket.getFloat();
                break;
            }

            case IDM_SEND_UPPER_DISPLACEMENT_X:
            {
                upperDisplacementXValue = rxPacket.getFloat();
                break;
            }

            case IDM_SEND_UPPER_DISPLACEMENT_Y:
            {
                upperDisplacementYValue = rxPacket.getFloat();
                break;
            }

            case IDM_SEND_ROTATIONAL_POSITION_X:
            {
                rotationalPositionXValue = rxPacket.getFloat();
                break;
            }

            case IDM_SEND_ROTATIONAL_POSITION_Y:
            {
                rotationalPositionYValue = rxPacket.getFloat();
                break;
            }

            default: break;
        }
    }
}

void FlywheelOperation::sync() // Fix issue where one or more bytes in a data set is missing. Example 1 2 3 arrived 4 is late. Error from overpopping queues
{
    if (communicationDevice->isReady())
    {
        if (emergencyStopActivated == true)
        {
            emergencyRetries = emergencyTimeout;
            //communicationDevice->pushCommandImmediate(ICM_EMERGENCY_STOP);
        }
        else
        {
            syncTX();
            communicationDevice->syncRX();
        }

        communicationDevice->syncTX();
        syncRX();
    }
}
