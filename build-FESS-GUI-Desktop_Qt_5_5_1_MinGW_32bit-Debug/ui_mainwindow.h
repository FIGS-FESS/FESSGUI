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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionEdit;
    QAction *actionNormal;
    QAction *actionExpanded;
    QAction *actionMetric;
    QAction *actionEmperial;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *page_5;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_6;
    QLabel *label;
    QSlider *verticalSlider;
    QVBoxLayout *verticalLayout_7;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_3;
    QSlider *verticalSlider_2;
    QVBoxLayout *verticalLayout_9;
    QDoubleSpinBox *doubleSpinBox_2;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_5;
    QSlider *verticalSlider_3;
    QVBoxLayout *verticalLayout_11;
    QDoubleSpinBox *doubleSpinBox_3;
    QLabel *label_6;
    QPushButton *pushButton;
    QWidget *page_6;
    QVBoxLayout *verticalLayout_5;
    QCustomPlot *widget;
    QPushButton *pushButton_2;
    QVBoxLayout *verticalLayout;
    QPushButton *controlButton;
    QPushButton *configButton;
    QPushButton *performButton;
    QTextBrowser *textBrowser_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuOptions;
    QMenu *menuChange_Units;
    QMenu *menuView;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 583);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionEdit = new QAction(MainWindow);
        actionEdit->setObjectName(QStringLiteral("actionEdit"));
        actionNormal = new QAction(MainWindow);
        actionNormal->setObjectName(QStringLiteral("actionNormal"));
        actionExpanded = new QAction(MainWindow);
        actionExpanded->setObjectName(QStringLiteral("actionExpanded"));
        actionMetric = new QAction(MainWindow);
        actionMetric->setObjectName(QStringLiteral("actionMetric"));
        actionEmperial = new QAction(MainWindow);
        actionEmperial->setObjectName(QStringLiteral("actionEmperial"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page_5 = new QWidget();
        page_5->setObjectName(QStringLiteral("page_5"));
        verticalLayout_4 = new QVBoxLayout(page_5);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(9, 9, -1, 6);
        groupBox = new QGroupBox(page_5);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(48, 48, 48, 48);
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_6->addWidget(label, 0, Qt::AlignHCenter);

        verticalSlider = new QSlider(groupBox);
        verticalSlider->setObjectName(QStringLiteral("verticalSlider"));
        verticalSlider->setMinimumSize(QSize(0, 200));
        verticalSlider->setMaximum(50);
        verticalSlider->setSingleStep(1);
        verticalSlider->setPageStep(10);
        verticalSlider->setOrientation(Qt::Vertical);
        verticalSlider->setTickPosition(QSlider::TicksAbove);
        verticalSlider->setTickInterval(10);

        verticalLayout_6->addWidget(verticalSlider, 0, Qt::AlignHCenter);


        horizontalLayout_2->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(3);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        doubleSpinBox = new QDoubleSpinBox(groupBox);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBox->setMaximum(50);
        doubleSpinBox->setSingleStep(0.01);

        verticalLayout_7->addWidget(doubleSpinBox, 0, Qt::AlignLeft|Qt::AlignBottom);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_7->addWidget(label_2, 0, Qt::AlignLeft|Qt::AlignTop);


        horizontalLayout_2->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_8->addWidget(label_3, 0, Qt::AlignHCenter);

        verticalSlider_2 = new QSlider(groupBox);
        verticalSlider_2->setObjectName(QStringLiteral("verticalSlider_2"));
        verticalSlider_2->setMinimumSize(QSize(0, 200));
        verticalSlider_2->setMaximum(10);
        verticalSlider_2->setOrientation(Qt::Vertical);
        verticalSlider_2->setTickPosition(QSlider::TicksAbove);
        verticalSlider_2->setTickInterval(2);

        verticalLayout_8->addWidget(verticalSlider_2, 0, Qt::AlignHCenter);


        horizontalLayout_2->addLayout(verticalLayout_8);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(3);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        doubleSpinBox_2 = new QDoubleSpinBox(groupBox);
        doubleSpinBox_2->setObjectName(QStringLiteral("doubleSpinBox_2"));
        doubleSpinBox_2->setMaximum(10);
        doubleSpinBox_2->setSingleStep(0.01);

        verticalLayout_9->addWidget(doubleSpinBox_2, 0, Qt::AlignLeft|Qt::AlignBottom);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_9->addWidget(label_4, 0, Qt::AlignLeft|Qt::AlignTop);


        horizontalLayout_2->addLayout(verticalLayout_9);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_10->addWidget(label_5, 0, Qt::AlignHCenter);

        verticalSlider_3 = new QSlider(groupBox);
        verticalSlider_3->setObjectName(QStringLiteral("verticalSlider_3"));
        verticalSlider_3->setMinimumSize(QSize(0, 200));
        verticalSlider_3->setMaximum(5);
        verticalSlider_3->setOrientation(Qt::Vertical);
        verticalSlider_3->setTickPosition(QSlider::TicksAbove);
        verticalSlider_3->setTickInterval(1);

        verticalLayout_10->addWidget(verticalSlider_3, 0, Qt::AlignHCenter);


        horizontalLayout_2->addLayout(verticalLayout_10);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(3);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        doubleSpinBox_3 = new QDoubleSpinBox(groupBox);
        doubleSpinBox_3->setObjectName(QStringLiteral("doubleSpinBox_3"));
        doubleSpinBox_3->setMaximum(5);
        doubleSpinBox_3->setSingleStep(0.01);

        verticalLayout_11->addWidget(doubleSpinBox_3, 0, Qt::AlignLeft|Qt::AlignBottom);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_11->addWidget(label_6, 0, Qt::AlignLeft|Qt::AlignTop);


        horizontalLayout_2->addLayout(verticalLayout_11);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton, 0, Qt::AlignBottom);


        verticalLayout_4->addWidget(groupBox);

        stackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName(QStringLiteral("page_6"));
        verticalLayout_5 = new QVBoxLayout(page_6);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        widget = new QCustomPlot(page_6);
        widget->setObjectName(QStringLiteral("widget"));

        verticalLayout_5->addWidget(widget);

        stackedWidget->addWidget(page_6);

        gridLayout->addWidget(stackedWidget, 0, 1, 1, 1);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        pushButton_2->setMinimumSize(QSize(20, 70));
        QFont font;
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        pushButton_2->setFont(font);

        gridLayout->addWidget(pushButton_2, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        controlButton = new QPushButton(centralWidget);
        controlButton->setObjectName(QStringLiteral("controlButton"));
        controlButton->setMinimumSize(QSize(0, 40));

        verticalLayout->addWidget(controlButton);

        configButton = new QPushButton(centralWidget);
        configButton->setObjectName(QStringLiteral("configButton"));
        configButton->setMinimumSize(QSize(0, 40));

        verticalLayout->addWidget(configButton);

        performButton = new QPushButton(centralWidget);
        performButton->setObjectName(QStringLiteral("performButton"));
        performButton->setMinimumSize(QSize(0, 40));

        verticalLayout->addWidget(performButton, 0, Qt::AlignTop);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        textBrowser_2 = new QTextBrowser(centralWidget);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));

        gridLayout->addWidget(textBrowser_2, 0, 2, 2, 1);

        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 516, 69));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 1, 1, 1, 1, Qt::AlignBottom);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        menuChange_Units = new QMenu(menuOptions);
        menuChange_Units->setObjectName(QStringLiteral("menuChange_Units"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(performButton, configButton);
        QWidget::setTabOrder(configButton, controlButton);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuOptions->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionEdit);
        menuOptions->addAction(menuChange_Units->menuAction());
        menuChange_Units->addAction(actionMetric);
        menuChange_Units->addAction(actionEmperial);
        menuView->addAction(actionNormal);
        menuView->addAction(actionExpanded);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Flywheel Energy Storage System", 0));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0));
        actionEdit->setText(QApplication::translate("MainWindow", "Edit", 0));
        actionNormal->setText(QApplication::translate("MainWindow", "Normal", 0));
        actionExpanded->setText(QApplication::translate("MainWindow", "Expanded", 0));
        actionMetric->setText(QApplication::translate("MainWindow", "Metric", 0));
        actionEmperial->setText(QApplication::translate("MainWindow", "Emperial", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Controls", 0));
        label->setText(QApplication::translate("MainWindow", "Velocity", 0));
        label_2->setText(QApplication::translate("MainWindow", "rad/sec", 0));
        label_3->setText(QApplication::translate("MainWindow", "Acceleration", 0));
        label_4->setText(QApplication::translate("MainWindow", "rad/sec^2", 0));
        label_5->setText(QApplication::translate("MainWindow", "Jerk", 0));
        label_6->setText(QApplication::translate("MainWindow", "rad/sec^3", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Go", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Emergency\n"
"Stop", 0));
        controlButton->setText(QApplication::translate("MainWindow", "Control", 0));
        configButton->setText(QApplication::translate("MainWindow", "Performance\n"
"Monitor", 0));
        performButton->setText(QApplication::translate("MainWindow", "Configuration", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuOptions->setTitle(QApplication::translate("MainWindow", "Options", 0));
        menuChange_Units->setTitle(QApplication::translate("MainWindow", "Change Units", 0));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
