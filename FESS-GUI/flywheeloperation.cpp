// Custom Libraries
#include "flypacket.h"
#include "flywheeloperation.h"

/*!
 * \brief FlywheelOperation::FlywheelOperation Initializes variables to default values.
 */
FlywheelOperation::FlywheelOperation()
{
    upperDisplacement = new QPointF();
    lowerDisplacement = new QPointF();
    rotationalPosition = new QPointF();
    setDefaults();
}

/*!
 * \brief FlywheelOperation::FlywheelOperation Sets the deviceInterface and initializes variables to default values.
 * \param deviceInterface
 */
FlywheelOperation::FlywheelOperation(CommonDeviceInterface* deviceInterface)
{
    upperDisplacement = new QPointF();
    lowerDisplacement = new QPointF();
    rotationalPosition = new QPointF();

    communicationDevice = deviceInterface;
    setDefaults();
}

/*!
 * \brief FlywheelOperation::~FlywheelOperation Deletes pointers.
 */
FlywheelOperation::~FlywheelOperation()
{
    delete upperDisplacement;
    delete lowerDisplacement;
    delete rotationalPosition;
}

/*!
 * \brief FlywheelOperation::setDefaults Sets default values for member variables.
 */
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

    emergencyStopActivated = false;
}

/*!
 * \brief FlywheelOperation::setInterface Sets the device interface.
 * \param deviceInterface Pointer to the interface to set member variable to.
 */
void FlywheelOperation::setInterface(CommonDeviceInterface* deviceInterface)
{
    communicationDevice = deviceInterface;
}

/*!
 * \brief FlywheelOperation::setMotion Sets all motion parameters for the flywheel.
 * \param velocity The velocity to set the flywheel to.
 * \param acceleration The acceleration to set the flywheel to.
 * \param jerk The jerk to set the flywheel to.
 */
void FlywheelOperation::setMotion(float velocityValue, float accelerationValue, float jerkValue)
{
    setVelocity(velocityValue);
    setAcceleration(accelerationValue);
    setJerk(jerkValue);
}

/*!
 * \brief FlywheelOperation::setVelocity Sets the velocity of the flywheel.
 * \param velocity The velocity to se tthe flywheel to.
 */
void FlywheelOperation::setVelocity(float velocityValue)
{
     if ((communicationDevice != nullptr) && (communicationDevice->isReady()))
    {
        FlyPacket dataPacket(ICM_SET_VELOCITY,velocityValue);
        communicationDevice->pushPacket(dataPacket);
    }
}

/*!
 * \brief FlywheelOperation::setAcceleration Sets the acceleration of the flywheel.
 * \param acceleration The acceleration to set the flywheel to.
 */
void FlywheelOperation::setAcceleration(float accelerationValue)
{
     if ((communicationDevice != nullptr) && (communicationDevice->isReady()))
    {
        FlyPacket dataPacket(ICM_SET_ACCELERATION,accelerationValue);
        communicationDevice->pushPacket(dataPacket);
    }
}

/*!
 * \brief FlywheelOperation::setJerk Sets the jerk of the flywheel.
 * \param jerk The jerk to set the flywheel to.
 */
void FlywheelOperation::setJerk(float jerkValue)
{
    if ((communicationDevice != nullptr) && (communicationDevice->isReady()))
    {
        FlyPacket dataPacket(ICM_SET_JERK,jerkValue);
        communicationDevice->pushPacket(dataPacket);
    }
}

/*!
 * \brief FlywheelOperation::getVelocity Gets the current velocity of the flywheel.
 * \return The current velocity of the flywheel.
 */
float FlywheelOperation::getVelocity()
{
    return velocityValue;
}

/*!
 * \brief FlywheelOperation::getAcceleration Gets the current acceleration of the flywheel.
 * \return The current acceleration of the flywheel.
 */
float FlywheelOperation::getAcceleration()
{
    return accelerationValue;
}

/*!
 * \brief FlywheelOperation::getJerk Gets the current jerk of the flywheel.
 * \return The current jerk of the flywheel.
 */
float FlywheelOperation::getJerk()
{
    return jerkValue;
}

/*!
 * \brief FlywheelOperation::getUpperDisplacement Gets the upper displacement of the flywheel.
 * \return The upper displacement of the flywheel.
 */
QPointF FlywheelOperation::getUpperDisplacement()
{
    upperDisplacement->setX(upperDisplacementXValue);
    upperDisplacement->setY(upperDisplacementYValue);

    return *upperDisplacement;
}

/*!
 * \brief FlywheelOperation::getLowerDisplacement Gets the lower displacement of the flywheel.
 * \return The lower displacement of the flywheel.
 */
QPointF FlywheelOperation::getLowerDisplacement()
{
    lowerDisplacement->setX(lowerDisplacementXValue);
    lowerDisplacement->setY(lowerDisplacementYValue);
    return *lowerDisplacement;
}

/*!
 * \brief FlywheelOperation::getRotationalPosition Gets the rotational position of the flywheel.
 * \return The rotational position of the flywheel.
 */
QPointF FlywheelOperation::getRotationalPosition()
{
    rotationalPosition->setX(rotationalPositionXValue);
    rotationalPosition->setY(rotationalPositionYValue);
    return *rotationalPosition;
}

/*!
 * \brief FlywheelOperation::emergencyStop Sends a command to stop the flywheel immediately.
 */
void FlywheelOperation::emergencyStop() // Tells the controller to stop and checks to confirm it stopped
{
    emergencyStopActivated = true;
}

/*!
 * \brief FlywheelOperation::sync Syncs the flywheel operation.
 * Syncs the communication device and fixes error where bytes in a data set are missing.
 */
void FlywheelOperation::syncRX()
{
    while(!communicationDevice->empty())
    {
        FlyPacket rxPacket = communicationDevice->popPacket();

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

            case ICM_EMERGENCY_STOP:
            {
                emergencyStopActivated = false;
                break;
            }

            default: break;
        }
    }
}

void FlywheelOperation::sync()
{
    if ((communicationDevice != nullptr) && (communicationDevice->isReady()))
    {
        if (emergencyStopActivated == true)
        {
            communicationDevice->flushTX();
            FlyPacket emergencyStopPacket(ICM_EMERGENCY_STOP,0);
            communicationDevice->pushPacket(emergencyStopPacket);
        }

        communicationDevice->syncRX();
        communicationDevice->syncTX();
        syncRX();
    }
}
