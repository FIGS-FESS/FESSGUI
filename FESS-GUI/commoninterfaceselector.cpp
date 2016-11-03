#include <QtGui>
#include "demodevice.h"
#include "serialdevice.h"
#include "commoninterfaceselector.h"
#include "ui_commoninterfaceselector.h"

CommonInterfaceSelector::CommonInterfaceSelector(CommonInterfaceManager* interfaceManager, QWidget *parent) : QDialog(parent), ui(new Ui::CommonInterfaceSelector)
{
    ui->setupUi(this);

    interface_manager = interfaceManager;
    serial_port_text_modified = false;

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
    serial_port_list = QSerialPortInfo::availablePorts();

    for (int i = 0; i < serial_port_list.size(); i++)
    {
        ui->serialPortCombo->insertItem(i,serial_port_list[i].portName());
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
            interface_manager->getNewDemoDevice();
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
        if (serial_port_text_modified)
        {
            QString serial_port_path = ui->serialPortCombo->currentText();

            SerialDevice* device_interface = interface_manager->getNewSerialDevice(serial_port_path);
            device_interface->setBaudRate(serial_baud_rate);
            device_interface->setParity(serial_parity_index);
            device_interface->setDataBits(serial_data_index+5);
            device_interface->setStopBits(serial_stop_index);
            device_interface->setFlowControl(serial_flow_index);

            qDebug() << serial_port_path;
            qDebug() << serial_baud_rate;
            qDebug() << serial_data_index;
            qDebug() << serial_stop_index;
            qDebug() << serial_flow_index;
            qDebug() << serial_parity_index;
        }

        else
        {
            SerialDevice* device_interface = interface_manager->getNewSerialDevice();
            device_interface->setPort(serial_port_list[serial_port_index]);
            device_interface->setBaudRate(serial_baud_rate);
            device_interface->setParity(serial_parity_index);
            device_interface->setDataBits(serial_data_index+5);
            device_interface->setStopBits(serial_stop_index);
            device_interface->setFlowControl(serial_flow_index);

            qDebug() << serial_port_index;
            qDebug() << serial_baud_rate;
            qDebug() << serial_data_index;
            qDebug() << serial_stop_index;
            qDebug() << serial_flow_index;
            qDebug() << serial_parity_index;
        }
    }

    closeWindow();
}

void CommonInterfaceSelector::serialButtonCancelClicked()
{
    closeWindow();
}
