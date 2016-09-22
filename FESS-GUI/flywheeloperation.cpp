#include "flywheeloperation.h"
#include <cmath>
#include <QTime>
#include <QtMath>

FlywheelOperation::FlywheelOperation(){}

void FlywheelOperation::setMotion(float velocity = NAN, float acceleration = NAN, float jerk = NAN)
{

}

float FlywheelOperation::getVelocity()
{
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    return qSin(key*1.6+qCos(key*1.7)*2)*10 + qSin(key*1.2+0.56)*20 + 26;
}

float FlywheelOperation::getAcceleration()
{
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    return qSin(key*1.3+qCos(key*1.2)*1.2)*7 + qSin(key*0.9+0.26)*24 + 26;
}

float FlywheelOperation::getJerk()
{
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    return key;
}
