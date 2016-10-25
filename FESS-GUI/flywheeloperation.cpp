// Custom Libraries
#include "conversions.h"
#include "flywheeloperation.h"

#include <QtGui>

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

    sync_state = 0;
    sync_data = false;
    sync_buffer.clear();

    emergency_retries = 0;
    emergency_timeout = 100; //Attempts

    emergency_acknowlegded = false;
}

void FlywheelOperation::sync() // Fix issue where one or more bytes in a data set is missing. Example 1 2 3 arrived 4 is late. Error from overpopping queues
{
    uint8_t byte;
    bool error = false;

    communicationDevice->sync();

    while(!communicationDevice->empty())
    {
        byte = communicationDevice->popCommand();

        if (error)
        {
            communicationDevice->flush();
            sync_state = 0;
            sync_data = false;
            break;
        }

        else if (sync_data)
        {
            if (sync_count == 0)
            {
                switch(byte) // Look for Complete Command
                {
                    case CDM_SEND_VELOCITY:
                    {
                        if (sync_state == IDM_SEND_VELOCITY)
                        {
                            vel.push(bytesToFloat(sync_buffer));
                            sync_buffer.clear();
                            sync_state = 0;
                            sync_data = false;
                        }

                        else
                        {
                            error = true;
                        }

                        break;
                    }

                    default:
                    {
                        error = true;
                        break;
                    }
                }
            }
            else
            {
                sync_count--;
                sync_buffer.push_back(byte);
            }
        }
        else
        {
            switch(byte) // Look for Initiate Command
            {
                case IDM_SEND_VELOCITY:
                {
                    sync_data = true;
                    sync_state = IDM_SEND_VELOCITY;
                    sync_count = 4;
                    break;
                }

                default: // Error: Unknown Commands
                {
                    error = true;
                    break;
                }
            }
        }

       // if (( emergency_retries > 0 )&&( emergency_acknowlegded == false ))
       // {
       //     communicationDevice->pushCommand(COMMAND_SET_EMER_STOP);
       //     communicationDevice->sync();
       //     emergency_retries--;
       // }
    }
}
