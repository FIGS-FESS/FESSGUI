/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDial>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAdjust_Paramaters;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_5;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout;
    QTextBrowser *textBrowser;
    QPushButton *pushButton;
    QLabel *label;
    QWidget *tab_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QSpinBox *spinBox;
    QLabel *label_5;
    QSpinBox *spinBox_2;
    QLabel *label_6;
    QPushButton *pushButton_2;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QSlider *horizontalSlider;
    QHBoxLayout *horizontalLayout_2;
    QDial *dial;
    QLabel *label_2;
    QWidget *tab_3;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QLCDNumber *lcdNumber;
    QMenuBar *menuBar;
    QMenu *menuSetting;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(656, 500);
        actionAdjust_Paramaters = new QAction(MainWindow);
        actionAdjust_Paramaters->setObjectName(QStringLiteral("actionAdjust_Paramaters"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_5 = new QVBoxLayout(centralWidget);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setStyleSheet(QStringLiteral(""));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_4 = new QVBoxLayout(tab);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        textBrowser = new QTextBrowser(tab);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        gridLayout->addWidget(textBrowser, 3, 0, 1, 1);

        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);

        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);


        verticalLayout_4->addLayout(gridLayout);

        tabWidget->addTab(tab, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        horizontalLayout_3 = new QHBoxLayout(tab_4);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_4 = new QLabel(tab_4);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        spinBox = new QSpinBox(tab_4);
        spinBox->setObjectName(QStringLiteral("spinBox"));

        horizontalLayout_3->addWidget(spinBox);

        label_5 = new QLabel(tab_4);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);

        spinBox_2 = new QSpinBox(tab_4);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));

        horizontalLayout_3->addWidget(spinBox_2);

        label_6 = new QLabel(tab_4);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_3->addWidget(label_6);

        pushButton_2 = new QPushButton(tab_4);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_3->addWidget(pushButton_2);

        tabWidget->addTab(tab_4, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        horizontalLayout = new QHBoxLayout(tab_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalSlider = new QSlider(tab_2);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setMinimum(1);
        horizontalSlider->setSliderPosition(12);
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(horizontalSlider);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        dial = new QDial(tab_2);
        dial->setObjectName(QStringLiteral("dial"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dial->sizePolicy().hasHeightForWidth());
        dial->setSizePolicy(sizePolicy);
        dial->setMinimumSize(QSize(50, 50));
        dial->setMaximumSize(QSize(100, 100));
        dial->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(dial, 0, Qt::AlignLeft|Qt::AlignTop);


        verticalLayout_2->addLayout(horizontalLayout_2);

        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);


        horizontalLayout->addLayout(verticalLayout_2);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout_2 = new QGridLayout(tab_3);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font;
        font.setPointSize(18);
        label_3->setFont(font);
        label_3->setContextMenuPolicy(Qt::CustomContextMenu);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());

        verticalLayout_5->addWidget(tabWidget);

        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));

        verticalLayout_5->addWidget(lcdNumber);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 656, 21));
        menuSetting = new QMenu(menuBar);
        menuSetting->setObjectName(QStringLiteral("menuSetting"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuSetting->menuAction());
        menuSetting->addAction(actionAdjust_Paramaters);
        mainToolBar->addAction(actionAdjust_Paramaters);

        retranslateUi(MainWindow);
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), lcdNumber, SLOT(display(int)));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionAdjust_Paramaters->setText(QApplication::translate("MainWindow", "Adjust Paramaters", 0));
        pushButton->setText(QApplication::translate("MainWindow", "If you push this, something exciting will happen.", 0));
        label->setText(QApplication::translate("MainWindow", "Here is where we will control the FESS.", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Controls", 0));
        label_4->setText(QApplication::translate("MainWindow", "Reach", 0));
        label_5->setText(QApplication::translate("MainWindow", "RPM with", 0));
        label_6->setText(QApplication::translate("MainWindow", "acceleration", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Go", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "Page", 0));
        label_2->setText(QApplication::translate("MainWindow", "OMG", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "More Controls", 0));
        label_3->setText(QApplication::translate("MainWindow", "Don't Press Spacebar", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Page of Death", 0));
        menuSetting->setTitle(QApplication::translate("MainWindow", "Settings", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
