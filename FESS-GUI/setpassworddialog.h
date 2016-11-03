#ifndef SETPASSWORDDIALOG_H
#define SETPASSWORDDIALOG_H

// QT Libraries
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

bool passwordMatches(QString);
QString GetRandomString();

#endif // SETPASSWORDDIALOG_H
