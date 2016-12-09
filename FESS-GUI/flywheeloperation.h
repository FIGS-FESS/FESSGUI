/*!
 * \brief The FlywheelOperation class handles all operations involving the flywheel.
 */

#ifndef FLYWHEELOPERATION_H
#define FLYWHEELOPERATION_H

// QT Libraries
#include <QPointF>

// C++ Libraries
#include <queue>

// Custom Libraries
#include "commondeviceinterface.h"


class FlywheelOperation
{
public:
    FlywheelOperation();
    FlywheelOperation(CommonDeviceInterface*);
    ~FlywheelOperation();

    void sync();

    void setDefaults();
    void setVelocity(float);
    void setAcceleration(float);
    void setJerk(float);
    void setMotion(float, float, float);

    float getVelocity();
    float getAcceleration();
    float getJerk();

    void emergencyStop();

    void setInterface(CommonDeviceInterface*);

    QPointF getUpperDisplacement();
    QPointF getLowerDisplacement();
    QPointF getRotationalPosition();

private:
    // Private Variables

    unsigned int emergencyTimeout;
    unsigned int emergencyRetries;

    bool emergencyStopActivated;

    QPointF* upperDisplacement;
    QPointF* lowerDisplacement;
    QPointF* rotationalPosition;

    CommonDeviceInterface* communicationDevice;

    float velocityValue;
    float accelerationValue;
    float jerkValue;

    float lowerDisplacementXValue;
    float lowerDisplacementYValue;
    float upperDisplacementXValue;
    float upperDisplacementYValue;
    float rotationalPositionXValue;
    float rotationalPositionYValue;

    void syncRX();
    void syncTX();
};

#endif // FLYWHEELOPERATION_H
