/*! \brief The Serial Class
 * Provides access to serial interfaces.
 */

#ifndef FLY_SERIAL_H
#define FLY_SERIAL_H

// QT Libraries
#include <QString>
#include <QSerialPort>
#include <QSerialPortInfo>

// Custom Libraries
#include "transmitbuffer.h"
#include "commondeviceinterface.h"


class SerialDevice : public CommonDeviceInterface
{
    public:
       SerialDevice();

       SerialDevice(QSerialPortInfo);
       SerialDevice(QSerialPortInfo, int, int, int, int, int);

       SerialDevice(QString);
       SerialDevice(QString, int, int, int, int, int);

        ~SerialDevice();

        // Overriden Interface Methods
        void syncRX();
        void syncTX();
        bool isReady();
        bool startDevice();
        void stopDevice();
        void setDefaults();

        bool empty();
        void flushRX();
        void flushTX();
        void pushByte(FlyByte);
        void pushPacket(FlyPacket);

        FlyByte popByte();
        FlyPacket popPacket();

        QString name();

        // Unique Methods
        void setDevice(int);
        void setBaudRate(int);
        void setParity(int);
        void setFlowControl(int);
        void setDataBits(int);
        void setStopBits(int);
        void setPort(QSerialPortInfo);

    private:
        void sendTX();
        void readRX();

        bool statusReady;

        // Internal variables
        QSerialPort* device;
        TransmitBuffer rx;
        TransmitBuffer tx;

};

#endif // FLY_SERIAL_H
