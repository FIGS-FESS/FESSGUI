#ifndef COMMONINTERFACEMANAGER_H
#define COMMONINTERFACEMANAGER_H

#include "demodevice.h"
#include "serialdevice.h"
#include "commondeviceinterface.h"

class CommonInterfaceManager
{
    public:

        CommonInterfaceManager();

        SerialDevice* getNewSerialDevice();
        SerialDevice* getNewSerialDevice(QString);

        DemoDevice* getNewDemoDevice();
        CommonDeviceInterface* getCurrentInterface();

        bool isADeviceSet();

   private:

        CommonDeviceInterface* currentDevice;
};

#endif // COMMONINTERFACEMANAGER_H
