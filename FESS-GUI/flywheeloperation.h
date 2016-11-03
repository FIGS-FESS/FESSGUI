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

    void setInterface(CommonDeviceInterface*);

    QPointF getUpperDisplacement();
    QPointF getLowerDisplacement();
    QPointF getRotationalPosition();

private:
    // Private Variables

    unsigned int emergency_timeout;
    unsigned int emergency_retries;
    bool emergency_acknowlegded;

    QPointF* upper_displacement;
    QPointF* lower_displacement;
    QPointF* rotational_position;

    CommonDeviceInterface* communication_device;
    std::queue<float> vel_buffer;
    std::queue<float> acc_buffer;
    std::queue<float> jer_buffer;
    std::queue<float> udx_buffer;
    std::queue<float> udy_buffer;
    std::queue<float> ldx_buffer;
    std::queue<float> ldy_buffer;
    std::queue<float> rpx_buffer;
    std::queue<float> rpy_buffer;

    // Queue Sizes

    unsigned int vel_buffer_limit;
    unsigned int acc_buffer_limit;
    unsigned int jer_buffer_limit;
    unsigned int ldx_buffer_limit;
    unsigned int ldy_buffer_limit;
    unsigned int udx_buffer_limit;
    unsigned int udy_buffer_limit;
    unsigned int rpx_buffer_limit;
    unsigned int rpy_buffer_limit;

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
