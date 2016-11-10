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
    velPrev = 0.0;
    accPrev = 0.0;
    jerPrev = 0.0;

    velBuffer = std::queue<float>();
    accBuffer = std::queue<float>();
    jerBuffer = std::queue<float>();
    udxBuffer = std::queue<float>();
    udyBuffer = std::queue<float>();
    ldxBuffer = std::queue<float>();
    ldyBuffer = std::queue<float>();
    rpxBuffer = std::queue<float>();
    rpyBuffer = std::queue<float>();

    velBuffer.push(0.0);
    accBuffer.push(0.0);
    jerBuffer.push(0.0);
    udxBuffer.push(0.0);
    udyBuffer.push(0.0);
    ldxBuffer.push(0.0);
    ldyBuffer.push(0.0);
    rpxBuffer.push(0.0);
    rpyBuffer.push(0.0);

    velBufferLimit = 64;
    accBufferLimit = 64;
    jerBufferLimit = 64;
    ldxBufferLimit = 64;
    ldyBufferLimit = 64;
    udxBufferLimit = 64;
    udyBufferLimit = 64;
    rpxBufferLimit = 64;
    rpyBufferLimit = 64;

    emergencyRetries = 0;
    emergencyTimeout = 100; //Attempts

    emergencyAcknowlegded = false;
}

void FlywheelOperation::setInterface(CommonDeviceInterface* deviceInterface)
{
    communicationDevice = deviceInterface;
}

void FlywheelOperation::setMotion(float velocity, float acceleration, float jerk)
{
    setVelocity(velocity);
    setAcceleration(acceleration);
    setJerk(jerk);
}

void FlywheelOperation::setVelocity(float velocity)
{
    communicationDevice->pushCommand(ICM_SET_VELOCITY);
    communicationDevice->pushFloat(velocity);
    communicationDevice->pushCommand(CCM_SET_VELOCITY);
}

void FlywheelOperation::setAcceleration(float acceleration)
{
    communicationDevice->pushCommand(ICM_SET_ACCELERATION);
    communicationDevice->pushFloat(acceleration);
    communicationDevice->pushCommand(CCM_SET_ACCELERATION);
}

void FlywheelOperation::setJerk(float jerk)
{
    communicationDevice->pushCommand(ICM_SET_JERK);
    communicationDevice->pushFloat(jerk);
    communicationDevice->pushCommand(CCM_SET_JERK);
}

float FlywheelOperation::getVelocity()
{
    if (!velBuffer.empty())
    {
        velPrev = velBuffer.front();
        velBuffer.pop();
    }

    return velPrev;
}

float FlywheelOperation::getAcceleration()
{
    if (!accBuffer.empty())
    {
        accPrev = accBuffer.front();
        accBuffer.pop();
    }

    return accPrev;
}

float FlywheelOperation::getJerk()
{
    if (jerBuffer.empty())
    {
        jerPrev = jerBuffer.front();
        jerBuffer.pop();
    }

    return jerPrev;
}

QPointF FlywheelOperation::getUpperDisplacement()
{
    if(!udxBuffer.empty() && !udyBuffer.empty())
    {
        upperDisplacement->setX(udxBuffer.front());
        upperDisplacement->setY(udyBuffer.front());

        udxBuffer.pop();
        udyBuffer.pop();
   }

    return *upperDisplacement;
}

QPointF FlywheelOperation::getLowerDisplacement()
{
    if(!ldxBuffer.empty() && !ldyBuffer.empty())
    {
        lowerDisplacement->setX(ldxBuffer.front());
        lowerDisplacement->setY(ldyBuffer.front());

        ldxBuffer.pop();
        ldyBuffer.pop();
    }
    return *lowerDisplacement;
}

QPointF FlywheelOperation::getRotationalPosition()
{
    if(!rpxBuffer.empty() && !rpyBuffer.empty())
    {
        rotationalPosition->setX(rpxBuffer.front());
        rotationalPosition->setY(rpyBuffer.front());

        rpxBuffer.pop();
        rpyBuffer.pop();
    }

    return *rotationalPosition;
}

void FlywheelOperation::emergencyStop() // Tells the controller to stop and checks to confirm it stopped
{
    emergencyRetries = emergencyTimeout;

    communicationDevice->pushCommandImmediate(ICM_EMERGENCY_STOP);
}

void FlywheelOperation::sync() // Fix issue where one or more bytes in a data set is missing. Example 1 2 3 arrived 4 is late. Error from overpopping queues
{
    if (communicationDevice->isReady())
    {
        communicationDevice->sync();

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
                        if (velBuffer.size() > velBufferLimit) velBuffer.pop();
                        velBuffer.push(rxPacket.dataValue);
                        break;
                    }

                    case ACCELERATION:
                    {
                        if (accBuffer.size() > accBufferLimit) accBuffer.pop();
                        accBuffer.push(rxPacket.dataValue);
                        break;
                    }

                    case JERK:
                    {
                        if (jerBuffer.size() > jerBufferLimit) jerBuffer.pop();
                        jerBuffer.push(rxPacket.dataValue);
                        break;
                    }

                    case LOWER_DISPLACMENT_X:
                    {
                        if (ldxBuffer.size() > ldxBufferLimit) ldxBuffer.pop();
                        ldxBuffer.push(rxPacket.dataValue);
                        break;
                    }

                    case LOWER_DISPLACMENT_Y:
                    {
                        if (ldyBuffer.size() > ldyBufferLimit) ldyBuffer.pop();
                        ldyBuffer.push(rxPacket.dataValue);
                        break;
                    }

                    case UPPER_DISPLACMENT_X:
                    {
                        if (udxBuffer.size() > udxBufferLimit) udxBuffer.pop();
                        udxBuffer.push(rxPacket.dataValue);
                        break;
                    }

                    case UPPER_DISPLACMENT_Y:
                    {
                        if (udyBuffer.size() > udyBufferLimit) udyBuffer.pop();
                        udyBuffer.push(rxPacket.dataValue);
                        break;
                    }

                    case ROTATIONAL_POSITION_X:
                    {
                        if (rpxBuffer.size() > rpxBufferLimit) rpxBuffer.pop();
                        rpxBuffer.push(rxPacket.dataValue);
                        break;
                    }

                    case ROTATIONAL_POSITION_Y:
                    {
                        if (rpyBuffer.size() > rpyBufferLimit) rpyBuffer.pop();
                        rpyBuffer.push(rxPacket.dataValue);
                        break;
                    }

                    default: break;
                }
            }
        }
    }
}
