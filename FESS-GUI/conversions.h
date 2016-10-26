#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include <qmath.h>

double radsPerSecondToRPM(double rads)
{
    return rads * (60 / (2 * M_PI)); //M_PI is defined in <qmath.h>
}

double RPMtoRadsPerSecond(double RPM)
{
    return RPM * ((2 * M_PI) / 60);
}

#endif // CONVERSIONS_H
