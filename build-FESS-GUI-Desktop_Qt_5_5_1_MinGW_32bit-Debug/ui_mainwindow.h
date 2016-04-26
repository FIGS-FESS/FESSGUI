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
#include <QtWidgets/QKeySequenceEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
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
    QAction *actionStart_Recording;
    QAction *actionStop_Recording;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *configButton;
    QPushButton *controlButton;
    QPushButton *performButton;
    QStackedWidget *stackedWidget;
    QWidget *controlPage;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_6;
    QLabel *label;
    QSlider *verticalSlider;
    QVBoxLayout *verticalLayout_7;
    QDoubleSpinBox *velSpinBox;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_3;
    QSlider *verticalSlider_2;
    QVBoxLayout *verticalLayout_9;
    QDoubleSpinBox *accSpinBox;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_5;
    QSlider *verticalSlider_3;
    QVBoxLayout *verticalLayout_11;
    QDoubleSpinBox *doubleSpinBox_3;
    QLabel *label_6;
    QPushButton *pushButton;
    QWidget *monitorPage;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_7;
    QLabel *label_14;
    QLabel *label_8;
    QLabel *label_9;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    QLabel *label_11;
    QLabel *label_10;
    QStackedWidget *stackedWidget_2;
    QWidget *velPage;
    QVBoxLayout *verticalLayout_13;
    QCustomPlot *mainVelGraph;
    QWidget *accPage;
    QVBoxLayout *verticalLayout_14;
    QCustomPlot *mainAccGraph;
    QWidget *udtPage;
    QVBoxLayout *verticalLayout_16;
    QCustomPlot *mainLdtGraph;
    QWidget *ldtPage;
    QVBoxLayout *verticalLayout_15;
    QCustomPlot *mainUdtGraph;
    QWidget *xyPage;
    QVBoxLayout *verticalLayout_19;
    QCustomPlot *mainXYGraph;
    QWidget *rotPage;
    QVBoxLayout *verticalLayout_17;
    QCustomPlot *mainRotGraph;
    QWidget *configPage;
    QVBoxLayout *verticalLayout_18;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_4;
    QKeySequenceEdit *eStopKey;
    QLineEdit *maxVel;
    QLabel *label_22;
    QLabel *label_23;
    QLineEdit *maxAccel;
    QLabel *label_24;
    QLabel *label_25;
    QLineEdit *lineEdit;
    QPushButton *pushButton_2;
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QVBoxLayout *verticalLayout_12;
    QLabel *label_15;
    QTextBrowser *textBrowser;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_16;
    QTextBrowser *textBrowser_2;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *velLabel;
    QCustomPlot *auxVelocGraph;
    QPushButton *velocButton;
    QLabel *accLabel;
    QCustomPlot *auxAccelGraph;
    QPushButton *accelButton;
    QLabel *upDtLabel;
    QCustomPlot *auxUpDtGraph;
    QPushButton *updtButton;
    QLabel *lowDtLabel;
    QCustomPlot *auxLowDtGraph;
    QPushButton *lowdtButton;
    QLabel *xyLabel;
    QCustomPlot *auxXYGraph;
    QPushButton *XYButton;
    QLabel *rotLabel;
    QCustomPlot *auxRotatGraph;
    QPushButton *rotatButton;
    QMenuBar *menuBar;
    QMenu *menuOptions;
    QMenu *menuChange_Units;
    QMenu *menuSounds;
    QMenu *menuRecording;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1190, 710);
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
        actionStart_Recording = new QAction(MainWindow);
        actionStart_Recording->setObjectName(QStringLiteral("actionStart_Recording"));
        actionStop_Recording = new QAction(MainWindow);
        actionStop_Recording->setObjectName(QStringLiteral("actionStop_Recording"));
        actionStop_Recording->setEnabled(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        configButton = new QPushButton(centralWidget);
        configButton->setObjectName(QStringLiteral("configButton"));
        configButton->setMinimumSize(QSize(0, 45));

        verticalLayout->addWidget(configButton);

        controlButton = new QPushButton(centralWidget);
        controlButton->setObjectName(QStringLiteral("controlButton"));
        controlButton->setMinimumSize(QSize(0, 45));

        verticalLayout->addWidget(controlButton);

        performButton = new QPushButton(centralWidget);
        performButton->setObjectName(QStringLiteral("performButton"));
        performButton->setMinimumSize(QSize(100, 45));

        verticalLayout->addWidget(performButton, 0, Qt::AlignTop);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        controlPage = new QWidget();
        controlPage->setObjectName(QStringLiteral("controlPage"));
        verticalLayout_4 = new QVBoxLayout(controlPage);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(9, 9, -1, 6);
        groupBox = new QGroupBox(controlPage);
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
        velSpinBox = new QDoubleSpinBox(groupBox);
        velSpinBox->setObjectName(QStringLiteral("velSpinBox"));
        velSpinBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        velSpinBox->setMaximum(50);
        velSpinBox->setSingleStep(0.01);

        verticalLayout_7->addWidget(velSpinBox, 0, Qt::AlignLeft|Qt::AlignBottom);

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
        accSpinBox = new QDoubleSpinBox(groupBox);
        accSpinBox->setObjectName(QStringLiteral("accSpinBox"));
        accSpinBox->setMaximum(10);
        accSpinBox->setSingleStep(0.01);

        verticalLayout_9->addWidget(accSpinBox, 0, Qt::AlignLeft|Qt::AlignBottom);

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

        stackedWidget->addWidget(controlPage);
        monitorPage = new QWidget();
        monitorPage->setObjectName(QStringLiteral("monitorPage"));
        verticalLayout_5 = new QVBoxLayout(monitorPage);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        groupBox_3 = new QGroupBox(monitorPage);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(6);
        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_2->addWidget(label_12, 3, 0, 1, 1, Qt::AlignTop);

        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_2->addWidget(label_13, 3, 1, 1, 1, Qt::AlignTop);

        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 2, 0, 1, 1, Qt::AlignBottom);

        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_2->addWidget(label_14, 3, 2, 1, 1, Qt::AlignTop);

        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 2, 1, 1, 1, Qt::AlignBottom);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 2, 2, 1, 1, Qt::AlignBottom);

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


        gridLayout_2->addWidget(groupBox_4, 2, 3, 2, 1);

        stackedWidget_2 = new QStackedWidget(groupBox_3);
        stackedWidget_2->setObjectName(QStringLiteral("stackedWidget_2"));
        sizePolicy1.setHeightForWidth(stackedWidget_2->sizePolicy().hasHeightForWidth());
        stackedWidget_2->setSizePolicy(sizePolicy1);
        velPage = new QWidget();
        velPage->setObjectName(QStringLiteral("velPage"));
        verticalLayout_13 = new QVBoxLayout(velPage);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        mainVelGraph = new QCustomPlot(velPage);
        mainVelGraph->setObjectName(QStringLiteral("mainVelGraph"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(mainVelGraph->sizePolicy().hasHeightForWidth());
        mainVelGraph->setSizePolicy(sizePolicy2);

        verticalLayout_13->addWidget(mainVelGraph);

        stackedWidget_2->addWidget(velPage);
        accPage = new QWidget();
        accPage->setObjectName(QStringLiteral("accPage"));
        verticalLayout_14 = new QVBoxLayout(accPage);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        mainAccGraph = new QCustomPlot(accPage);
        mainAccGraph->setObjectName(QStringLiteral("mainAccGraph"));

        verticalLayout_14->addWidget(mainAccGraph);

        stackedWidget_2->addWidget(accPage);
        udtPage = new QWidget();
        udtPage->setObjectName(QStringLiteral("udtPage"));
        verticalLayout_16 = new QVBoxLayout(udtPage);
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setContentsMargins(11, 11, 11, 11);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        mainLdtGraph = new QCustomPlot(udtPage);
        mainLdtGraph->setObjectName(QStringLiteral("mainLdtGraph"));

        verticalLayout_16->addWidget(mainLdtGraph);

        stackedWidget_2->addWidget(udtPage);
        ldtPage = new QWidget();
        ldtPage->setObjectName(QStringLiteral("ldtPage"));
        verticalLayout_15 = new QVBoxLayout(ldtPage);
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setContentsMargins(11, 11, 11, 11);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        mainUdtGraph = new QCustomPlot(ldtPage);
        mainUdtGraph->setObjectName(QStringLiteral("mainUdtGraph"));

        verticalLayout_15->addWidget(mainUdtGraph);

        stackedWidget_2->addWidget(ldtPage);
        xyPage = new QWidget();
        xyPage->setObjectName(QStringLiteral("xyPage"));
        verticalLayout_19 = new QVBoxLayout(xyPage);
        verticalLayout_19->setSpacing(6);
        verticalLayout_19->setContentsMargins(11, 11, 11, 11);
        verticalLayout_19->setObjectName(QStringLiteral("verticalLayout_19"));
        mainXYGraph = new QCustomPlot(xyPage);
        mainXYGraph->setObjectName(QStringLiteral("mainXYGraph"));

        verticalLayout_19->addWidget(mainXYGraph);

        stackedWidget_2->addWidget(xyPage);
        rotPage = new QWidget();
        rotPage->setObjectName(QStringLiteral("rotPage"));
        sizePolicy1.setHeightForWidth(rotPage->sizePolicy().hasHeightForWidth());
        rotPage->setSizePolicy(sizePolicy1);
        verticalLayout_17 = new QVBoxLayout(rotPage);
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setContentsMargins(11, 11, 11, 11);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        mainRotGraph = new QCustomPlot(rotPage);
        mainRotGraph->setObjectName(QStringLiteral("mainRotGraph"));
        sizePolicy1.setHeightForWidth(mainRotGraph->sizePolicy().hasHeightForWidth());
        mainRotGraph->setSizePolicy(sizePolicy1);

        verticalLayout_17->addWidget(mainRotGraph);

        stackedWidget_2->addWidget(rotPage);

        gridLayout_2->addWidget(stackedWidget_2, 1, 0, 1, 4);


        verticalLayout_5->addWidget(groupBox_3);

        stackedWidget->addWidget(monitorPage);
        configPage = new QWidget();
        configPage->setObjectName(QStringLiteral("configPage"));
        verticalLayout_18 = new QVBoxLayout(configPage);
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setContentsMargins(11, 11, 11, 11);
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));
        groupBox_5 = new QGroupBox(configPage);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        gridLayout_4 = new QGridLayout(groupBox_5);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        eStopKey = new QKeySequenceEdit(groupBox_5);
        eStopKey->setObjectName(QStringLiteral("eStopKey"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(eStopKey->sizePolicy().hasHeightForWidth());
        eStopKey->setSizePolicy(sizePolicy3);

        gridLayout_4->addWidget(eStopKey, 0, 1, 1, 1);

        maxVel = new QLineEdit(groupBox_5);
        maxVel->setObjectName(QStringLiteral("maxVel"));
        sizePolicy3.setHeightForWidth(maxVel->sizePolicy().hasHeightForWidth());
        maxVel->setSizePolicy(sizePolicy3);
        maxVel->setInputMethodHints(Qt::ImhDigitsOnly);

        gridLayout_4->addWidget(maxVel, 1, 1, 1, 1);

        label_22 = new QLabel(groupBox_5);
        label_22->setObjectName(QStringLiteral("label_22"));

        gridLayout_4->addWidget(label_22, 0, 0, 1, 1);

        label_23 = new QLabel(groupBox_5);
        label_23->setObjectName(QStringLiteral("label_23"));

        gridLayout_4->addWidget(label_23, 1, 0, 1, 1);

        maxAccel = new QLineEdit(groupBox_5);
        maxAccel->setObjectName(QStringLiteral("maxAccel"));
        sizePolicy3.setHeightForWidth(maxAccel->sizePolicy().hasHeightForWidth());
        maxAccel->setSizePolicy(sizePolicy3);
        maxAccel->setInputMethodHints(Qt::ImhDigitsOnly);

        gridLayout_4->addWidget(maxAccel, 2, 1, 1, 1);

        label_24 = new QLabel(groupBox_5);
        label_24->setObjectName(QStringLiteral("label_24"));

        gridLayout_4->addWidget(label_24, 2, 0, 1, 1);

        label_25 = new QLabel(groupBox_5);
        label_25->setObjectName(QStringLiteral("label_25"));

        gridLayout_4->addWidget(label_25, 3, 0, 1, 1);

        lineEdit = new QLineEdit(groupBox_5);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        sizePolicy3.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy3);
        lineEdit->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        lineEdit->setReadOnly(false);

        gridLayout_4->addWidget(lineEdit, 3, 1, 1, 1);


        verticalLayout_18->addWidget(groupBox_5);

        stackedWidget->addWidget(configPage);

        gridLayout->addWidget(stackedWidget, 0, 1, 1, 1);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        sizePolicy3.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy3);
        pushButton_2->setMinimumSize(QSize(100, 100));
        QFont font;
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        pushButton_2->setFont(font);
        pushButton_2->setAutoDefault(true);

        gridLayout->addWidget(pushButton_2, 1, 0, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setMaximumSize(QSize(16777215, 200));
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

        gridLayout->addWidget(tabWidget, 1, 1, 1, 1);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy4);
        groupBox_2->setMinimumSize(QSize(180, 0));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        velLabel = new QLabel(groupBox_2);
        velLabel->setObjectName(QStringLiteral("velLabel"));
        velLabel->setStyleSheet(QStringLiteral("font-size: 14px"));

        verticalLayout_2->addWidget(velLabel);

        auxVelocGraph = new QCustomPlot(groupBox_2);
        auxVelocGraph->setObjectName(QStringLiteral("auxVelocGraph"));
        sizePolicy.setHeightForWidth(auxVelocGraph->sizePolicy().hasHeightForWidth());
        auxVelocGraph->setSizePolicy(sizePolicy);
        auxVelocGraph->setMinimumSize(QSize(0, 0));
        auxVelocGraph->setStyleSheet(QStringLiteral(""));
        velocButton = new QPushButton(auxVelocGraph);
        velocButton->setObjectName(QStringLiteral("velocButton"));
        velocButton->setGeometry(QRect(0, -20, 161, 111));
        sizePolicy.setHeightForWidth(velocButton->sizePolicy().hasHeightForWidth());
        velocButton->setSizePolicy(sizePolicy);
        velocButton->setStyleSheet(QLatin1String("background-color: transparent;\n"
"\n"
""));
        velocButton->setCheckable(false);

        verticalLayout_2->addWidget(auxVelocGraph);

        accLabel = new QLabel(groupBox_2);
        accLabel->setObjectName(QStringLiteral("accLabel"));
        accLabel->setStyleSheet(QStringLiteral("color: grey"));

        verticalLayout_2->addWidget(accLabel);

        auxAccelGraph = new QCustomPlot(groupBox_2);
        auxAccelGraph->setObjectName(QStringLiteral("auxAccelGraph"));
        sizePolicy.setHeightForWidth(auxAccelGraph->sizePolicy().hasHeightForWidth());
        auxAccelGraph->setSizePolicy(sizePolicy);
        auxAccelGraph->setMinimumSize(QSize(0, 0));
        auxAccelGraph->setStyleSheet(QStringLiteral(""));
        accelButton = new QPushButton(auxAccelGraph);
        accelButton->setObjectName(QStringLiteral("accelButton"));
        accelButton->setGeometry(QRect(0, -20, 161, 111));
        sizePolicy.setHeightForWidth(accelButton->sizePolicy().hasHeightForWidth());
        accelButton->setSizePolicy(sizePolicy);
        accelButton->setStyleSheet(QLatin1String("background-color: transparent;\n"
""));
        accelButton->setCheckable(false);
        accelButton->setChecked(false);
        accelButton->setAutoExclusive(false);

        verticalLayout_2->addWidget(auxAccelGraph);

        upDtLabel = new QLabel(groupBox_2);
        upDtLabel->setObjectName(QStringLiteral("upDtLabel"));
        upDtLabel->setStyleSheet(QStringLiteral("color: grey"));

        verticalLayout_2->addWidget(upDtLabel);

        auxUpDtGraph = new QCustomPlot(groupBox_2);
        auxUpDtGraph->setObjectName(QStringLiteral("auxUpDtGraph"));
        sizePolicy.setHeightForWidth(auxUpDtGraph->sizePolicy().hasHeightForWidth());
        auxUpDtGraph->setSizePolicy(sizePolicy);
        auxUpDtGraph->setMinimumSize(QSize(0, 0));
        auxUpDtGraph->setStyleSheet(QStringLiteral(""));
        updtButton = new QPushButton(auxUpDtGraph);
        updtButton->setObjectName(QStringLiteral("updtButton"));
        updtButton->setGeometry(QRect(0, -20, 161, 111));
        sizePolicy.setHeightForWidth(updtButton->sizePolicy().hasHeightForWidth());
        updtButton->setSizePolicy(sizePolicy);
        updtButton->setStyleSheet(QLatin1String("background-color: transparent;\n"
""));
        updtButton->setCheckable(false);
        updtButton->setChecked(false);
        updtButton->setAutoExclusive(false);

        verticalLayout_2->addWidget(auxUpDtGraph);

        lowDtLabel = new QLabel(groupBox_2);
        lowDtLabel->setObjectName(QStringLiteral("lowDtLabel"));
        lowDtLabel->setStyleSheet(QStringLiteral("color: grey"));

        verticalLayout_2->addWidget(lowDtLabel);

        auxLowDtGraph = new QCustomPlot(groupBox_2);
        auxLowDtGraph->setObjectName(QStringLiteral("auxLowDtGraph"));
        sizePolicy.setHeightForWidth(auxLowDtGraph->sizePolicy().hasHeightForWidth());
        auxLowDtGraph->setSizePolicy(sizePolicy);
        auxLowDtGraph->setMinimumSize(QSize(0, 0));
        lowdtButton = new QPushButton(auxLowDtGraph);
        lowdtButton->setObjectName(QStringLiteral("lowdtButton"));
        lowdtButton->setGeometry(QRect(0, -20, 161, 111));
        sizePolicy.setHeightForWidth(lowdtButton->sizePolicy().hasHeightForWidth());
        lowdtButton->setSizePolicy(sizePolicy);
        lowdtButton->setStyleSheet(QLatin1String("background-color: transparent;\n"
""));

        verticalLayout_2->addWidget(auxLowDtGraph);

        xyLabel = new QLabel(groupBox_2);
        xyLabel->setObjectName(QStringLiteral("xyLabel"));
        xyLabel->setStyleSheet(QStringLiteral("color: grey"));

        verticalLayout_2->addWidget(xyLabel);

        auxXYGraph = new QCustomPlot(groupBox_2);
        auxXYGraph->setObjectName(QStringLiteral("auxXYGraph"));
        sizePolicy.setHeightForWidth(auxXYGraph->sizePolicy().hasHeightForWidth());
        auxXYGraph->setSizePolicy(sizePolicy);
        auxXYGraph->setMinimumSize(QSize(0, 0));
        XYButton = new QPushButton(auxXYGraph);
        XYButton->setObjectName(QStringLiteral("XYButton"));
        XYButton->setGeometry(QRect(0, -10, 161, 101));
        sizePolicy.setHeightForWidth(XYButton->sizePolicy().hasHeightForWidth());
        XYButton->setSizePolicy(sizePolicy);
        XYButton->setStyleSheet(QLatin1String("background-color: transparent;\n"
""));

        verticalLayout_2->addWidget(auxXYGraph);

        rotLabel = new QLabel(groupBox_2);
        rotLabel->setObjectName(QStringLiteral("rotLabel"));
        rotLabel->setStyleSheet(QStringLiteral("color: grey"));

        verticalLayout_2->addWidget(rotLabel);

        auxRotatGraph = new QCustomPlot(groupBox_2);
        auxRotatGraph->setObjectName(QStringLiteral("auxRotatGraph"));
        sizePolicy.setHeightForWidth(auxRotatGraph->sizePolicy().hasHeightForWidth());
        auxRotatGraph->setSizePolicy(sizePolicy);
        auxRotatGraph->setMinimumSize(QSize(0, 0));
        rotatButton = new QPushButton(auxRotatGraph);
        rotatButton->setObjectName(QStringLiteral("rotatButton"));
        rotatButton->setGeometry(QRect(0, -20, 161, 111));
        sizePolicy.setHeightForWidth(rotatButton->sizePolicy().hasHeightForWidth());
        rotatButton->setSizePolicy(sizePolicy);
        rotatButton->setStyleSheet(QLatin1String("background-color: transparent;\n"
""));

        verticalLayout_2->addWidget(auxRotatGraph);

        rotLabel->raise();
        xyLabel->raise();
        lowDtLabel->raise();
        upDtLabel->raise();
        accLabel->raise();
        velLabel->raise();
        auxVelocGraph->raise();
        auxAccelGraph->raise();
        auxLowDtGraph->raise();
        auxXYGraph->raise();
        auxRotatGraph->raise();
        auxUpDtGraph->raise();

        gridLayout->addWidget(groupBox_2, 0, 2, 2, 1, Qt::AlignHCenter);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1190, 21));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        menuChange_Units = new QMenu(menuOptions);
        menuChange_Units->setObjectName(QStringLiteral("menuChange_Units"));
        menuSounds = new QMenu(menuOptions);
        menuSounds->setObjectName(QStringLiteral("menuSounds"));
        menuRecording = new QMenu(menuBar);
        menuRecording->setObjectName(QStringLiteral("menuRecording"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(performButton, controlButton);

        menuBar->addAction(menuOptions->menuAction());
        menuBar->addAction(menuRecording->menuAction());
        menuOptions->addAction(menuChange_Units->menuAction());
        menuOptions->addAction(menuSounds->menuAction());
        menuChange_Units->addAction(actionMetric);
        menuChange_Units->addAction(actionEmperial);
        menuSounds->addAction(actionNone);
        menuSounds->addAction(actionDefault);
        menuSounds->addAction(actionDarth_Vader);
        menuRecording->addAction(actionStart_Recording);
        menuRecording->addAction(actionStop_Recording);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);
        stackedWidget_2->setCurrentIndex(0);
        pushButton_2->setDefault(false);
        tabWidget->setCurrentIndex(0);


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
        actionEmperial->setText(QApplication::translate("MainWindow", "Imperial", 0));
        actionNone->setText(QApplication::translate("MainWindow", "None", 0));
        actionDefault->setText(QApplication::translate("MainWindow", "Default", 0));
        actionDarth_Vader->setText(QApplication::translate("MainWindow", "Darth Vader", 0));
        actionStart_Recording->setText(QApplication::translate("MainWindow", "Start Recording", 0));
        actionStop_Recording->setText(QApplication::translate("MainWindow", "Stop Recording", 0));
        configButton->setText(QApplication::translate("MainWindow", "Performance\n"
"Monitor", 0));
        controlButton->setText(QApplication::translate("MainWindow", "Control", 0));
        performButton->setText(QApplication::translate("MainWindow", "Configuration", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Control", 0));
        label->setText(QApplication::translate("MainWindow", "Velocity", 0));
        label_2->setText(QApplication::translate("MainWindow", "rad/sec", 0));
        label_3->setText(QApplication::translate("MainWindow", "Acceleration", 0));
        label_4->setText(QApplication::translate("MainWindow", "<html><head/><body><p>rad/sec<span style=\" vertical-align:super;\">2</span></p></body></html>", 0));
        label_5->setText(QApplication::translate("MainWindow", "Jerk", 0));
        label_6->setText(QApplication::translate("MainWindow", "<html><head/><body><p>rad/sec<span style=\" vertical-align:super;\">3</span></p></body></html>", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Go", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Performance Monitor", 0));
        label_12->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_13->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_7->setText(QApplication::translate("MainWindow", "Velocity", 0));
        label_14->setText(QApplication::translate("MainWindow", "0", 0));
        label_8->setText(QApplication::translate("MainWindow", "Max Velocity", 0));
        label_9->setText(QApplication::translate("MainWindow", "Up Time (s)", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Legend", 0));
        label_11->setText(QApplication::translate("MainWindow", "Expected Value", 0));
        label_10->setText(QApplication::translate("MainWindow", "Measured Value", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Configuration", 0));
        label_22->setText(QApplication::translate("MainWindow", "Emergency Stop Button", 0));
        label_23->setText(QApplication::translate("MainWindow", "Maximum Velocity (rad/s)", 0));
        label_24->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Maximum Acceleration (rad/s<span style=\" vertical-align:super;\">2</span>)</p></body></html>", 0));
        label_25->setText(QApplication::translate("MainWindow", "Password", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Emergency\n"
"Stop", 0));
        label_15->setText(QApplication::translate("MainWindow", "Output Log", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QApplication::translate("MainWindow", "Output", 0));
        label_16->setText(QApplication::translate("MainWindow", "Error Log", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Errors", 0));
        groupBox_2->setTitle(QString());
        velLabel->setText(QApplication::translate("MainWindow", "Velocity", 0));
        velocButton->setText(QString());
        accLabel->setText(QApplication::translate("MainWindow", "Acceleration", 0));
        accelButton->setText(QString());
        upDtLabel->setText(QApplication::translate("MainWindow", "Upper X/Y Displacement", 0));
        updtButton->setText(QString());
        lowDtLabel->setText(QApplication::translate("MainWindow", "Lower X/Y Displacement", 0));
        lowdtButton->setText(QString());
        xyLabel->setText(QApplication::translate("MainWindow", "X/Y Displacement", 0));
        XYButton->setText(QString());
        rotLabel->setText(QApplication::translate("MainWindow", "Rotational Location", 0));
        rotatButton->setText(QString());
        menuOptions->setTitle(QApplication::translate("MainWindow", "Options", 0));
        menuChange_Units->setTitle(QApplication::translate("MainWindow", "Change Units", 0));
        menuSounds->setTitle(QApplication::translate("MainWindow", "Sounds", 0));
        menuRecording->setTitle(QApplication::translate("MainWindow", "Recording", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
