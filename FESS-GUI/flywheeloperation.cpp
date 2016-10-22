// Custom Libraries
#include "flywheeloperation.h"

FlywheelOperation::FlywheelOperation(Interface *inter)
{
    upperDisplacement = new QPointF();
    lowerDisplacement = new QPointF();
    rotationalPosition = new QPointF();

    interface = inter;
    setDefaults();
}

void FlywheelOperation::setMotion(float velocity, float acceleration, float jerk)
{
    interface->pushCommand(COMMAND_SET_ALLD_FLOA);
    interface->pushData(velocity);
    interface->pushData(acceleration);
    interface->pushData(jerk);
}

void FlywheelOperation::setVelocity(float velocity)
{
    interface->pushCommand(COMMAND_SET_VELO_FLOA);
    interface->pushData(velocity);
}

void FlywheelOperation::setAcceleration(float acceleration)
{
    interface->pushCommand(COMMAND_SET_ACCE_FLOA);
    interface->pushData(acceleration);
}

void FlywheelOperation::setJerk(float jerk)
{
    interface->pushCommand(COMMAND_SET_JERK_FLOA);
    interface->pushData(jerk);
}

float FlywheelOperation::getVelocity()
{
    float val = 0.0;

    if (!vel.empty())
    {
        val = vel.front();

        if (vel.size() > 1)
        {
            vel.pop();
        }
    }

    return val;
}

float FlywheelOperation::getAcceleration()
{
    float val = 0.0;

    if (!acc.empty())
    {
        val = acc.front();

        if (acc.size() > 1)
        {
            acc.pop();
        }
    }

    return val;
}

float FlywheelOperation::getJerk()
{
    float val = 0.0;

    if (jer.empty())
    {
        val = jer.front();

        if (jer.size() > 1)
        {
            jer.pop();
        }
    }

    return val;
}

QPointF FlywheelOperation::getUpperDisplacement()
{
    upperDisplacement->setX(0);
    upperDisplacement->setY(0);

    if(!udx.empty() && !udy.empty())
    {
        upperDisplacement->setX(udx.front());
        upperDisplacement->setY(udy.front());

        if (udx.size() > 1)
        {
            udx.pop();
        }

        if (udy.size() > 1)
        {
            udy.pop();
        }
   }

    return *upperDisplacement;
}

QPointF FlywheelOperation::getLowerDisplacement()
{
    lowerDisplacement->setX(0);
    lowerDisplacement->setY(0);

    if(!ldx.empty() && !ldy.empty())
    {
        lowerDisplacement->setX(ldx.front());
        lowerDisplacement->setY(ldy.front());

        if (ldx.size() > 1)
        {
            ldx.pop();
        }

        if (ldy.size() > 1)
        {
            ldy.pop();
        }
    }
    return *lowerDisplacement;
}

QPointF FlywheelOperation::getRotationalPosition()
{
    rotationalPosition->setX(0);
    rotationalPosition->setY(0);

    if(!rpx.empty() && !rpy.empty())
    {
        rotationalPosition->setX(rpx.front());
        rotationalPosition->setY(rpy.front());

        if (rpx.size() > 1)
        {
            rpx.pop();
        }

        if (rpy.size() > 1)
        {
            rpy.pop();
        }
    }

    return *rotationalPosition;
}

void FlywheelOperation::emergencyStop() // Tells the controller to stop and checks to confirm it stopped
{
    emergency_retries = emergency_timeout;

    interface->flushTX();
    interface->pushCommand(COMMAND_SET_EMER_STOP);
    interface->sync();
}

void FlywheelOperation::setDefaults()
{
    vel.push(1.0);
    acc.push(1.0);
    jer.push(1.0);
    udx.push(1.0);
    udy.push(1.0);
    ldx.push(1.0);
    ldy.push(1.0);
    rpx.push(1.0);
    rpy.push(1.0);

    emergency_retries = 0;
    emergency_timeout = 100; //Attempts

    emergency_acknowlegded = false;
}

void FlywheelOperation::sync() // Fix issue where one or more bytes in a data set is missing. Example 1 2 3 arrived 4 is late. Error from overpopping queues
{
    bool loop = true;
    interface->sync();

    while(( !interface->empty() )&&( loop ))
    {
        switch(interface->pop())
        {
            case COMMAND_ERR_EMER_STOP: // Emergency Stop
            {
                emergency_acknowlegded = true;
                loop = false;
                break;
            }

            case COMMAND_ERR_FIFO_FULL: // FIFO Full
            {
                loop = false;
                break;
            }

            case COMMAND_RES_VELO_FLOA: // Velocity
            {
                vel.push(getData());
                break;
            }

            case COMMAND_RES_ACCE_FLOA: // Acceleration
            {
                acc.push(getData());
                break;
            }

            case COMMAND_RES_JERK_FLOA: // Jerk
            {
                jer.push(getData());
                break;
            }

            case COMMAND_RES_LOWE_DISP: // Lower Displacement
            {
                ldx.push(getData());
                ldy.push(getData());
                break;
            }

            case COMMAND_RES_UPPE_DISP: // Upper Displacement
            {
                udx.push(getData());
                udy.push(getData());
                break;
            }

            case COMMAND_RES_ROTA_POSI: // Lower Displacement
            {
                rpx.push(getData());
                rpy.push(getData());
                break;
            }

            case COMMAND_RES_ALLD_FLOA:  // All
            {
                vel.push(getData());
                acc.push(getData());
                jer.push(getData());
                ldx.push(getData());
                ldy.push(getData());
                udx.push(getData());
                udy.push(getData());
                rpx.push(getData());
                rpy.push(getData());
                break;
            }

            default: // Error: Unknown Commands
            {
                loop = false;
                interface->flush();
                break;
            }
        }

        if (( emergency_retries > 0 )&&( emergency_acknowlegded == false ))
        {
            interface->pushCommand(COMMAND_SET_EMER_STOP);
            interface->sync();
            emergency_retries--;
        }
    }
}

float FlywheelOperation::getData()
{
    unsigned char val[4];
    val[0] = interface->pop();
    val[1] = interface->pop();
    val[2] = interface->pop();
    val[3] = interface->pop();

    return *reinterpret_cast<float*>(&val);
}
