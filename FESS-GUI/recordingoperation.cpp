// C/C++ Libraries
#include <ctime>
#include <iomanip>
#include <sstream>

// Custom Libraries
#include "recordingoperation.h"

/*!
 * \brief RecordingOperation::RecordingOperation
 */
RecordingOperation::RecordingOperation()
{
}
/*!
 * \brief RecordingOperation::Start Starts the recording process.
 * Creates a file "FlywheelOutput_{time}.csv", opens a filestream for it, and prints the heading row.
 */
void RecordingOperation::Start(){
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    //Set filename using stringstream
    std::stringstream iss;
    iss << "FlywheelOutput_";
    iss << std::setw(4) << std::setfill('0') << (timeinfo->tm_year)+1900; //setw() and setfill('0') ensure leading zeros are there.
    iss << std::setw(2) << std::setfill('0') << (timeinfo->tm_mon)+1;
    iss << std::setw(2) << std::setfill('0') << timeinfo->tm_mday;
    iss << "_";
    iss << std::setw(2) << std::setfill('0') << timeinfo->tm_hour;
    iss << std::setw(2) << std::setfill('0') << timeinfo->tm_min;
    iss << std::setw(2) << std::setfill('0') << timeinfo->tm_sec;
    iss << ".csv";
    std::string filename = iss.str();

    rfs.open(filename.c_str());
    rfs << "Time, " << "Velocity, " << "Acceleration, "
        << "UppderDispX, " << "UpperDispY, "
        << "LowerDispX, " << "LowerDispY, "
        << "RotationalPosX, " << "RotationalPosY, "
        << std::endl;
}

/*!
 * \brief RecordingOperation::Record Records the given values in a row.
 * \param time Value to record in the time column.
 * \param velocity Value to record in the velocity column.
 * \param acceleration Value to record in the acceleration column.
 * \param upperDispX Value to record in the upper displacement x column.
 * \param upperDispY Value to record in the upper displacement y column.
 * \param lowerDispX Value to record in the lower displacement x column.
 * \param lowerDispY Value to record in the lower displacement y column.
 * \param rotationalPosX Value to record in the rotational position x column.
 * \param rotationalPosY Value to record in the rotational position y column.
 */
void RecordingOperation::Record(double time, double velocity, double acceleration,
                           double upperDispX, double upperDispY,
                           double lowerDispX, double lowerDispY,
                           double rotationalPosX, double rotationalPosY){
    rfs << std::setprecision(4) << std::fixed
        << time << ", "
        << velocity << ", "
        << acceleration << ", "
        << upperDispX << ", "
        << upperDispY << ", "
        << lowerDispX << ", "
        << lowerDispY << ", "
        << rotationalPosX << ", "
        << rotationalPosY << ", "
        << "\n";
}

/*!
 * \brief RecordingOperation::Stop Stops the current recording process.
 * Flushes the uffer and closes the filestream.
 */
void RecordingOperation::Stop(){
    rfs << std::flush;
    rfs.close();
}
