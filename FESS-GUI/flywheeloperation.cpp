#include "flywheeloperation.h"
#include <cmath>
#include <QTime>
#include <QtMath>

FlywheelOperation::FlywheelOperation()
{
    upperDisplacement = new QPointF();
    lowerDisplacement = new QPointF();
    rotationalPosition = new QPointF();
}

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

QPointF FlywheelOperation::getUpperDisplacement()
{
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    upperDisplacement->setX(2*qCos(key) - qCos(2*key));
    upperDisplacement->setY(2*qSin(key) - qSin(2*key));
    return *upperDisplacement;
}

QPointF FlywheelOperation::getLowerDisplacement()
{
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    lowerDisplacement->setX(2*qCos(key + 0.1) - qCos(2*key + 0.1));
    lowerDisplacement->setY(2*qSin(key + 0.1) - qSin(2*key + 0.1));
    return *lowerDisplacement;
}

QPointF FlywheelOperation::getRotationalPosition()
{
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    rotationalPosition->setX(qSin(key));
    rotationalPosition->setY(qCos(key));
    return *rotationalPosition;
}
