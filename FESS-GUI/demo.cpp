//C Libraries
#include <cmath>

//QT Libraries
#include <QTime>
#include <QtMath>

//Custom Libraries
#include "demo.h"
#include "commands.h"

Demo::Demo(){}

void Demo::sync()
{
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

    float vel = qSin(key*1.6+qCos(key*1.7)*2)*10 + qSin(key*1.2+0.56)*20 + 26;
    float acc = qSin(key*1.3+qCos(key*1.2)*1.2)*7 + qSin(key*0.9+0.26)*24 + 26;
    float jer = key;
    float udx = 2*qCos(key) - qCos(2*key);
    float udy = 2*qSin(key) - qSin(2*key);
    float ldx = 2*qCos(key + 0.1) - qCos(2*key + 0.1);
    float ldy = 2*qSin(key + 0.1) - qSin(2*key + 0.1);
    //float rpx = qSin(key);
    //float rpy = qCos(key);

    pushRXChar(COMMAND_RES_ALLD_FLOA);

    pushRXFloat(vel);
    pushRXFloat(acc);
    pushRXFloat(jer);
    pushRXFloat(ldx);
    pushRXFloat(ldy);
    pushRXFloat(udx);
    pushRXFloat(udy);
    //pushRXFloat(rpx);
    //pushRXFloat(rpx);
}
