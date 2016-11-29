// Custom Libraries --------------------------------------------------
#include "serialdevice.h"

//--------------------------------------------------------------------
// SerialDevice Constructors
//--------------------------------------------------------------------

SerialDevice::SerialDevice()
{
    device = new QSerialPort();
    setDefaults();
}

SerialDevice::SerialDevice(QSerialPortInfo port)
{
    device = new QSerialPort();
    setDefaults();
    setPort(port);
}

SerialDevice::SerialDevice(QString path)
{
    device = new QSerialPort(path);
    setDefaults();
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

void SerialDevice::setPort(QSerialPortInfo port)
{
    device->setPort(port);
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
            device->setStopBits(QSerialPort::OneAndHalfStop);
            break;
        }

        case 3:
        {
            device->setStopBits(QSerialPort::TwoStop);
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

    for (int i = 0; i < in.size(); i++)
    {
        rx.pushByte(in[i]);
    }
}


//--------------------------------------------------------------------
// Interface Overedload Functions
//--------------------------------------------------------------------

void SerialDevice::syncRX()
{
    readRX();
}

void SerialDevice::syncTX()
{
    sendTX();
}

bool SerialDevice::isReady()
{
    return statusReady;
}

bool SerialDevice::startDevice()
{
    statusReady = device->open(QIODevice::ReadWrite);

    if (statusReady == true)
    {
        device->clear();
    }

    return statusReady;
}

void SerialDevice::stopDevice()
{
    if (statusReady == true)
    {

        statusReady = false;
        rx.flush();
        tx.flush();
        device->clear();
        device->close();
    }
}

void SerialDevice::setDefaults()
{
    statusReady = false;
    setBaudRate(9600);
    setParity(0);
    setFlowControl(0);
    setDataBits(8);
    setStopBits(1);
}

FlyByte SerialDevice::popByte()
{
    return rx.popByte();
}

FlyPacket SerialDevice::popPacket()
{
    return rx.popPacket();
}

void SerialDevice::pushByte(FlyByte dataByte)
{
    tx.pushByte(dataByte);
}

void SerialDevice::pushPacket(FlyPacket dataPacket)
{
    tx.pushPacket(dataPacket);
}

void SerialDevice::flush()
{
    rx.flush();
}

bool SerialDevice::empty()
{
    return rx.empty();
}


QString SerialDevice::name()
{
    if (device)
    {
        return QString("Serial Device: %1").arg(device->portName());
    }
    else
    {
        return QString("Serial Device: None");
    }
}
