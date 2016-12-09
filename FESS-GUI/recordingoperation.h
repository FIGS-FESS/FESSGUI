#ifndef RECORDINGOPERATION_H
#define RECORDINGOPERATION_H
#include <fstream>

/*!
 * \brief The RecordingOperation class
 * Handles operations involving recording values to csv.
 */
class RecordingOperation
{
private:
    std::ofstream rfs;
public:
    RecordingOperation();
    void Start();
    void Stop();
    void Record(double time, double velocity, double acceleration,
                double upperDispX, double upperDispY,
                double lowerDispX, double lowerDispY,
                double rotationalPosX, double rotationalPosY);
};

#endif // RECORDINGOPERATION_H
