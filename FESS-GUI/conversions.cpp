#include "qmath.h"
#include "string.h"
#include "conversions.h"

/*!
 * \brief byteArrayToFloat Interprets and copies a byte a array into a float.
 * \param buffer The source byte array.
 * \param val The destination float.
 */
void byteArrayToFloat(flybyte* buffer, float* val)
{
    memcpy(val, buffer, sizeof(*val));
}

/*!
 * \brief floatToByteArray Interprets and copies a float into a byte array.
 * \param buffer The destination byte array.
 * \param val The source float.
 */
void floatToByteArray(flybyte* buffer, float* val)
{
    memcpy(buffer, val, sizeof(*val));
}

/*!
 * \brief byteArrayToInt Interprets and copies a byte array into an int.
 * \param buffer The source byte array.
 * \param val The destination int.
 */
void byteArrayToInt(flybyte* buffer, int* val)
{
    memcpy(val, buffer, sizeof(*val));
}

/*!
 * \brief intToByteArray Interprets and copies an int into a byte array.
 * \param buffer The destination byte array.
 * \param val The source int.
 */
void intToByteArray(flybyte* buffer, int* val)
{
    memcpy(buffer, val, sizeof(*val));
}

/*!
 * \brief radsPerSecondToRPM Convertes a value in radians per second to rotations per minute.
 * \param rads The source value in radians per second.
 * \return The value converted to rotations per minute.
 */
double radsPerSecondToRPM(double rads)
{
    return rads * (60 / (2 * M_PI)); //M_PI is defined in <qmath.h>
}

/*!
 * \brief RPMtoRadsPerSecond Converts a value in rotations per miute to radians per second.
 * \param RPM The source value in rotations per minute.
 * \return The value converted to radians per second.
 */
double RPMtoRadsPerSecond(double RPM)
{
    return RPM * ((2 * M_PI) / 60);
}

/*!
 * \brief derivative Returns the difference between two values.
 * \param value The given value.
 * \param prev The previous value.
 * \return The difference between value and prev.
 */
float derivative(float value, float prev)
{
    return value-prev;
}

/*!
 * \brief refreshRateToMS Converts a rate in Hz to its corresponding interval in milliseconds.
 * \param rate The source value in Hz.
 * \return The corresponding interval in milliseconds.
 */
float refreshRateToMS(int rate)
{
    return 1000.0/rate;
}
