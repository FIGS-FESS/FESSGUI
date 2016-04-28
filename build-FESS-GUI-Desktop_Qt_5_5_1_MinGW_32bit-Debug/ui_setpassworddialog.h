/********************************************************************************
** Form generated from reading UI file 'setpassworddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETPASSWORDDIALOG_H
#define UI_SETPASSWORDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetPasswordDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_newPassword;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_confirmPassword;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEdit_oldPassword;

    void setupUi(QDialog *SetPasswordDialog)
    {
        if (SetPasswordDialog->objectName().isEmpty())
            SetPasswordDialog->setObjectName(QStringLiteral("SetPasswordDialog"));
        SetPasswordDialog->resize(404, 300);
        buttonBox = new QDialogButtonBox(SetPasswordDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(SetPasswordDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(120, 110, 151, 41));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2, 0, Qt::AlignHCenter);

        lineEdit_newPassword = new QLineEdit(layoutWidget);
        lineEdit_newPassword->setObjectName(QStringLiteral("lineEdit_newPassword"));
        lineEdit_newPassword->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(lineEdit_newPassword);

        layoutWidget_2 = new QWidget(SetPasswordDialog);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(120, 170, 151, 41));
        verticalLayout_3 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_3->addWidget(label_3, 0, Qt::AlignHCenter);

        lineEdit_confirmPassword = new QLineEdit(layoutWidget_2);
        lineEdit_confirmPassword->setObjectName(QStringLiteral("lineEdit_confirmPassword"));
        lineEdit_confirmPassword->setEchoMode(QLineEdit::Password);

        verticalLayout_3->addWidget(lineEdit_confirmPassword);

        layoutWidget1 = new QWidget(SetPasswordDialog);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(120, 30, 151, 61));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label, 0, Qt::AlignHCenter);

        lineEdit_oldPassword = new QLineEdit(layoutWidget1);
        lineEdit_oldPassword->setObjectName(QStringLiteral("lineEdit_oldPassword"));
        lineEdit_oldPassword->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(lineEdit_oldPassword);


        retranslateUi(SetPasswordDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SetPasswordDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SetPasswordDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SetPasswordDialog);
    } // setupUi

    void retranslateUi(QDialog *SetPasswordDialog)
    {
        SetPasswordDialog->setWindowTitle(QApplication::translate("SetPasswordDialog", "Set/Reset Password", 0));
        label_2->setText(QApplication::translate("SetPasswordDialog", "New Password", 0));
        label_3->setText(QApplication::translate("SetPasswordDialog", "Confirm New Password", 0));
        label->setText(QApplication::translate("SetPasswordDialog", "Old Password\n"
"(Blank if not set)", 0));
    } // retranslateUi

};

namespace Ui {
    class SetPasswordDialog: public Ui_SetPasswordDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETPASSWORDDIALOG_H
