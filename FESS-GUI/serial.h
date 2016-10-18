#ifndef FLY_SERIAL_H
#define FLY_SERIAL_H

// QT Libraries
#include <QtGui>
#include <QSerialPort>
#include <QSerialPortInfo>

// C++ Libraries
#include <string>

// Custom Libraries
#include "interface.h"

class Serial : public Interface
{
    public:
        Serial();
        ~Serial();

        bool findDevices();
        bool setDevice(int);
        bool setBaudRate(int);
        bool setParity(int);
        bool setFlowControl(int);
        bool setDataBits(int);
        bool setStopBits(int);
        void setDefaults();

        void sync();

        void startDevice();
        void stopDevice();

        std::string getDevices();

    private:
        int  interfac;
        int  baudrate;
        int  available;
        char parity;
        char flowctrl;
        char databits;
        char stopbits;

        QSerialPort device;
        QSerialPortInfo port;
        QList<QSerialPortInfo> portlist;
};

#endif // FLY_SERIAL_H
