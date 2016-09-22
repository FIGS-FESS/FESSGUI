#ifndef FLYWHEELOPERATION_H
#define FLYWHEELOPERATION_H

#include <QPointF>

class FlywheelOperation
{
public:
    FlywheelOperation();
    void setMotion(float velocity, float acceleration, float jerk);
    float getVelocity();
    float getAcceleration();
    float getJerk();
    QPointF getUpperDisplacement();
    QPointF getLowerDisplacement();
};

#endif // FLYWHEELOPERATION_H
