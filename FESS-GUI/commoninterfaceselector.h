#ifndef COMMONINTERFACESELECTOR_H
#define COMMONINTERFACESELECTOR_H

#include <QDialog>
#include <QErrorMessage>
#include <QSerialPortInfo>

#include "demodevice.h"
#include "serialdevice.h"
#include "errormessages.h"
#include "commoninterfacemanager.h"
#include "ui_commoninterfaceselector.h"

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

    void setSerialPortsComboBoxIndex(int);
    void setSerialPortsComboBoxText(const QString &text);

private:
    Ui::CommonInterfaceSelector *ui;

    int serialPortIndex;
    CommonInterfaceManager* interfaceManager;

    QString serialPortTextValue;
    QErrorMessage* errorHandler;
    QList<QSerialPortInfo> serialPortList;

    void closeWindow();
    void setUpSignals();
    void setSerialPortsComboBox();
};

#endif // COMMONINTERFACESELECTOR_H
