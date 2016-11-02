// C/C++ Libraries
#include <ctime>
#include <iomanip>
#include <sstream>

// Custom Libraries
#include "recordingoperation.h"

RecordingOperation::RecordingOperation()
{
}

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

void RecordingOperation::Stop(){
    rfs << std::flush;
    rfs.close();
}
