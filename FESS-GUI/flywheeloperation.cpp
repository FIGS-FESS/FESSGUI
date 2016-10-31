// Custom Libraries
#include "commands.h"
#include "datatypes.h"
#include "flypacket.h"
#include "demodevice.h"
#include "serialdevice.h"
#include "flywheeloperation.h"

FlywheelOperation::FlywheelOperation()
{
    upper_displacement = new QPointF();
    lower_displacement = new QPointF();
    rotational_position = new QPointF();

    communication_device = new DemoDevice();
    communication_device->startDevice();
    setDefaults();
}

FlywheelOperation::~FlywheelOperation()
{
    communication_device->stopDevice();
    delete upper_displacement;
    delete lower_displacement;
    delete rotational_position;
}

void FlywheelOperation::setMotion(float velocity, float acceleration, float jerk)
{
    setVelocity(velocity);
    setAcceleration(acceleration);
    setJerk(jerk);
}

void FlywheelOperation::setVelocity(float velocity)
{
    communication_device->pushCommand(ICM_SET_VELOCITY);
    communication_device->pushFloat(velocity);
    communication_device->pushCommand(CCM_SET_VELOCITY);
}

void FlywheelOperation::setAcceleration(float acceleration)
{
    communication_device->pushCommand(ICM_SET_ACCELERATION);
    communication_device->pushFloat(acceleration);
    communication_device->pushCommand(CCM_SET_ACCELERATION);
}

void FlywheelOperation::setJerk(float jerk)
{
    communication_device->pushCommand(ICM_SET_JERK);
    communication_device->pushFloat(jerk);
    communication_device->pushCommand(CCM_SET_JERK);
}

float FlywheelOperation::getVelocity()
{
    if (!vel_buffer.empty())
    {
        vel_prev = vel_buffer.front();
        vel_buffer.pop();
    }

    return vel_prev;
}

float FlywheelOperation::getAcceleration()
{
    if (!acc_buffer.empty())
    {
        acc_prev = acc_buffer.front();
        acc_buffer.pop();
    }

    return acc_prev;
}

float FlywheelOperation::getJerk()
{
    if (jer_buffer.empty())
    {
        jer_prev = jer_buffer.front();
        jer_buffer.pop();
    }

    return jer_prev;
}

QPointF FlywheelOperation::getUpperDisplacement()
{
    if(!udx_buffer.empty() && !udy_buffer.empty())
    {
        upper_displacement->setX(udx_buffer.front());
        upper_displacement->setY(udy_buffer.front());

        udx_buffer.pop();
        udy_buffer.pop();
   }

    return *upper_displacement;
}

QPointF FlywheelOperation::getLowerDisplacement()
{
    if(!ldx_buffer.empty() && !ldy_buffer.empty())
    {
        lower_displacement->setX(ldx_buffer.front());
        lower_displacement->setY(ldy_buffer.front());

        ldx_buffer.pop();
        ldy_buffer.pop();
    }
    return *lower_displacement;
}

QPointF FlywheelOperation::getRotationalPosition()
{
    if(!rpx_buffer.empty() && !rpy_buffer.empty())
    {
        rotational_position->setX(rpx_buffer.front());
        rotational_position->setY(rpy_buffer.front());

        rpx_buffer.pop();
        rpy_buffer.pop();
    }

    return *rotational_position;
}

void FlywheelOperation::emergencyStop() // Tells the controller to stop and checks to confirm it stopped
{
    emergency_retries = emergency_timeout;

    communication_device->pushCommandImmediate(ICM_EMERGENCY_STOP);
}

void FlywheelOperation::setDefaults()
{
    vel_prev = 0.0;
    acc_prev = 0.0;
    jer_prev = 0.0;

    vel_buffer.push(0.0);
    acc_buffer.push(0.0);
    jer_buffer.push(0.0);
    udx_buffer.push(0.0);
    udy_buffer.push(0.0);
    ldx_buffer.push(0.0);
    ldy_buffer.push(0.0);
    rpx_buffer.push(0.0);
    rpy_buffer.push(0.0);

    //lower_displacement->setX(0.0);
    //lower_displacement->setY(0.0);

    //upper_displacement->setX(0.0);
    //upper_displacement->setY(0.0);

    //rotational_position->setX(0.0);
    //rotational_position->setY(0.0);

    vel_buffer_limit = 64;
    acc_buffer_limit = 64;
    jer_buffer_limit = 64;
    ldx_buffer_limit = 64;
    ldy_buffer_limit = 64;
    udx_buffer_limit = 64;
    udy_buffer_limit = 64;
    rpx_buffer_limit = 64;
    rpy_buffer_limit = 64;

    emergency_retries = 0;
    emergency_timeout = 100; //Attempts

    emergency_acknowlegded = false;
}

void FlywheelOperation::sync() // Fix issue where one or more bytes in a data set is missing. Example 1 2 3 arrived 4 is late. Error from overpopping queues
{
    communication_device->sync();

    while(!communication_device->empty())
    {
        flybyte rx_data = communication_device->popCommand();
        flypacket rx_packet = buildFlyPacket(rx_data);

        if (rx_packet.packet_type == DATA_PACKET)
        {

            switch(rx_packet.data_type)
            {
                case VELOCITY:
                {
                    if (vel_buffer.size() > vel_buffer_limit) vel_buffer.pop();
                    vel_buffer.push(rx_packet.data_value);
                    break;
                }

                case ACCELERATION:
                {
                    if (acc_buffer.size() > acc_buffer_limit) acc_buffer.pop();
                    acc_buffer.push(rx_packet.data_value);
                    break;
                }

                case JERK:
                {
                    if (jer_buffer.size() > jer_buffer_limit) jer_buffer.pop();
                    jer_buffer.push(rx_packet.data_value);
                    break;
                }

                case LOWER_DISPLACMENT_X:
                {
                    if (ldx_buffer.size() > ldx_buffer_limit) ldx_buffer.pop();
                    ldx_buffer.push(rx_packet.data_value);
                    break;
                }

                case LOWER_DISPLACMENT_Y:
                {
                    if (ldy_buffer.size() > ldy_buffer_limit) ldy_buffer.pop();
                    ldy_buffer.push(rx_packet.data_value);
                    break;
                }

                case UPPER_DISPLACMENT_X:
                {
                    if (udx_buffer.size() > udx_buffer_limit) udx_buffer.pop();
                    udx_buffer.push(rx_packet.data_value);
                    break;
                }

                case UPPER_DISPLACMENT_Y:
                {
                    if (udy_buffer.size() > udy_buffer_limit) udy_buffer.pop();
                    udy_buffer.push(rx_packet.data_value);
                    break;
                }

                case ROTATIONAL_POSITION_X:
                {
                    if (rpx_buffer.size() > rpx_buffer_limit) rpx_buffer.pop();
                    rpx_buffer.push(rx_packet.data_value);
                    break;
                }

                case ROTATIONAL_POSITION_Y:
                {
                    if (rpy_buffer.size() > rpy_buffer_limit) rpy_buffer.pop();
                    rpy_buffer.push(rx_packet.data_value);
                    break;
                }

                default: break;
            }
        }

       // if (( emergency_retries > 0 )&&( emergency_acknowlegded == false ))
       // {
       //     communication_device->pushCommand(COMMAND_SET_EMER_STOP);
       //     communication_device->sync();
       //     emergency_retries--;
       // }
    }
}
