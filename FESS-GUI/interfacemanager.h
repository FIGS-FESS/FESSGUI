#ifndef INTERFACEMANAGER_H
#define INTERFACEMANAGER_H

// C/C++ Libraries
#include <string>

// QT Libraries
#include <QSerialPortInfo>

// Custom Libraries
#include "commondeviceinterface.h"

class interfaceManager
{
    public:
        interfaceManager();
        ~interfaceManager();

        void findSerialDevices();
        void setCurrentDevices(int index);

        CommonDeviceInterface* getCurrentDevice();

    private:
        std::vector<CommonDeviceInterface*> interface_list;

        QSerialPortInfo* port;
        QList<QSerialPortInfo> serial_port_list;
};

#endif // INTERFACEMANAGER_H
