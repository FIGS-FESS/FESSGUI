#include "setpassworddialog.h"
#include "ui_setpassworddialog.h"
#include <QSettings>
#include <QString>
#include <QDebug>
#include <iostream>

SetPasswordDialog::SetPasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetPasswordDialog)
{
    ui->setupUi(this);
}

SetPasswordDialog::~SetPasswordDialog()
{
    delete ui;
}

void SetPasswordDialog::on_buttonBox_accepted()
{
    QSettings settings;
    //Check if old password exists
    if(settings.contains("password")){
        //Check if old password matches
        QString oldpw = settings.value("password", "").toString();
        if(QString::compare(oldpw, ui->lineEdit_oldPassword->text()) != 0)
            qDebug("Wrong old password provided");
    }
    //Check if new password matches confirm password

    //Set new password
}
