#include "conversions.h"

/*!
 * \brief byteArrayToFloat Interprets and copies a byte a array into a float.
 * \param buffer The source byte array.
 * \return The array converted to a float.
 */
float byteArrayToFloat(FlyByte* buffer)
{
    float val;
    memcpy(&val, buffer, sizeof(val));
    return val;
}

/*!
 * \brief floatToByteArray Interprets and copies a float into a byte array.
 * \param buffer The destination byte array.
 * \param val The source float.
 */
void floatToByteArray(FlyByte* buffer, float* val)
{
    memcpy(buffer, val, sizeof(*val));
}

/*!
 * \brief byteArrayToInt Interprets and copies a byte array into an int.
 * \param buffer The source byte array.
 * \return The array converted to an int.
 */
int byteArrayToInt(FlyByte* buffer)
{
    int val;
    memcpy(&val, buffer, sizeof(val));
    return val;
}

/*!
 * \brief intToByteArray Interprets and copies an int into a byte array.
 * \param buffer The destination byte array.
 * \param val The source int.
 */
void intToByteArray(FlyByte* buffer, int* val)
{
    memcpy(buffer, val, sizeof(*val));
}

/*!
 * \brief zeroArray fills an array with zeros.
 * \param target The destination array.
 * \param size The size of the array.
 */
void zeroArray(void* target, size_t size)
{
    memset(target, 0, size);
}

/*!
 * \brief radsPerSecondToRPM Convertes a value in radians per second to rotations per minute.
 * \param rads The source value in radians per second.
 * \return The value converted to rotations per minute.
 */
double radsPerSecondToRPM(double rads)
{
    return rads * (60 / TAU);
}

/*!
 * \brief RPMtoRadsPerSecond Converts a value in rotations per miute to radians per second.
 * \param RPM The source value in rotations per minute.
 * \return The value converted to radians per second.
 */
double RPMtoRadsPerSecond(double RPM)
{
    return RPM * (TAU / 60);
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
