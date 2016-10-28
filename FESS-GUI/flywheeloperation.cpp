// Custom Libraries
#include "datatypes.h"
#include "flypacket.h"
#include "flywheeloperation.h"

FlywheelOperation::FlywheelOperation(CommonDeviceInterface* cdi)
{
    upperDisplacement = new QPointF();
    lowerDisplacement = new QPointF();
    rotationalPosition = new QPointF();

    communicationDevice = cdi;
    setDefaults();
}

FlywheelOperation::~FlywheelOperation()
{
    delete upperDisplacement;
    delete lowerDisplacement;
    delete rotationalPosition;
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
    if (!vel.empty())
    {
        vel_prev = vel.front();
        vel.pop();
    }

    return vel_prev;
}

float FlywheelOperation::getAcceleration()
{
    if (!acc.empty())
    {
        acc_prev = acc.front();
        acc.pop();
    }

    return acc_prev;
}

float FlywheelOperation::getJerk()
{
    if (jer.empty())
    {
        jer_prev = jer.front();
        jer.pop();
    }

    return jer_prev;
}

QPointF FlywheelOperation::getUpperDisplacement()
{
    if(!udx.empty() && !udy.empty())
    {
        upperDisplacement->setX(udx.front());
        upperDisplacement->setY(udy.front());

        udx.pop();
        udy.pop();
   }

    return *upperDisplacement;
}

QPointF FlywheelOperation::getLowerDisplacement()
{
    if(!ldx.empty() && !ldy.empty())
    {
        lowerDisplacement->setX(ldx.front());
        lowerDisplacement->setY(ldy.front());

        ldx.pop();
        ldy.pop();
    }
    return *lowerDisplacement;
}

QPointF FlywheelOperation::getRotationalPosition()
{
    if(!rpx.empty() && !rpy.empty())
    {
        rotationalPosition->setX(rpx.front());
        rotationalPosition->setY(rpy.front());

        rpx.pop();
        rpy.pop();
    }

    return *rotationalPosition;
}

void FlywheelOperation::emergencyStop() // Tells the controller to stop and checks to confirm it stopped
{
    emergency_retries = emergency_timeout;

    communicationDevice->pushCommandImmediate(ICM_EMERGENCY_STOP);
}

void FlywheelOperation::setDefaults()
{
    vel_prev = 0.0;
    acc_prev = 0.0;
    jer_prev = 0.0;

    vel.push(0.0);
    acc.push(0.0);
    jer.push(0.0);
    udx.push(0.0);
    udy.push(0.0);
    ldx.push(0.0);
    ldy.push(0.0);
    rpx.push(0.0);
    rpy.push(0.0);

    lowerDisplacement->setX(0.0);
    lowerDisplacement->setY(0.0);

    upperDisplacement->setX(0.0);
    upperDisplacement->setY(0.0);

    rotationalPosition->setX(0.0);
    rotationalPosition->setY(0.0);

    emergency_retries = 0;
    emergency_timeout = 100; //Attempts

    emergency_acknowlegded = false;
}

void FlywheelOperation::sync() // Fix issue where one or more bytes in a data set is missing. Example 1 2 3 arrived 4 is late. Error from overpopping queues
{
    communicationDevice->sync();

    while(!communicationDevice->empty())
    {
        flybyte rx_data = communicationDevice->popCommand();
        flypacket rx_packet = buildFlyPacket(rx_data);

        switch(rx_packet.type)
        {
            case VELOCITY:
            {
                if (vel.size() > 64) vel.pop();
                vel.push(rx_packet.value);
                break;
            }

            case ACCELERATION:
            {
                if (acc.size() > 64) acc.pop();
                acc.push(rx_packet.value);
                break;
            }

            case JERK:
            {
                if (jer.size() > 64) jer.pop();
                jer.push(rx_packet.value);
                break;
            }

            case LOWER_DISPLACMENT_X:
            {
                if (ldx.size() > 64) ldx.pop();
                ldx.push(rx_packet.value);
                break;
            }

            case LOWER_DISPLACMENT_Y:
            {
                if (ldy.size() > 64) ldy.pop();
                ldy.push(rx_packet.value);
                break;
            }

            case UPPER_DISPLACMENT_X:
            {
                if (udx.size() > 64) udx.pop();
                udx.push(rx_packet.value);
                break;
            }

            case UPPER_DISPLACMENT_Y:
            {
                if (udy.size() > 64) udy.pop();
                udy.push(rx_packet.value);
                break;
            }

            case ROTATIONAL_POSITION_X:
            {
                if (rpx.size() > 64) rpx.pop();
                rpx.push(rx_packet.value);
                break;
            }

            case ROTATIONAL_POSITION_Y:
            {
                if (rpy.size() > 64) rpy.pop();
                rpy.push(rx_packet.value);
                break;
            }

            default: break;
        }


       // if (( emergency_retries > 0 )&&( emergency_acknowlegded == false ))
       // {
       //     communicationDevice->pushCommand(COMMAND_SET_EMER_STOP);
       //     communicationDevice->sync();
       //     emergency_retries--;
       // }
    }
}
