#ifndef COMMONINTERFACESELECTOR_H
#define COMMONINTERFACESELECTOR_H

#include <QDialog>
#include <QSerialPortInfo>

#include "commoninterfacemanager.h"

namespace Ui { class CommonInterfaceSelector;}

class CommonInterfaceSelector : public QDialog
{
    Q_OBJECT

public:
    explicit CommonInterfaceSelector(CommonInterfaceManager*, QWidget *parent = 0);
    ~CommonInterfaceSelector();

private slots:
    void demoButtonSetClicked();
    void demoButtonCancelClicked();

    void serialButtonSetClicked();
    void serialButtonCancelClicked();

private:
    Ui::CommonInterfaceSelector *ui;

    bool serialPortTextModified;

    CommonInterfaceManager* interfaceManager;
    QList<QSerialPortInfo> serialPortList;

    void closeWindow();
    void setUpSignals();
    void setSerialPortsComboBox();
};

#endif // COMMONINTERFACESELECTOR_H
