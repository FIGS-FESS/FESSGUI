#ifndef SETPASSWORDDIALOG_H
#define SETPASSWORDDIALOG_H

#include <QDialog>

namespace Ui {
class SetPasswordDialog;
}

class SetPasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetPasswordDialog(QWidget *parent = 0);
    ~SetPasswordDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SetPasswordDialog *ui;
};

#endif // SETPASSWORDDIALOG_H
