#ifndef FLYWHEELOPERATION_H
#define FLYWHEELOPERATION_H



class FlywheelOperation
{
public:
    FlywheelOperation();
    void setMotion(float velocity, float acceleration, float jerk);
    float getVelocity();
    float getAcceleration();
    float getJerk();
};

#endif // FLYWHEELOPERATION_H
