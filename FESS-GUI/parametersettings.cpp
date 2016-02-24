#include "parametersettings.h"
#include "ui_parametersettings.h"

ParameterSettings::ParameterSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParameterSettings)
{
    ui->setupUi(this);
}

ParameterSettings::~ParameterSettings()
{
    delete ui;
}
