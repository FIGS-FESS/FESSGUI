#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include <qmath.h>

double radsPerSecondToRPM(double rads)
{
    return rads * 60 / M_PI;
}

#endif // CONVERSIONS_H
