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
#include <QtWidgets/QSlider>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
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
    QAction *actionNone;
    QAction *actionDefault;
    QAction *actionDarth_Vader;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QVBoxLayout *verticalLayout_12;
    QLabel *label_15;
    QTextBrowser *textBrowser;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_16;
    QTextBrowser *textBrowser_2;
    QTextBrowser *textBrowser_3;
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
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QCustomPlot *maingraph;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    QLabel *label_11;
    QLabel *label_10;
    QVBoxLayout *verticalLayout;
    QPushButton *controlButton;
    QPushButton *configButton;
    QPushButton *performButton;
    QPushButton *pushButton_2;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_17;
    QCustomPlot *auxgraph1;
    QLabel *label_18;
    QCustomPlot *auxgraph2;
    QGroupBox *groupBox_5;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_Record;
    QPushButton *pushButton_StopRecording;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuOptions;
    QMenu *menuChange_Units;
    QMenu *menuSounds;
    QMenu *menuView;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(802, 577);
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
        actionMetric->setCheckable(true);
        actionMetric->setChecked(true);
        actionEmperial = new QAction(MainWindow);
        actionEmperial->setObjectName(QStringLiteral("actionEmperial"));
        actionEmperial->setCheckable(true);
        actionNone = new QAction(MainWindow);
        actionNone->setObjectName(QStringLiteral("actionNone"));
        actionNone->setCheckable(true);
        actionNone->setChecked(true);
        actionDefault = new QAction(MainWindow);
        actionDefault->setObjectName(QStringLiteral("actionDefault"));
        actionDefault->setCheckable(true);
        actionDarth_Vader = new QAction(MainWindow);
        actionDarth_Vader->setObjectName(QStringLiteral("actionDarth_Vader"));
        actionDarth_Vader->setCheckable(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setTabPosition(QTabWidget::South);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tab_1 = new QWidget();
        tab_1->setObjectName(QStringLiteral("tab_1"));
        verticalLayout_12 = new QVBoxLayout(tab_1);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        label_15 = new QLabel(tab_1);
        label_15->setObjectName(QStringLiteral("label_15"));

        verticalLayout_12->addWidget(label_15);

        textBrowser = new QTextBrowser(tab_1);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout_12->addWidget(textBrowser);

        tabWidget->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_16 = new QLabel(tab_2);
        label_16->setObjectName(QStringLiteral("label_16"));

        verticalLayout_3->addWidget(label_16);

        textBrowser_2 = new QTextBrowser(tab_2);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));
        textBrowser_2->setLineWidth(1);

        verticalLayout_3->addWidget(textBrowser_2);

        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 2, 1, 1, 1);

        textBrowser_3 = new QTextBrowser(centralWidget);
        textBrowser_3->setObjectName(QStringLiteral("textBrowser_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textBrowser_3->sizePolicy().hasHeightForWidth());
        textBrowser_3->setSizePolicy(sizePolicy1);
        textBrowser_3->setMinimumSize(QSize(0, 26));
        textBrowser_3->setStyleSheet(QStringLiteral("background-color:rgb(0, 255, 0);"));

        gridLayout->addWidget(textBrowser_3, 0, 0, 1, 3);

        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy2);
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
        groupBox_3 = new QGroupBox(page_6);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy3);
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(6);
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 1, 0, 1, 1, Qt::AlignBottom);

        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 1, 1, 1, 1, Qt::AlignBottom);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 1, 2, 1, 1, Qt::AlignBottom);

        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_2->addWidget(label_12, 2, 0, 1, 1, Qt::AlignTop);

        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_2->addWidget(label_13, 2, 1, 1, 1, Qt::AlignTop);

        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_2->addWidget(label_14, 2, 2, 1, 1, Qt::AlignTop);

        maingraph = new QCustomPlot(groupBox_3);
        maingraph->setObjectName(QStringLiteral("maingraph"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(maingraph->sizePolicy().hasHeightForWidth());
        maingraph->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(maingraph, 0, 0, 1, 4);

        groupBox_4 = new QGroupBox(groupBox_3);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_3 = new QGridLayout(groupBox_4);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_3->addWidget(label_11, 2, 0, 1, 1);

        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_3->addWidget(label_10, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_4, 1, 3, 2, 1);


        verticalLayout_5->addWidget(groupBox_3);

        stackedWidget->addWidget(page_6);

        gridLayout->addWidget(stackedWidget, 1, 1, 1, 1);

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


        gridLayout->addLayout(verticalLayout, 1, 0, 1, 1);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy5);
        pushButton_2->setMinimumSize(QSize(20, 70));
        QFont font;
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        pushButton_2->setFont(font);

        gridLayout->addWidget(pushButton_2, 2, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(180, 0));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 9, -1, 9);
        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QStringLiteral("label_17"));

        verticalLayout_2->addWidget(label_17, 0, Qt::AlignBottom);

        auxgraph1 = new QCustomPlot(groupBox_2);
        auxgraph1->setObjectName(QStringLiteral("auxgraph1"));
        auxgraph1->setMinimumSize(QSize(0, 130));

        verticalLayout_2->addWidget(auxgraph1, 0, Qt::AlignVCenter);

        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QStringLiteral("label_18"));

        verticalLayout_2->addWidget(label_18, 0, Qt::AlignBottom);

        auxgraph2 = new QCustomPlot(groupBox_2);
        auxgraph2->setObjectName(QStringLiteral("auxgraph2"));
        auxgraph2->setMinimumSize(QSize(0, 130));

        verticalLayout_2->addWidget(auxgraph2, 0, Qt::AlignVCenter);


        gridLayout->addWidget(groupBox_2, 1, 2, 1, 1);

        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        horizontalLayoutWidget = new QWidget(groupBox_5);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 20, 170, 111));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_Record = new QPushButton(horizontalLayoutWidget);
        pushButton_Record->setObjectName(QStringLiteral("pushButton_Record"));

        horizontalLayout->addWidget(pushButton_Record);

        pushButton_StopRecording = new QPushButton(horizontalLayoutWidget);
        pushButton_StopRecording->setObjectName(QStringLiteral("pushButton_StopRecording"));
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(pushButton_StopRecording->sizePolicy().hasHeightForWidth());
        pushButton_StopRecording->setSizePolicy(sizePolicy6);
        pushButton_StopRecording->setMinimumSize(QSize(0, 0));

        horizontalLayout->addWidget(pushButton_StopRecording);


        gridLayout->addWidget(groupBox_5, 2, 2, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 802, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        menuChange_Units = new QMenu(menuOptions);
        menuChange_Units->setObjectName(QStringLiteral("menuChange_Units"));
        menuSounds = new QMenu(menuOptions);
        menuSounds->setObjectName(QStringLiteral("menuSounds"));
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
        menuOptions->addAction(menuSounds->menuAction());
        menuChange_Units->addAction(actionMetric);
        menuChange_Units->addAction(actionEmperial);
        menuSounds->addAction(actionNone);
        menuSounds->addAction(actionDefault);
        menuSounds->addAction(actionDarth_Vader);
        menuView->addAction(actionNormal);
        menuView->addAction(actionExpanded);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "FlyCAM - Flywheel Control and Monitoring", 0));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0));
        actionEdit->setText(QApplication::translate("MainWindow", "Edit", 0));
        actionNormal->setText(QApplication::translate("MainWindow", "Normal", 0));
        actionExpanded->setText(QApplication::translate("MainWindow", "Expanded", 0));
        actionMetric->setText(QApplication::translate("MainWindow", "Metric", 0));
        actionEmperial->setText(QApplication::translate("MainWindow", "Emperial", 0));
        actionNone->setText(QApplication::translate("MainWindow", "None", 0));
        actionDefault->setText(QApplication::translate("MainWindow", "Default", 0));
        actionDarth_Vader->setText(QApplication::translate("MainWindow", "Darth Vader", 0));
        label_15->setText(QApplication::translate("MainWindow", "Output Log", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QApplication::translate("MainWindow", "Output", 0));
        label_16->setText(QApplication::translate("MainWindow", "Error Log", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Errors", 0));
        textBrowser_3->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">No errors detected</span></p></body></html>", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Control", 0));
        label->setText(QApplication::translate("MainWindow", "Velocity", 0));
        label_2->setText(QApplication::translate("MainWindow", "rad/sec", 0));
        label_3->setText(QApplication::translate("MainWindow", "Acceleration", 0));
        label_4->setText(QApplication::translate("MainWindow", "<html><head/><body><p>rad/sec<span style=\" vertical-align:super;\">2</span></p></body></html>", 0));
        label_5->setText(QApplication::translate("MainWindow", "Jerk", 0));
        label_6->setText(QApplication::translate("MainWindow", "<html><head/><body><p>rad/sec<span style=\" vertical-align:super;\">3</span></p></body></html>", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Go", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Performance Monitor", 0));
        label_7->setText(QApplication::translate("MainWindow", "Velocity", 0));
        label_8->setText(QApplication::translate("MainWindow", "Max Velocity", 0));
        label_9->setText(QApplication::translate("MainWindow", "Up Time", 0));
        label_12->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_13->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_14->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Legend", 0));
        label_11->setText(QApplication::translate("MainWindow", "Expected Value", 0));
        label_10->setText(QApplication::translate("MainWindow", "Measured Value", 0));
        controlButton->setText(QApplication::translate("MainWindow", "Control", 0));
        configButton->setText(QApplication::translate("MainWindow", "Performance\n"
"Monitor", 0));
        performButton->setText(QApplication::translate("MainWindow", "Configuration", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Emergency\n"
"Stop", 0));
        groupBox_2->setTitle(QString());
        label_17->setText(QApplication::translate("MainWindow", "Velocity", 0));
        label_18->setText(QApplication::translate("MainWindow", "Acceleration", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "GroupBox", 0));
        pushButton_Record->setText(QApplication::translate("MainWindow", "Record", 0));
        pushButton_StopRecording->setText(QApplication::translate("MainWindow", "Stop Recording", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuOptions->setTitle(QApplication::translate("MainWindow", "Options", 0));
        menuChange_Units->setTitle(QApplication::translate("MainWindow", "Change Units", 0));
        menuSounds->setTitle(QApplication::translate("MainWindow", "Sounds", 0));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
