#ifndef FLY_SERIAL_H
#define FLY_SERIAL_H

// QT Libraries
#include <QtGui>
#include <QSerialPort>
#include <QSerialPortInfo>

// Custom Libraries
#include "interface.h"

class Serial : public Interface
{
    public:
        Serial();
        ~Serial();

        // Overriden Interface Methods
        void sync();
        void startDevice();
        void stopDevice();

        // Unique Methods
        void setDevice(int);
        void setBaudRate(int);
        void setParity(int);
        void setFlowControl(int);
        void setDataBits(int);
        void setStopBits(int);

        void setPort(QSerialPortInfo*);

    private:

        // Internal Helper Functions
        void sendTX();
        void readRX();
        void setDefaults();

        // Internal variables
        QSerialPort* device;

};

#endif // FLY_SERIAL_H
