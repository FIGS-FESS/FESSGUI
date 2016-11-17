// QT Libraries
#include <QSettings>
#include <QString>
#include <QDebug>
#include <QCryptographicHash>
#include <QTime>

// Custom Libraries
#include "setpassworddialog.h"
#include "ui_setpassworddialog.h"


/*!
 * \brief SetPasswordDialog::SetPasswordDialog Constructs the object.
 * \param parent The parent widget (should be the mainWindow).
 */
SetPasswordDialog::SetPasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetPasswordDialog)
{
    ui->setupUi(this);
}

/*!
 * \brief SetPasswordDialog::~SetPasswordDialog Destructs the object.
 */
SetPasswordDialog::~SetPasswordDialog()
{
    delete ui;
}

/*!
 * \brief SetPasswordDialog::on_buttonBox_accepted Handles submission of the dialog.
 * Checks if the old password field matches the previously set password.
 * Checks that the new password matches its confirmation.
 * Salts and hashes the new password, then stores it in the settings.
 */
void SetPasswordDialog::on_buttonBox_accepted()
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    //qDebug(settings.fileName().toLocal8Bit());
    //Check if old password exists
    if(settings.contains("password")){
        //Check if old password matches
        QString oldpw = settings.value("password", "").toString();

        if(!passwordMatches(ui->lineEdit_oldPassword->text())){
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

/*!
 * \brief passwordMatches Checks if a provided password matches the set password.
 * \param prov A provided password that will be checked.
 * \return True if the provided password matches the set password. False otherwise.
 */
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

/*!
 * \brief GetRandomString Generates a random string of letters and numbers of size 16 - 32.
 * \return The generated random string.
 */
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
