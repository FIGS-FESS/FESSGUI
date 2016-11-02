#include "commoninterfaceselector.h"
#include "ui_commoninterfaceselector.h"

CommonInterfaceSelector::CommonInterfaceSelector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CommonInterfaceSelector)
{
    ui->setupUi(this);
}

CommonInterfaceSelector::~CommonInterfaceSelector()
{
    delete ui;
}
