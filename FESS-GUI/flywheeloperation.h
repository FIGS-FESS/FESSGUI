#ifndef FLYWHEELOPERATION_H
#define FLYWHEELOPERATION_H

// QT Libraries
#include <QPointF>

// C++ Libraries
#include <queue>

// Custom Libraries
#include "commands.h"
#include "commondeviceinterface.h"

class FlywheelOperation
{
public:
    FlywheelOperation(CommonDeviceInterface*);
    ~FlywheelOperation();

    void sync();

    void setVelocity(float);
    void setAcceleration(float);
    void setJerk(float);
    void setMotion(float, float, float);

    float getVelocity();
    float getAcceleration();
    float getJerk();

    void emergencyStop();

    QPointF getUpperDisplacement();
    QPointF getLowerDisplacement();
    QPointF getRotationalPosition();

private:
    // Private Variables

    int emergency_timeout;
    int emergency_retries;
    bool emergency_acknowlegded;

    QPointF* upperDisplacement;
    QPointF* lowerDisplacement;
    QPointF* rotationalPosition;

    CommonDeviceInterface* communicationDevice;
    std::queue<float> vel;
    std::queue<float> acc;
    std::queue<float> jer;
    std::queue<float> udx;
    std::queue<float> udy;
    std::queue<float> ldx;
    std::queue<float> ldy;
    std::queue<float> rpx;
    std::queue<float> rpy;

    // Sync Flags and Buffers

    float vel_prev;
    float acc_prev;
    float jer_prev;

    // Private Setters

    void setDefaults();

    // Helper Functions
    float getData();
};

#endif // FLYWHEELOPERATION_H
