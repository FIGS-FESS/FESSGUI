#include <QtGui>
#include "demodevice.h"
#include "serialdevice.h"
#include "commoninterfaceselector.h"
#include "ui_commoninterfaceselector.h"

CommonInterfaceSelector::CommonInterfaceSelector(CommonInterfaceManager* interfaceManager, QWidget *parent) : QDialog(parent), ui(new Ui::CommonInterfaceSelector)
{
    ui->setupUi(this);

    interfaceManager = interfaceManager;
    serialPortTextModified = false;

    setUpSignals();
    setSerialPortsComboBox();
}

CommonInterfaceSelector::~CommonInterfaceSelector()
{
    delete ui;
}

// Private Functions

void CommonInterfaceSelector::closeWindow()
{
    this->close();
}

void CommonInterfaceSelector::setUpSignals()
{
    connect(ui->demoButtonSet,    SIGNAL(clicked()), SLOT(demoButtonSetClicked()));
    connect(ui->demoButtonCancel, SIGNAL(clicked()), SLOT(demoButtonCancelClicked()));

    connect(ui->serialButtonSet,    SIGNAL(clicked()), SLOT(serialButtonSetClicked()));
    connect(ui->serialButtonCancel, SIGNAL(clicked()), SLOT(serialButtonCancelClicked()));
}

void CommonInterfaceSelector::setSerialPortsComboBox()
{
    serialPortList = QSerialPortInfo::availablePorts();

    for (int i = 0; i < serialPortList.size(); i++)
    {
        ui->serialPortCombo->insertItem(i,serialPortList[i].portName());
    }
}

// Private Slots

void CommonInterfaceSelector::demoButtonSetClicked()
{
    int demo_port_index = ui->demoPortCombo->currentIndex();

    switch(demo_port_index)
    {
        case 0:
        {
            interfaceManager->getNewDemoDevice();
            break;
        }
        default: break;
    }

    closeWindow();
}

void CommonInterfaceSelector::demoButtonCancelClicked()
{
    closeWindow();
}

void CommonInterfaceSelector::serialButtonSetClicked()
{
    int serial_baud_rate = ui->serialBaudLine->text().toInt();
    int serial_data_index = ui->serialDataCombo->currentIndex();
    int serial_stop_index = ui->serialStopCombo->currentIndex();
    int serial_flow_index = ui->serialFlowCombo->currentIndex();
    int serial_port_index = ui->serialPortCombo->currentIndex();
    int serial_parity_index = ui->serialParityCombo->currentIndex();

    if (serial_port_index != -1)
    {
        if (serialPortTextModified)
        {
            QString serial_port_path = ui->serialPortCombo->currentText();

            SerialDevice* deviceInterface = interfaceManager->getNewSerialDevice(serial_port_path);
            deviceInterface->setBaudRate(serial_baud_rate);
            deviceInterface->setParity(serial_parity_index);
            deviceInterface->setDataBits(serial_data_index+5);
            deviceInterface->setStopBits(serial_stop_index);
            deviceInterface->setFlowControl(serial_flow_index);
        }
        else
        {
            SerialDevice* deviceInterface = interfaceManager->getNewSerialDevice();
            deviceInterface->setPort(serialPortList[serial_port_index]);
            deviceInterface->setBaudRate(serial_baud_rate);
            deviceInterface->setParity(serial_parity_index);
            deviceInterface->setDataBits(serial_data_index+5);
            deviceInterface->setStopBits(serial_stop_index);
            deviceInterface->setFlowControl(serial_flow_index);
        }
    }

    closeWindow();
}

void CommonInterfaceSelector::serialButtonCancelClicked()
{
    closeWindow();
}
