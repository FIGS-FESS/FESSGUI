#include "commoninterfacemanager.h"

CommonInterfaceManager::CommonInterfaceManager()
{
    currentDevice = NULL;
}

SerialDevice* CommonInterfaceManager::getNewSerialDevice()
{
    SerialDevice* interface = new SerialDevice();
    currentDevice = interface;
    return interface;
}

SerialDevice* CommonInterfaceManager::getNewSerialDevice(QString port)
{
    SerialDevice* interface = new SerialDevice(port);
    currentDevice = interface;
    return interface;
}

DemoDevice* CommonInterfaceManager::getNewDemoDevice()
{
    DemoDevice* interface = new DemoDevice();
    currentDevice = interface;
    return interface;
}

CommonDeviceInterface* CommonInterfaceManager::getCurrentInterface()
{
    return currentDevice;
}

 bool CommonInterfaceManager::isADeviceSet()
 {
     if(currentDevice != NULL)
     {
         return true;
     }
     else
     {
         return false;
     }
}

void CommonInterfaceManager::closeCurrentInterface()
{
    delete currentDevice;
    currentDevice = NULL;
}
