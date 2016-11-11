// Custom Libraries
#include "commands.h"
#include "datatypes.h"
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
    velocityCurrentValue = 0.0;
    accelerationCurrentValue = 0.0;
    jerkCurrentValue = 0.0;

    velocityValueBufferRX = std::queue<float>();
    accelerationValueBufferRX = std::queue<float>();
    jerkValueBufferRX = std::queue<float>();
    upperDisplacementXValueBufferRX = std::queue<float>();
    upperDisplacementYValueBufferRX = std::queue<float>();
    lowerDisplacementXValueBufferRX = std::queue<float>();
    lowerDisplacementYValueBufferRX = std::queue<float>();
    rotationalPositionXValueBufferRX = std::queue<float>();
    rotationalPositionYValueBufferRX = std::queue<float>();

    velocityValueBufferTX = std::queue<float>();
    accelerationValueBufferTX = std::queue<float>();
    jerkValueBufferTX = std::queue<float>();

    velocityValueBufferRX.push(0.0);
    accelerationValueBufferRX.push(0.0);
    jerkValueBufferRX.push(0.0);
    upperDisplacementXValueBufferRX.push(0.0);
    upperDisplacementYValueBufferRX.push(0.0);
    lowerDisplacementXValueBufferRX.push(0.0);
    lowerDisplacementYValueBufferRX.push(0.0);
    rotationalPositionXValueBufferRX.push(0.0);
    rotationalPositionYValueBufferRX.push(0.0);

    velocityValueBufferRXLimit = 64;
    accelerationValueBufferRXLimit = 64;
    jerkValueBufferRXLimit = 64;
    lowerDisplacementXValueBufferRXLimit = 64;
    lowerDisplacementYValueBufferRXLimit = 64;
    upperDisplacementXValueBufferRXLimit = 64;
    upperDisplacementYValueBufferRXLimit = 64;
    rotationalPositionXValueBufferRXLimit = 64;
    rotationalPositionYValueBufferRXLimit = 64;

    velocityValueBufferRXLimit = 4;
    accelerationValueBufferRXLimit = 4;
    jerkValueBufferRXLimit = 4;

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
    setAcceleration(accelerationValue);
    setJerk(jerkValue);
}

void FlywheelOperation::setVelocity(float velocityValue)
{
    velocityValueBufferTX.push(velocityValue);

    if (velocityValueBufferTX.size() > velocityValueBufferTXLimit)
    {
        velocityValueBufferTX.pop();
    }
}

void FlywheelOperation::setAcceleration(float accelerationValue)
{
    accelerationValueBufferTX.push(accelerationValue);

    if (accelerationValueBufferTX.size() > accelerationValueBufferTXLimit)
    {
        accelerationValueBufferTX.pop();
    }
}

void FlywheelOperation::setJerk(float jerkValue)
{
    jerkValueBufferTX.push(jerkValue);

    if (jerkValueBufferTX.size() > jerkValueBufferTXLimit)
    {
        jerkValueBufferTX.pop();
    }
}

float FlywheelOperation::getVelocity()
{
    if (!velocityValueBufferRX.empty())
    {
        velocityCurrentValue = velocityValueBufferRX.front();
        velocityValueBufferRX.pop();
    }

    return velocityCurrentValue;
}

float FlywheelOperation::getAcceleration()
{
    if (!accelerationValueBufferRX.empty())
    {
        accelerationCurrentValue = accelerationValueBufferRX.front();
        accelerationValueBufferRX.pop();
    }

    return accelerationCurrentValue;
}

float FlywheelOperation::getJerk()
{
    if (jerkValueBufferRX.empty())
    {
        jerkCurrentValue = jerkValueBufferRX.front();
        jerkValueBufferRX.pop();
    }

    return jerkCurrentValue;
}

QPointF FlywheelOperation::getUpperDisplacement()
{
    if(!upperDisplacementXValueBufferRX.empty() && !upperDisplacementYValueBufferRX.empty())
    {
        upperDisplacement->setX(upperDisplacementXValueBufferRX.front());
        upperDisplacement->setY(upperDisplacementYValueBufferRX.front());

        upperDisplacementXValueBufferRX.pop();
        upperDisplacementYValueBufferRX.pop();
   }

    return *upperDisplacement;
}

QPointF FlywheelOperation::getLowerDisplacement()
{
    if(!lowerDisplacementXValueBufferRX.empty() && !lowerDisplacementYValueBufferRX.empty())
    {
        lowerDisplacement->setX(lowerDisplacementXValueBufferRX.front());
        lowerDisplacement->setY(lowerDisplacementYValueBufferRX.front());

        lowerDisplacementXValueBufferRX.pop();
        lowerDisplacementYValueBufferRX.pop();
    }
    return *lowerDisplacement;
}

