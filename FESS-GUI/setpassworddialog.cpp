#include "setpassworddialog.h"
#include "ui_setpassworddialog.h"
#include <QSettings>
#include <QString>
#include <QDebug>
#include <QCryptographicHash>

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

        if(!passwordMatches(ui->lineEdit_oldPassword->text())){
            qDebug("Wrong old password provided");
            return;
        }
        //old password correct
    }

    //Check if new password matches confirm password and set new password
    if(QString::compare(ui->lineEdit_newPassword->text(), ui->lineEdit_confirmPassword->text()) == 0){
        QString salt = GetRandomString();
        QString pwHashed = QString(QCryptographicHash::hash(((ui->lineEdit_newPassword->text()+salt).toUtf8()),QCryptographicHash::Sha512).toHex());
        settings.setValue("password", pwHashed);
        settings.setValue("salt", salt);
    }

}

bool passwordsMatch(QString old, QString provided){
    QSettings settings("settings.ini", QSettings::IniFormat);
    if (!settings.contains("salt")){
        return false;
    }
    QString salt = settings.value("salt", "").toString();
    QString oldHashed = QString(QCryptographicHash::hash(((old+salt).toUtf8()),QCryptographicHash::Sha512).toHex());
    QString provHashed = QString(QCryptographicHash::hash(((provided+salt).toUtf8()),QCryptographicHash::Sha512).toHex());
    return (QString::compare(oldHashed, provHashed) == 0);
}

bool passwordMatches(QString prov){
    QSettings settings("settings.ini", QSettings::IniFormat);
    if (!settings.contains("salt")){
        return false;
    }
    if (!settings.contains("password")){
        return false;
    }
    QString salt = settings.value("salt", "").toString();
    QString oldPassHashed = settings.value("password", "").toString();
    QString provHashed = QString(QCryptographicHash::hash(((prov+salt).toUtf8()),QCryptographicHash::Sha512).toHex());
    return (QString::compare(oldPassHashed, provHashed) == 0);
}

QString GetRandomString()
{
   const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
   const int randomStringLength = 16 + (qrand() % 16); // assuming you want random strings of 12 characters

   QString randomString;
   for(int i=0; i<randomStringLength; ++i)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }
   return randomString;
}

