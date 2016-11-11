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
    bool emergencyStopAcknowlegded;

    QPointF* upperDisplacement;
    QPointF* lowerDisplacement;
    QPointF* rotationalPosition;

    CommonDeviceInterface* communicationDevice;

    std::queue<float> velocityValueBufferRX;
    std::queue<float> accelerationValueBufferRX;
    std::queue<float> jerkValueBufferRX;
    std::queue<float> upperDisplacementXValueBufferRX;
    std::queue<float> upperDisplacementYValueBufferRX;
    std::queue<float> lowerDisplacementXValueBufferRX;
    std::queue<float> lowerDisplacementYValueBufferRX;
    std::queue<float> rotationalPositionXValueBufferRX;
    std::queue<float> rotationalPositionYValueBufferRX;

    std::queue<float> velocityValueBufferTX;
    std::queue<float> accelerationValueBufferTX;
    std::queue<float> jerkValueBufferTX;

    // Queue Sizes

    unsigned int velocityValueBufferRXLimit;
    unsigned int accelerationValueBufferRXLimit;
    unsigned int jerkValueBufferRXLimit;
    unsigned int lowerDisplacementXValueBufferRXLimit;
    unsigned int lowerDisplacementYValueBufferRXLimit;
    unsigned int upperDisplacementXValueBufferRXLimit;
    unsigned int upperDisplacementYValueBufferRXLimit;
    unsigned int rotationalPositionXValueBufferRXLimit;
    unsigned int rotationalPositionYValueBufferRXLimit;

    unsigned int velocityValueBufferTXLimit;
    unsigned int accelerationValueBufferTXLimit;
    unsigned int jerkValueBufferTXLimit;

    float velocityCurrentValue;
    float accelerationCurrentValue;
    float jerkCurrentValue;

    void syncRX();
    void syncTX();
};

#endif // FLYWHEELOPERATION_H
