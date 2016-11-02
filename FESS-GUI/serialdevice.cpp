// Custom Libraries --------------------------------------------------
#include "serialdevice.h"

#include <QtGui>

//--------------------------------------------------------------------
// SerialDevice Constructors
//--------------------------------------------------------------------

SerialDevice::SerialDevice()
{
    device = new QSerialPort("/dev/pts/1");

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
            qDebug() << "Name : " << info.portName();
            qDebug() << "Description : " << info.description();
            qDebug() << "Manufacturer: " << info.manufacturer();
    }

    setDefaults();
}

SerialDevice::SerialDevice(QSerialPortInfo* port)
{
    device = new QSerialPort();
    setDefaults();
    setPort(port);
}

SerialDevice::SerialDevice(QSerialPortInfo* port, int baud)
{
    device = new QSerialPort();
    setDefaults();
    setPort(port);
    setBaudRate(baud);

}

SerialDevice::SerialDevice(QSerialPortInfo* port, int baud, int parity)
{
    device = new QSerialPort();
    setDefaults();
    setPort(port);
    setBaudRate(baud);
    setParity(parity);

}

SerialDevice::SerialDevice(QSerialPortInfo* port, int baud, int parity, int databits)
{
    device = new QSerialPort();
    setDefaults();
    setPort(port);
    setBaudRate(baud);
    setParity(parity);
    setDataBits(databits);
}

SerialDevice::SerialDevice(QSerialPortInfo* port, int baud, int parity, int databits, int stopbits)
{
    device = new QSerialPort();
    setDefaults();
    setPort(port);
    setBaudRate(baud);
    setParity(parity);
    setDataBits(databits);
    setStopBits(stopbits);
}

SerialDevice::SerialDevice(QSerialPortInfo* port, int baud, int parity, int databits, int stopbits, int flowcon)
{
    device = new QSerialPort();
    setPort(port);
    setBaudRate(baud);
    setParity(parity);
    setDataBits(databits);
    setStopBits(stopbits);
    setFlowControl(flowcon);
}

//--------------------------------------------------------------------
// SerialDevice Destructors
//--------------------------------------------------------------------

SerialDevice::~SerialDevice()
{
    stopDevice();
    delete device;
}

//--------------------------------------------------------------------
// Public
//--------------------------------------------------------------------

// SerialDevice Device Settings --------------------------------------------

void SerialDevice::setPort(QSerialPortInfo* port)
{
    device->setPort(*port);
}

void SerialDevice::setBaudRate(int rate)
{
    device->setBaudRate(rate,QSerialPort::AllDirections);
}

void SerialDevice::setParity(int pari)
{
    switch(pari)
    {
        case 0:
        {
            device->setParity(QSerialPort::NoParity);
            break;
        }
        case 1:
        {
            device->setParity(QSerialPort::OddParity);
            break;
        }

        case 2:
        {
            device->setParity(QSerialPort::EvenParity);
            break;
        }
        default:
        {
            break;
        }
    }
}

void SerialDevice::setFlowControl(int flow)
{
    switch(flow)
    {
        case 0:
        {
            device->setFlowControl(QSerialPort::NoFlowControl);
            break;
        }
        case 1:
        {
            device->setFlowControl(QSerialPort::HardwareControl);
            break;
        }

        case 2:
        {
            device->setFlowControl(QSerialPort::SoftwareControl);
            break;
        }
        default:
        {
            break;
        }
    }
}

void SerialDevice::setDataBits(int bits)
{
    switch(bits)
    {
        case 5:
        {
            device->setDataBits(QSerialPort::Data5);
            break;
        }

        case 6:
        {
            device->setDataBits(QSerialPort::Data6);
            break;
        }
        case 7:
        {
            device->setDataBits(QSerialPort::Data7);
            break;
        }

        case 8:
        {
            device->setDataBits(QSerialPort::Data8);
            break;
        }
        default:
        {
            break;
        }
    }
}

void SerialDevice::setStopBits(int bits)
{
    switch(bits)
    {
        case 1:
        {
            device->setStopBits(QSerialPort::OneStop);
            break;
        }

        case 2:
        {
            device->setStopBits(QSerialPort::TwoStop);
            break;
        }
        case 3:
        {
            device->setStopBits(QSerialPort::OneAndHalfStop);
            break;
        }
        default:
        {
            break;
        }
    }
}


//--------------------------------------------------------------------
// Private
//--------------------------------------------------------------------

// SerialDevice Device Send and Receive ----------------------------------


void SerialDevice::sendTX()
{
    while(!tx.empty())
    {
        device->putChar(tx.popByte());
    }

    device->waitForBytesWritten(0);
}

void SerialDevice::readRX()
{
    device->waitForReadyRead(0);

    QByteArray in = device->readAll();

    qDebug() << "Read:" << in;

    for (int i = 0; i < in.size(); i++)
    {
        rx.pushByte(in[i]);
    }
}


//--------------------------------------------------------------------
// Interface Overedload Functions
//--------------------------------------------------------------------

void SerialDevice::sync()
{
    sendTX();
    readRX();
}

void SerialDevice::startDevice()
{
    device->open(QIODevice::ReadWrite);
}

void SerialDevice::stopDevice()
{
    device->close();
}

void SerialDevice::setDefaults()
{
    setBaudRate(9600);
    setParity(0);
    setFlowControl(0);
    setDataBits(8);
    setStopBits(1);
}


flybyte SerialDevice::popCommand()
{
    return rx.popByte();
}


void SerialDevice::pushInt(int32_t val)
{
    tx.pushInt(val);
}

void SerialDevice::pushFloat(float val)
{
    tx.pushFloat(val);
}

void SerialDevice::pushCommand(flybyte byte)
{
    tx.pushByte(byte);
}

void SerialDevice::pushCommandImmediate(flybyte byte)
{
    tx.pushByteFront(byte);
    sendTX();
}


void SerialDevice::flush()
{
    rx.flush();
}

bool SerialDevice::empty()
{
    return rx.empty();
}
