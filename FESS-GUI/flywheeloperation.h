#ifndef FLYWHEELOPERATION_H
#define FLYWHEELOPERATION_H

#include <QPointF>
#include <queue>

#include "commands.h"
#include "interface.h"

class FlywheelOperation
{
public:
    FlywheelOperation(Interface *inter);

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

    Interface* interface;
    std::queue<float> vel;
    std::queue<float> acc;
    std::queue<float> jer;
    std::queue<float> udx;
    std::queue<float> udy;
    std::queue<float> ldx;
    std::queue<float> ldy;
    std::queue<float> rpx;
    std::queue<float> rpy;

    // Private Setters

    void setDefaults();

    // Helper Functions
    float getData();
};

#endif // FLYWHEELOPERATION_H
