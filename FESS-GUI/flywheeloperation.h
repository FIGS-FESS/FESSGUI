#ifndef FLYWHEELOPERATION_H
#define FLYWHEELOPERATION_H

// QT Libraries
#include <QPointF>

// C++ Libraries
#include <queue>

// Custom Libraries
#include "commondeviceinterface.h"

/*!
 * \brief The FlywheelOperation class handles all operations involving the flywheel.
 */
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
    bool emergencyAcknowlegded;

    QPointF* upperDisplacement;
    QPointF* lowerDisplacement;
    QPointF* rotationalPosition;

    CommonDeviceInterface* communicationDevice;

    std::queue<float> velBuffer;
    std::queue<float> accBuffer;
    std::queue<float> jerBuffer;
    std::queue<float> udxBuffer;
    std::queue<float> udyBuffer;
    std::queue<float> ldxBuffer;
    std::queue<float> ldyBuffer;
    std::queue<float> rpxBuffer;
    std::queue<float> rpyBuffer;

    // Queue Sizes

    unsigned int velBufferLimit;
    unsigned int accBufferLimit;
    unsigned int jerBufferLimit;
    unsigned int ldxBufferLimit;
    unsigned int ldyBufferLimit;
    unsigned int udxBufferLimit;
    unsigned int udyBufferLimit;
    unsigned int rpxBufferLimit;
    unsigned int rpyBufferLimit;

    // Sync Flags and Buffers

    float velPrev;
    float accPrev;
    float jerPrev;
};

#endif // FLYWHEELOPERATION_H
