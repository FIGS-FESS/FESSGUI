/********************************************************************************
** Form generated from reading UI file 'parametersettings.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETERSETTINGS_H
#define UI_PARAMETERSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_ParameterSettings
{
public:
    QDialogButtonBox *buttonBox;
    QComboBox *comboBox;

    void setupUi(QDialog *ParameterSettings)
    {
        if (ParameterSettings->objectName().isEmpty())
            ParameterSettings->setObjectName(QStringLiteral("ParameterSettings"));
        ParameterSettings->resize(400, 300);
        buttonBox = new QDialogButtonBox(ParameterSettings);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        comboBox = new QComboBox(ParameterSettings);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(150, 30, 69, 22));

        retranslateUi(ParameterSettings);
        QObject::connect(buttonBox, SIGNAL(accepted()), ParameterSettings, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ParameterSettings, SLOT(reject()));

        QMetaObject::connectSlotsByName(ParameterSettings);
    } // setupUi

    void retranslateUi(QDialog *ParameterSettings)
    {
        ParameterSettings->setWindowTitle(QApplication::translate("ParameterSettings", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class ParameterSettings: public Ui_ParameterSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETERSETTINGS_H
