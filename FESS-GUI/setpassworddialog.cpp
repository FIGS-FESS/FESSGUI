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
    QSettings settings("settings.ini", QSettings::IniFormat);
    //qDebug(settings.fileName().toLocal8Bit());
    //Check if old password exists
    if(settings.contains("password")){
        //Check if old password matches
        QString oldpw = settings.value("password", "").toString();
        if(QString::compare(oldpw, ui->lineEdit_oldPassword->text()) != 0){
            qDebug("Wrong old password provided");
            return;
        }
        //old password correct
    }
    //Check if new password matches confirm password and set new password
    if(QString::compare(ui->lineEdit_newPassword->text(), ui->lineEdit_confirmPassword->text()) == 0){
        settings.setValue("password", ui->lineEdit_newPassword->text());
        qDebug("Password set to "+ui->lineEdit_newPassword->text().toLocal8Bit());
        qDebug(settings.value("password", "").toString().toLocal8Bit());
    }
}
