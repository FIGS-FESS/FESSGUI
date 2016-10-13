// THIS Header
#include "serial.h"

Serial::Serial()
{
    getDevices();
    setDefaults();
}

Serial::~Serial()
{

}

bool Serial::getDevices()
{
    portlist = QSerialPortInfo::availablePorts();
    available = portlist.size();

    if (available > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Serial::setDevice(int interface)
{
    if ((available > 0) && (available >= interface) && (interface >= 0))
    {
        port = portlist[interface];
        device.setPort(port);
        return true;
    }
    return false;
}

bool Serial::setBaudRate(int rate)
{
    return device.setBaudRate(rate,QSerialPort::AllDirections);
}

bool Serial::setParity(int pari)
{
    switch(pari)
    {
        case 0:
        {
            device.setParity(QSerialPort::NoParity);
            return true;
            break;
        }
        case 1:
        {
            device.setParity(QSerialPort::OddParity);
            return true;
            break;
        }

        case 2:
        {
            device.setParity(QSerialPort::EvenParity);
            return true;
            break;
        }
        default:
        {
            return false;
            break;
        }
    }
}

bool Serial::setFlowControl(int flow)
{
    switch(flow)
    {
        case 0:
        {
            device.setFlowControl(QSerialPort::NoFlowControl);
            return true;
            break;
        }
        case 1:
        {
            device.setFlowControl(QSerialPort::HardwareControl);
            return true;
            break;
        }

        case 2:
        {
            device.setFlowControl(QSerialPort::SoftwareControl);
            return true;
            break;
        }
        default:
        {
            return false;
            break;
        }
    }
}

bool Serial::setDataBits(int bits)
{
    switch(bits)
    {
        case 5:
        {
            device.setDataBits(QSerialPort::Data5);
            return true;
            break;
        }

        case 6:
        {
            device.setDataBits(QSerialPort::Data6);
            return true;
            break;
        }
        case 7:
        {
            device.setDataBits(QSerialPort::Data7);
            return true;
            break;
        }

        case 8:
        {
            device.setDataBits(QSerialPort::Data8);
            return true;
            break;
        }
        default:
        {
            return false;
            break;
        }
    }
}

bool Serial::setStopBits(int bits)
{
    switch(bits)
    {
        case 1:
        {
            device.setStopBits(QSerialPort::OneStop);
            return true;
            break;
        }

        case 2:
        {
            device.setStopBits(QSerialPort::TwoStop);
            return true;
            break;
        }
        case 3:
        {
            device.setStopBits(QSerialPort::OneAndHalfStop);
            return true;
            break;
        }
        default:
        {
            return false;
            break;
        }
    }
}

void Serial::setDefaults()
{
    setDevice(0);
    setBaudRate(9600);
    setParity(0);
    setFlowControl(0);
    setDataBits(8);
    setStopBits(1);

    qDebug() << "Serial: Searching for Devices";

    // Example use QSerialPortInfo
    foreach (const QSerialPortInfo &info, portlist)
    {
        qDebug() << "Name : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();

        // Example use QSerialPort

    //    device.setPort(info);

     //   if (device.open(QIODevice::ReadWrite))
     //   {
     //       device.putChar('a');
     //       device.flush();

            //qDebug() << "Read:" << device.readAll();

     //       device.close();
     //   }
    }

    qDebug() << "Serial: Done";

}

void Serial::syncDevice()
{
    char val;

    while(!internalEmpty())
    {
        val = internalPop();
        qDebug() << "Value:" << val;
        device.putChar(val);
        device.flush();
    }
}

void Serial::startDevice()
{
    device.setPort(port);
    device.open(QIODevice::ReadWrite);
}

void Serial::stopDevice()
{
    device.close();
}
