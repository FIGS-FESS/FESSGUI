#ifndef FLY_SERIAL_H
#define FLY_SERIAL_H

// QT Libraries
#include <QSerialPort>
#include <QSerialPortInfo>

// Custom Libraries
#include "interface.h"
#include "transmitbuffer.h"

class Serial : public Interface
{
    public:
        Serial();
        ~Serial();

        // Overriden Interface Methods
        void sync();
        void startDevice();
        void stopDevice();
        void setDefaults();

        bool empty();
        void flush();
        void pushInt(int);
        void pushFloat(float);
        void pushCommand(unsigned char);
        void pushCommandImmediate(unsigned char);

        int popInt();
        float popFloat();
        unsigned char popCommand();

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
