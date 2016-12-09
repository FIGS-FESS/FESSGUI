/*! \brief CommonInterfaceManager Class
 *  Manages interfaces set in the interface selector menu
 */

#ifndef COMMONINTERFACEMANAGER_H
#define COMMONINTERFACEMANAGER_H

#include "commondeviceinterface.h"

class CommonInterfaceManager
{
    public:

        CommonInterfaceManager();
        ~CommonInterfaceManager();

        CommonDeviceInterface* getCurrentInterface();

        void setCurrentInterface(CommonDeviceInterface*);

        bool isADeviceSet();
        void closeCurrentInterface();

   private:

        CommonDeviceInterface* currentDevice;
};

#endif // COMMONINTERFACEMANAGER_H
