#ifndef PARAMETERSETTINGS_H
#define PARAMETERSETTINGS_H

#include <QDialog>

namespace Ui {
class ParameterSettings;
}

class ParameterSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ParameterSettings(QWidget *parent = 0);
    ~ParameterSettings();

private:
    Ui::ParameterSettings *ui;
};

#endif // PARAMETERSETTINGS_H
