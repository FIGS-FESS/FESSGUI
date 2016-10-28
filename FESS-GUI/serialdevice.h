#ifndef FLY_SERIAL_H
#define FLY_SERIAL_H

// QT Libraries
#include <QSerialPort>
#include <QSerialPortInfo>

// Custom Libraries
#include "datatypes.h"
#include "transmitbuffer.h"
#include "commondeviceinterface.h"


class SerialDevice : public CommonDeviceInterface
{
    public:
       SerialDevice();
       SerialDevice(QSerialPortInfo*);
       SerialDevice(QSerialPortInfo*, int);
       SerialDevice(QSerialPortInfo*, int, int);
       SerialDevice(QSerialPortInfo*, int, int, int);
       SerialDevice(QSerialPortInfo*, int, int, int, int);
       SerialDevice(QSerialPortInfo*, int, int, int, int, int);

        ~SerialDevice();

        // Overriden Interface Methods
        void sync();
        void startDevice();
        void stopDevice();
        void setDefaults();

        bool empty();
        void flush();
        void pushInt(int);
        void pushFloat(float);
        void pushCommand(flybyte);
        void pushCommandImmediate(flybyte);

        int popInt();
        float popFloat();
        flybyte popCommand();

        // Unique Methods
        void setDevice(int);
        void setBaudRate(int);
        void setParity(int);
        void setFlowControl(int);
        void setDataBits(int);
        void setStopBits(int);
        void setPort(QSerialPortInfo*);

    private:
        void sendTX();
        void readRX();

        // Internal variables
        QSerialPort* device;
        TransmitBuffer rx;
        TransmitBuffer tx;

};

#endif // FLY_SERIAL_H
