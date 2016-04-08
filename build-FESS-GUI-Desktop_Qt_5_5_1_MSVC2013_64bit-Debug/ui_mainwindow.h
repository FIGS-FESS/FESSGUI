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
    QVBoxLayout *verticalLayout;
    QPushButton *controlButton;
    QPushButton *configButton;
    QPushButton *performButton;
    QPushButton *pushButton_2;
    QStackedWidget *stackedWidget;
    QWidget *page_5;
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
    QWidget *page_6;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_7;
    QLabel *label_13;
    QLabel *label_12;
    QLabel *label_14;
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
    QWidget *ldtPage;
    QVBoxLayout *verticalLayout_15;
    QCustomPlot *mainUdtGraph;
    QWidget *udtPage;
    QVBoxLayout *verticalLayout_16;
    QCustomPlot *mainLdtGraph;
    QWidget *rotPage;
    QVBoxLayout *verticalLayout_17;
    QCustomPlot *mainRotGraph;
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
    QLabel *label_17;
    QCustomPlot *auxVelocGraph;
    QPushButton *velocButton;
    QLabel *label_18;
    QCustomPlot *auxAccelGraph;
    QPushButton *accelButton;
    QLabel *label_19;
    QCustomPlot *auxUpDtGraph;
    QPushButton *updtButton;
    QLabel *label_20;
    QCustomPlot *auxLowDtGraph;
    QPushButton *lowdtButton;
    QLabel *label_21;
    QCustomPlot *auxRotatGraph;
    QPushButton *rotatButton;
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
        MainWindow->resize(970, 700);
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

        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy1);
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

        stackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName(QStringLiteral("page_6"));
        verticalLayout_5 = new QVBoxLayout(page_6);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        groupBox_3 = new QGroupBox(page_6);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy2);
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(6);
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 1, 1, 1, 1, Qt::AlignBottom);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 1, 2, 1, 1, Qt::AlignBottom);

        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 1, 0, 1, 1, Qt::AlignBottom);

        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_2->addWidget(label_13, 2, 1, 1, 1, Qt::AlignTop);

        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_2->addWidget(label_12, 2, 0, 1, 1, Qt::AlignTop);

        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_2->addWidget(label_14, 2, 2, 1, 1, Qt::AlignTop);

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

        stackedWidget_2 = new QStackedWidget(groupBox_3);
        stackedWidget_2->setObjectName(QStringLiteral("stackedWidget_2"));
        velPage = new QWidget();
        velPage->setObjectName(QStringLiteral("velPage"));
        verticalLayout_13 = new QVBoxLayout(velPage);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        mainVelGraph = new QCustomPlot(velPage);
        mainVelGraph->setObjectName(QStringLiteral("mainVelGraph"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(mainVelGraph->sizePolicy().hasHeightForWidth());
        mainVelGraph->setSizePolicy(sizePolicy3);

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
        rotPage = new QWidget();
        rotPage->setObjectName(QStringLiteral("rotPage"));
        verticalLayout_17 = new QVBoxLayout(rotPage);
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setContentsMargins(11, 11, 11, 11);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        mainRotGraph = new QCustomPlot(rotPage);
        mainRotGraph->setObjectName(QStringLiteral("mainRotGraph"));

        verticalLayout_17->addWidget(mainRotGraph);

        stackedWidget_2->addWidget(rotPage);

        gridLayout_2->addWidget(stackedWidget_2, 0, 0, 1, 4);


        verticalLayout_5->addWidget(groupBox_3);

        stackedWidget->addWidget(page_6);

        gridLayout->addWidget(stackedWidget, 0, 1, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy4);
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
        groupBox_2->setMinimumSize(QSize(180, 0));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(12, -1, 12, -1);
        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setStyleSheet(QStringLiteral("font-size: 14px"));

        verticalLayout_2->addWidget(label_17);

        auxVelocGraph = new QCustomPlot(groupBox_2);
        auxVelocGraph->setObjectName(QStringLiteral("auxVelocGraph"));
        auxVelocGraph->setMinimumSize(QSize(0, 100));
        auxVelocGraph->setStyleSheet(QStringLiteral(""));
        velocButton = new QPushButton(auxVelocGraph);
        velocButton->setObjectName(QStringLiteral("velocButton"));
        velocButton->setGeometry(QRect(0, 0, 161, 101));
        velocButton->setStyleSheet(QLatin1String("background-color: transparent;\n"
"\n"
""));
        velocButton->setCheckable(false);

        verticalLayout_2->addWidget(auxVelocGraph);

        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setStyleSheet(QStringLiteral("color: grey"));

        verticalLayout_2->addWidget(label_18);

        auxAccelGraph = new QCustomPlot(groupBox_2);
        auxAccelGraph->setObjectName(QStringLiteral("auxAccelGraph"));
        auxAccelGraph->setMinimumSize(QSize(0, 100));
        auxAccelGraph->setStyleSheet(QStringLiteral(""));
        accelButton = new QPushButton(auxAccelGraph);
        accelButton->setObjectName(QStringLiteral("accelButton"));
        accelButton->setGeometry(QRect(0, 0, 151, 91));
        accelButton->setStyleSheet(QLatin1String("background-color: transparent;\n"
""));
        accelButton->setCheckable(false);
        accelButton->setChecked(false);
        accelButton->setAutoExclusive(false);

        verticalLayout_2->addWidget(auxAccelGraph);

        label_19 = new QLabel(groupBox_2);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setStyleSheet(QStringLiteral("color: grey"));

        verticalLayout_2->addWidget(label_19);

        auxUpDtGraph = new QCustomPlot(groupBox_2);
        auxUpDtGraph->setObjectName(QStringLiteral("auxUpDtGraph"));
        auxUpDtGraph->setMinimumSize(QSize(0, 100));
        updtButton = new QPushButton(auxUpDtGraph);
        updtButton->setObjectName(QStringLiteral("updtButton"));
        updtButton->setGeometry(QRect(4, 2, 151, 91));
        updtButton->setStyleSheet(QLatin1String("background-color: transparent;\n"
""));

        verticalLayout_2->addWidget(auxUpDtGraph);

        label_20 = new QLabel(groupBox_2);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setStyleSheet(QStringLiteral("color: grey"));

        verticalLayout_2->addWidget(label_20);

        auxLowDtGraph = new QCustomPlot(groupBox_2);
        auxLowDtGraph->setObjectName(QStringLiteral("auxLowDtGraph"));
        auxLowDtGraph->setMinimumSize(QSize(0, 100));
        lowdtButton = new QPushButton(auxLowDtGraph);
        lowdtButton->setObjectName(QStringLiteral("lowdtButton"));
        lowdtButton->setGeometry(QRect(4, 2, 151, 91));
        lowdtButton->setStyleSheet(QLatin1String("background-color: transparent;\n"
""));

        verticalLayout_2->addWidget(auxLowDtGraph);

        label_21 = new QLabel(groupBox_2);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setStyleSheet(QStringLiteral("color: grey"));

        verticalLayout_2->addWidget(label_21);

        auxRotatGraph = new QCustomPlot(groupBox_2);
        auxRotatGraph->setObjectName(QStringLiteral("auxRotatGraph"));
        auxRotatGraph->setMinimumSize(QSize(0, 100));
        rotatButton = new QPushButton(auxRotatGraph);
        rotatButton->setObjectName(QStringLiteral("rotatButton"));
        rotatButton->setGeometry(QRect(4, 2, 151, 91));
        rotatButton->setStyleSheet(QLatin1String("background-color: transparent;\n"
""));

        verticalLayout_2->addWidget(auxRotatGraph);


        gridLayout->addWidget(groupBox_2, 0, 2, 2, 1, Qt::AlignHCenter);

        MainWindow->setCentralWidget(centralWidget);
        groupBox_2->raise();
        pushButton_2->raise();
        stackedWidget->raise();
        tabWidget->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 970, 21));
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

        stackedWidget->setCurrentIndex(1);
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
        actionEmperial->setText(QApplication::translate("MainWindow", "Emperial", 0));
        actionNone->setText(QApplication::translate("MainWindow", "None", 0));
        actionDefault->setText(QApplication::translate("MainWindow", "Default", 0));
        actionDarth_Vader->setText(QApplication::translate("MainWindow", "Darth Vader", 0));
        controlButton->setText(QApplication::translate("MainWindow", "Control", 0));
        configButton->setText(QApplication::translate("MainWindow", "Performance\n"
"Monitor", 0));
        performButton->setText(QApplication::translate("MainWindow", "Configuration", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Emergency\n"
"Stop", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Control", 0));
        label->setText(QApplication::translate("MainWindow", "Velocity", 0));
        label_2->setText(QApplication::translate("MainWindow", "rad/sec", 0));
        label_3->setText(QApplication::translate("MainWindow", "Acceleration", 0));
        label_4->setText(QApplication::translate("MainWindow", "<html><head/><body><p>rad/sec<span style=\" vertical-align:super;\">2</span></p></body></html>", 0));
        label_5->setText(QApplication::translate("MainWindow", "Jerk", 0));
        label_6->setText(QApplication::translate("MainWindow", "<html><head/><body><p>rad/sec<span style=\" vertical-align:super;\">3</span></p></body></html>", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Go", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Performance Monitor", 0));
        label_8->setText(QApplication::translate("MainWindow", "Max Velocity", 0));
        label_9->setText(QApplication::translate("MainWindow", "Up Time", 0));
        label_7->setText(QApplication::translate("MainWindow", "Velocity", 0));
        label_13->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_12->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_14->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Legend", 0));
        label_11->setText(QApplication::translate("MainWindow", "Expected Value", 0));
        label_10->setText(QApplication::translate("MainWindow", "Measured Value", 0));
        label_15->setText(QApplication::translate("MainWindow", "Output Log", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QApplication::translate("MainWindow", "Output", 0));
        label_16->setText(QApplication::translate("MainWindow", "Error Log", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Errors", 0));
        groupBox_2->setTitle(QString());
        label_17->setText(QApplication::translate("MainWindow", "Velocity", 0));
        velocButton->setText(QString());
        label_18->setText(QApplication::translate("MainWindow", "Acceleration", 0));
        accelButton->setText(QString());
        label_19->setText(QApplication::translate("MainWindow", "Upper X/Y Displacement", 0));
        updtButton->setText(QString());
        label_20->setText(QApplication::translate("MainWindow", "Lower X/Y Displacement", 0));
        lowdtButton->setText(QString());
        label_21->setText(QApplication::translate("MainWindow", "Rotational Location", 0));
        rotatButton->setText(QString());
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
