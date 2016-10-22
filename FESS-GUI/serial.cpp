// Custom Libraries
#include "serial.h"

Serial::Serial()
{
    device = new QSerialPort("/dev/pts/1");
    setDefaults();
}

Serial::~Serial()
{
    delete device;
}

void Serial::setPort(QSerialPortInfo* port)
{
    device->setPort(*port);
}

void Serial::setBaudRate(int rate)
{
    device->setBaudRate(rate,QSerialPort::AllDirections);
}

void Serial::setParity(int pari)
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

void Serial::setFlowControl(int flow)
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

void Serial::setDataBits(int bits)
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

void Serial::setStopBits(int bits)
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

void Serial::setDefaults()
{
    setBaudRate(9600);
    setParity(0);
    setFlowControl(0);
    setDataBits(8);
    setStopBits(1);
}

void Serial::sync()
{
    sendTX();
    readRX();
}

void Serial::sendTX()
{
    while(!emptyTX())
    {
        device->putChar(popTX());
    }

    device->waitForBytesWritten(1);
}

void Serial::readRX()
{
    device->waitForReadyRead(1);

    QByteArray rx = device->readAll();

    for (int i = 0; i < rx.size(); i++)
    {
        pushRXChar(rx[i]);
    }
}

void Serial::startDevice()
{
    device->open(QIODevice::ReadWrite);
}

void Serial::stopDevice()
{
    device->close();
}