QPointF FlywheelOperation::getRotationalPosition()
{
    if(!rotationalPositionXValueBufferRX.empty() && !rotationalPositionYValueBufferRX.empty())
    {
        rotationalPosition->setX(rotationalPositionXValueBufferRX.front());
        rotationalPosition->setY(rotationalPositionYValueBufferRX.front());

        rotationalPositionXValueBufferRX.pop();
        rotationalPositionYValueBufferRX.pop();
    }

    return *rotationalPosition;
}

void FlywheelOperation::emergencyStop() // Tells the controller to stop and checks to confirm it stopped
{
    emergencyStopActivated = true;
    emergencyStopAcknowlegded = false;
}

void FlywheelOperation::syncTX()
{
    while(velocityValueBufferTX.size() > 0)
    {
        communicationDevice->pushCommand(ICM_SET_VELOCITY);
        communicationDevice->pushFloat(velocityValueBufferTX.front());
        communicationDevice->pushCommand(CCM_SET_VELOCITY);

        velocityValueBufferTX.pop();
    }

    while(accelerationValueBufferTX.size() > 0)
    {
        communicationDevice->pushCommand(ICM_SET_ACCELERATION);
        communicationDevice->pushFloat(accelerationValueBufferTX.front());
        communicationDevice->pushCommand(CCM_SET_ACCELERATION);

        accelerationValueBufferTX.pop();
    }

    while(jerkValueBufferTX.size() > 0)
    {
        communicationDevice->pushCommand(ICM_SET_JERK);
        communicationDevice->pushFloat(jerkValueBufferTX.front());
        communicationDevice->pushCommand(CCM_SET_JERK);

        jerkValueBufferTX.pop();
    }
}

void FlywheelOperation::syncRX()
{
    while(!communicationDevice->empty())
    {
        flybyte rxData = communicationDevice->popCommand();
        flypacket rxPacket = buildFlyPacket(rxData);

        if (rxPacket.packetType == DATA_PACKET)
        {
            switch(rxPacket.dataType)
            {
                case VELOCITY:
                {
                    if (velocityValueBufferRX.size() > velocityValueBufferRXLimit) velocityValueBufferRX.pop();
                    velocityValueBufferRX.push(rxPacket.dataValue);
                    break;
                }

                case ACCELERATION:
                {
                    if (accelerationValueBufferRX.size() > accelerationValueBufferRXLimit) accelerationValueBufferRX.pop();
                    accelerationValueBufferRX.push(rxPacket.dataValue);
                    break;
                }

                case JERK:
                {
                    if (jerkValueBufferRX.size() > jerkValueBufferRXLimit) jerkValueBufferRX.pop();
                    jerkValueBufferRX.push(rxPacket.dataValue);
                    break;
                }

                case LOWER_DISPLACMENT_X:
                {
                    if (lowerDisplacementXValueBufferRX.size() > lowerDisplacementXValueBufferRXLimit) lowerDisplacementXValueBufferRX.pop();
                    lowerDisplacementXValueBufferRX.push(rxPacket.dataValue);
                    break;
                }

                case LOWER_DISPLACMENT_Y:
                {
                    if (lowerDisplacementYValueBufferRX.size() > lowerDisplacementYValueBufferRXLimit) lowerDisplacementYValueBufferRX.pop();
                    lowerDisplacementYValueBufferRX.push(rxPacket.dataValue);
                    break;
                }

                case UPPER_DISPLACMENT_X:
                {
                    if (upperDisplacementXValueBufferRX.size() > upperDisplacementXValueBufferRXLimit) upperDisplacementXValueBufferRX.pop();
                    upperDisplacementXValueBufferRX.push(rxPacket.dataValue);
                    break;
                }

                case UPPER_DISPLACMENT_Y:
                {
                    if (upperDisplacementYValueBufferRX.size() > upperDisplacementYValueBufferRXLimit) upperDisplacementYValueBufferRX.pop();
                    upperDisplacementYValueBufferRX.push(rxPacket.dataValue);
                    break;
                }

                case ROTATIONAL_POSITION_X:
                {
                    if (rotationalPositionXValueBufferRX.size() > rotationalPositionXValueBufferRXLimit) rotationalPositionXValueBufferRX.pop();
                    rotationalPositionXValueBufferRX.push(rxPacket.dataValue);
                    break;
                }

                case ROTATIONAL_POSITION_Y:
                {
                    if (rotationalPositionYValueBufferRX.size() > rotationalPositionYValueBufferRXLimit) rotationalPositionYValueBufferRX.pop();
                    rotationalPositionYValueBufferRX.push(rxPacket.dataValue);
                    break;
                }

                default: break;
            }
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
            communicationDevice->pushCommandImmediate(ICM_EMERGENCY_STOP);
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
