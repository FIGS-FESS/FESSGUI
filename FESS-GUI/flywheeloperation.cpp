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
    float val = vel.front();

    if (!vel.empty())
    {
        vel.pop();
    }

    return val;
}

float FlywheelOperation::getAcceleration()
{
    float val = acc.front();

    if (!acc.empty())
    {
        acc.pop();
    }

    return val;
}

float FlywheelOperation::getJerk()
{
    float val = jer.front();

    if (!jer.empty())
    {
        jer.pop();
    }

    return val;
}

QPointF FlywheelOperation::getUpperDisplacement()
{
    upperDisplacement->setX(udx.front());
    upperDisplacement->setY(udy.front());

    if (!udx.empty())
    {
        udx.pop();
    }

    if (!udy.empty())
    {
        udy.pop();
    }

    return *upperDisplacement;
}

QPointF FlywheelOperation::getLowerDisplacement()
{
    lowerDisplacement->setX(ldx.front());
    lowerDisplacement->setY(ldy.front());

    if (!ldx.empty())
    {
        ldx.pop();
    }

    if (!ldy.empty())
    {
        ldy.pop();
    }

    return *lowerDisplacement;
}

QPointF FlywheelOperation::getRotationalPosition()
{
    rotationalPosition->setX(rpx.front());
    rotationalPosition->setY(rpy.front());

    if (!rpx.empty())
    {
        rpx.pop();
    }

    if (!rpy.empty())
    {
        rpy.pop();
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
    vel.push(0.0);
    acc.push(0.0);
    jer.push(0.0);
    udx.push(0.0);
    udy.push(0.0);
    ldx.push(0.0);
    ldy.push(0.0);
    rpx.push(0.0);
    rpy.push(0.0);

    emergency_retries = 0;
    emergency_timeout = 100; //Attempts

    emergency_acknowlegded = false;
}

void FlywheelOperation::sync()
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
