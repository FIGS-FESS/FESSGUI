#ifndef COMMONINTERFACESELECTOR_H
#define COMMONINTERFACESELECTOR_H

#include <QDialog>

namespace Ui {
class CommonInterfaceSelector;
}

class CommonInterfaceSelector : public QDialog
{
    Q_OBJECT

public:
    explicit CommonInterfaceSelector(QWidget *parent = 0);
    ~CommonInterfaceSelector();

private:
    Ui::CommonInterfaceSelector *ui;
};

#endif // COMMONINTERFACESELECTOR_H
