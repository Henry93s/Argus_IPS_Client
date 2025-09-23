/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *DashboardTab;
    QGridLayout *gridLayout_2;
    QFrame *WebcamStatusFrame;
    QHBoxLayout *horizontalLayout;
    QLabel *CamPowerLabel;
    QLabel *CommandStatusIPLabel;
    QLabel *CameraStatusLabel;
    QTableView *liveThreatFeedTableView;
    QFrame *frame;
    QVBoxLayout *verticalLayout_4;
    QLabel *ThreatTypePChartLabel;
    QGraphicsView *ThreatTypePChartGraphicsView;
    QLabel *HozTopAttackerTop5Label;
    QGraphicsView *HozTopAttackerTop5GraphicsView;
    QLabel *ThreatTypePChartLabel_2;
    QGraphicsView *HozTopTargetPortTop5GraphicsView;
    QFrame *StatusAndChartFrame;
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter;
    QLabel *ActiveSessionCountLabel;
    QLCDNumber *ActiveSessionCountLcdNumber;
    QLabel *BannedIPCountLabel;
    QLCDNumber *BannedIPCountLcdNumber;
    QLabel *ThreatCountLabel;
    QLCDNumber *ThreatCountLcdNumber;
    QLabel *label;
    QGraphicsView *ThreatBarChartGraphicsView;
    QWidget *AlertTab;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QCheckBox *dateTimeFromOnOff;
    QDateTimeEdit *dateTimeFrom;
    QLabel *label_4;
    QCheckBox *dateTimeUntilOnOff;
    QDateTimeEdit *dateTimeUntil;
    QComboBox *comboBox;
    QRadioButton *radioAlert;
    QRadioButton *radioDrop;
    QRadioButton *radioReject;
    QLabel *label_16;
    QComboBox *SeveritySelect;
    QLabel *protocolName;
    QComboBox *ProtocolSelect;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QLineEdit *SrcIP1;
    QLabel *label_7;
    QLineEdit *SrcIP2;
    QLabel *label_8;
    QLineEdit *SrcIP3;
    QLabel *label_9;
    QLineEdit *SrcIP4;
    QLabel *label_10;
    QLineEdit *DestIP1;
    QLabel *label_11;
    QLineEdit *DestIP2;
    QLabel *label_12;
    QLineEdit *DestIP3;
    QLabel *label_13;
    QLineEdit *DestIP4;
    QLabel *label_14;
    QLineEdit *SrcPort;
    QLabel *label_15;
    QLineEdit *DestPort;
    QSpacerItem *horizontalSpacer_4;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer_6;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QCheckBox *checkBox_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_8;
    QListWidget *AlertList;
    QWidget *SessionTab;
    QGridLayout *gridLayout_4;
    QWidget *widget_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 800);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1200, 800));
        MainWindow->setMaximumSize(QSize(1200, 800));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        DashboardTab = new QWidget();
        DashboardTab->setObjectName("DashboardTab");
        gridLayout_2 = new QGridLayout(DashboardTab);
        gridLayout_2->setObjectName("gridLayout_2");
        WebcamStatusFrame = new QFrame(DashboardTab);
        WebcamStatusFrame->setObjectName("WebcamStatusFrame");
        WebcamStatusFrame->setFrameShape(QFrame::Shape::StyledPanel);
        WebcamStatusFrame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout = new QHBoxLayout(WebcamStatusFrame);
        horizontalLayout->setObjectName("horizontalLayout");
        CamPowerLabel = new QLabel(WebcamStatusFrame);
        CamPowerLabel->setObjectName("CamPowerLabel");

        horizontalLayout->addWidget(CamPowerLabel);

        CommandStatusIPLabel = new QLabel(WebcamStatusFrame);
        CommandStatusIPLabel->setObjectName("CommandStatusIPLabel");

        horizontalLayout->addWidget(CommandStatusIPLabel);

        CameraStatusLabel = new QLabel(WebcamStatusFrame);
        CameraStatusLabel->setObjectName("CameraStatusLabel");

        horizontalLayout->addWidget(CameraStatusLabel);


        gridLayout_2->addWidget(WebcamStatusFrame, 0, 0, 1, 2);

        liveThreatFeedTableView = new QTableView(DashboardTab);
        liveThreatFeedTableView->setObjectName("liveThreatFeedTableView");
        liveThreatFeedTableView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        liveThreatFeedTableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        gridLayout_2->addWidget(liveThreatFeedTableView, 1, 0, 1, 1);

        frame = new QFrame(DashboardTab);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_4 = new QVBoxLayout(frame);
        verticalLayout_4->setObjectName("verticalLayout_4");
        ThreatTypePChartLabel = new QLabel(frame);
        ThreatTypePChartLabel->setObjectName("ThreatTypePChartLabel");

        verticalLayout_4->addWidget(ThreatTypePChartLabel);

        ThreatTypePChartGraphicsView = new QGraphicsView(frame);
        ThreatTypePChartGraphicsView->setObjectName("ThreatTypePChartGraphicsView");

        verticalLayout_4->addWidget(ThreatTypePChartGraphicsView);

        HozTopAttackerTop5Label = new QLabel(frame);
        HozTopAttackerTop5Label->setObjectName("HozTopAttackerTop5Label");

        verticalLayout_4->addWidget(HozTopAttackerTop5Label);

        HozTopAttackerTop5GraphicsView = new QGraphicsView(frame);
        HozTopAttackerTop5GraphicsView->setObjectName("HozTopAttackerTop5GraphicsView");

        verticalLayout_4->addWidget(HozTopAttackerTop5GraphicsView);

        ThreatTypePChartLabel_2 = new QLabel(frame);
        ThreatTypePChartLabel_2->setObjectName("ThreatTypePChartLabel_2");

        verticalLayout_4->addWidget(ThreatTypePChartLabel_2);

        HozTopTargetPortTop5GraphicsView = new QGraphicsView(frame);
        HozTopTargetPortTop5GraphicsView->setObjectName("HozTopTargetPortTop5GraphicsView");

        verticalLayout_4->addWidget(HozTopTargetPortTop5GraphicsView);


        gridLayout_2->addWidget(frame, 1, 1, 2, 1);

        StatusAndChartFrame = new QFrame(DashboardTab);
        StatusAndChartFrame->setObjectName("StatusAndChartFrame");
        StatusAndChartFrame->setFrameShape(QFrame::Shape::StyledPanel);
        StatusAndChartFrame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_3 = new QVBoxLayout(StatusAndChartFrame);
        verticalLayout_3->setObjectName("verticalLayout_3");
        splitter = new QSplitter(StatusAndChartFrame);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        ActiveSessionCountLabel = new QLabel(splitter);
        ActiveSessionCountLabel->setObjectName("ActiveSessionCountLabel");
        splitter->addWidget(ActiveSessionCountLabel);
        ActiveSessionCountLcdNumber = new QLCDNumber(splitter);
        ActiveSessionCountLcdNumber->setObjectName("ActiveSessionCountLcdNumber");
        splitter->addWidget(ActiveSessionCountLcdNumber);
        BannedIPCountLabel = new QLabel(splitter);
        BannedIPCountLabel->setObjectName("BannedIPCountLabel");
        splitter->addWidget(BannedIPCountLabel);
        BannedIPCountLcdNumber = new QLCDNumber(splitter);
        BannedIPCountLcdNumber->setObjectName("BannedIPCountLcdNumber");
        splitter->addWidget(BannedIPCountLcdNumber);
        ThreatCountLabel = new QLabel(splitter);
        ThreatCountLabel->setObjectName("ThreatCountLabel");
        splitter->addWidget(ThreatCountLabel);
        ThreatCountLcdNumber = new QLCDNumber(splitter);
        ThreatCountLcdNumber->setObjectName("ThreatCountLcdNumber");
        splitter->addWidget(ThreatCountLcdNumber);

        verticalLayout_3->addWidget(splitter);

        label = new QLabel(StatusAndChartFrame);
        label->setObjectName("label");

        verticalLayout_3->addWidget(label);

        ThreatBarChartGraphicsView = new QGraphicsView(StatusAndChartFrame);
        ThreatBarChartGraphicsView->setObjectName("ThreatBarChartGraphicsView");

        verticalLayout_3->addWidget(ThreatBarChartGraphicsView);


        gridLayout_2->addWidget(StatusAndChartFrame, 2, 0, 1, 1);

        tabWidget->addTab(DashboardTab, QString());
        AlertTab = new QWidget();
        AlertTab->setObjectName("AlertTab");
        verticalLayout_2 = new QVBoxLayout(AlertTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        widget = new QWidget(AlertTab);
        widget->setObjectName("widget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy1);
        widget->setMinimumSize(QSize(0, 50));
        widget->setMaximumSize(QSize(16777215, 500));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setMaximumSize(QSize(60, 16777215));
        QFont font;
        font.setPointSize(11);
        label_3->setFont(font);

        horizontalLayout_3->addWidget(label_3);

        dateTimeFromOnOff = new QCheckBox(widget);
        dateTimeFromOnOff->setObjectName("dateTimeFromOnOff");
        dateTimeFromOnOff->setMinimumSize(QSize(15, 0));
        dateTimeFromOnOff->setMaximumSize(QSize(15, 16777215));

        horizontalLayout_3->addWidget(dateTimeFromOnOff);

        dateTimeFrom = new QDateTimeEdit(widget);
        dateTimeFrom->setObjectName("dateTimeFrom");

        horizontalLayout_3->addWidget(dateTimeFrom);

        label_4 = new QLabel(widget);
        label_4->setObjectName("label_4");
        label_4->setMaximumSize(QSize(10, 16777215));

        horizontalLayout_3->addWidget(label_4);

        dateTimeUntilOnOff = new QCheckBox(widget);
        dateTimeUntilOnOff->setObjectName("dateTimeUntilOnOff");
        dateTimeUntilOnOff->setMaximumSize(QSize(15, 16777215));

        horizontalLayout_3->addWidget(dateTimeUntilOnOff);

        dateTimeUntil = new QDateTimeEdit(widget);
        dateTimeUntil->setObjectName("dateTimeUntil");

        horizontalLayout_3->addWidget(dateTimeUntil);

        comboBox = new QComboBox(widget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        horizontalLayout_3->addWidget(comboBox);

        radioAlert = new QRadioButton(widget);
        radioAlert->setObjectName("radioAlert");
        radioAlert->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_3->addWidget(radioAlert);

        radioDrop = new QRadioButton(widget);
        radioDrop->setObjectName("radioDrop");
        radioDrop->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_3->addWidget(radioDrop);

        radioReject = new QRadioButton(widget);
        radioReject->setObjectName("radioReject");
        radioReject->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_3->addWidget(radioReject);

        label_16 = new QLabel(widget);
        label_16->setObjectName("label_16");

        horizontalLayout_3->addWidget(label_16);

        SeveritySelect = new QComboBox(widget);
        SeveritySelect->addItem(QString());
        SeveritySelect->addItem(QString());
        SeveritySelect->addItem(QString());
        SeveritySelect->addItem(QString());
        SeveritySelect->setObjectName("SeveritySelect");

        horizontalLayout_3->addWidget(SeveritySelect);

        protocolName = new QLabel(widget);
        protocolName->setObjectName("protocolName");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(protocolName->sizePolicy().hasHeightForWidth());
        protocolName->setSizePolicy(sizePolicy3);
        protocolName->setMinimumSize(QSize(60, 0));

        horizontalLayout_3->addWidget(protocolName);

        ProtocolSelect = new QComboBox(widget);
        ProtocolSelect->addItem(QString());
        ProtocolSelect->addItem(QString());
        ProtocolSelect->addItem(QString());
        ProtocolSelect->addItem(QString());
        ProtocolSelect->setObjectName("ProtocolSelect");

        horizontalLayout_3->addWidget(ProtocolSelect);

        horizontalSpacer_2 = new QSpacerItem(30, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_2->addWidget(widget);

        widget_2 = new QWidget(AlertTab);
        widget_2->setObjectName("widget_2");
        sizePolicy1.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy1);
        widget_2->setMinimumSize(QSize(0, 50));
        widget_2->setMaximumSize(QSize(16777215, 50));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_6 = new QLabel(widget_2);
        label_6->setObjectName("label_6");
        sizePolicy3.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy3);
        label_6->setFont(font);

        horizontalLayout_2->addWidget(label_6);

        SrcIP1 = new QLineEdit(widget_2);
        SrcIP1->setObjectName("SrcIP1");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(SrcIP1->sizePolicy().hasHeightForWidth());
        SrcIP1->setSizePolicy(sizePolicy4);
        SrcIP1->setMinimumSize(QSize(40, 0));
        SrcIP1->setMaximumSize(QSize(40, 16777215));
        SrcIP1->setFont(font);

        horizontalLayout_2->addWidget(SrcIP1);

        label_7 = new QLabel(widget_2);
        label_7->setObjectName("label_7");
        sizePolicy2.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy2);
        label_7->setMaximumSize(QSize(15, 16777215));

        horizontalLayout_2->addWidget(label_7);

        SrcIP2 = new QLineEdit(widget_2);
        SrcIP2->setObjectName("SrcIP2");
        sizePolicy4.setHeightForWidth(SrcIP2->sizePolicy().hasHeightForWidth());
        SrcIP2->setSizePolicy(sizePolicy4);
        SrcIP2->setMinimumSize(QSize(40, 0));
        SrcIP2->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_2->addWidget(SrcIP2);

        label_8 = new QLabel(widget_2);
        label_8->setObjectName("label_8");
        sizePolicy2.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy2);
        label_8->setMaximumSize(QSize(15, 16777215));

        horizontalLayout_2->addWidget(label_8);

        SrcIP3 = new QLineEdit(widget_2);
        SrcIP3->setObjectName("SrcIP3");
        sizePolicy4.setHeightForWidth(SrcIP3->sizePolicy().hasHeightForWidth());
        SrcIP3->setSizePolicy(sizePolicy4);
        SrcIP3->setMinimumSize(QSize(40, 0));
        SrcIP3->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_2->addWidget(SrcIP3);

        label_9 = new QLabel(widget_2);
        label_9->setObjectName("label_9");

        horizontalLayout_2->addWidget(label_9);

        SrcIP4 = new QLineEdit(widget_2);
        SrcIP4->setObjectName("SrcIP4");
        sizePolicy4.setHeightForWidth(SrcIP4->sizePolicy().hasHeightForWidth());
        SrcIP4->setSizePolicy(sizePolicy4);
        SrcIP4->setMinimumSize(QSize(40, 0));
        SrcIP4->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_2->addWidget(SrcIP4);

        label_10 = new QLabel(widget_2);
        label_10->setObjectName("label_10");

        horizontalLayout_2->addWidget(label_10);

        DestIP1 = new QLineEdit(widget_2);
        DestIP1->setObjectName("DestIP1");
        sizePolicy4.setHeightForWidth(DestIP1->sizePolicy().hasHeightForWidth());
        DestIP1->setSizePolicy(sizePolicy4);
        DestIP1->setMinimumSize(QSize(40, 0));
        DestIP1->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_2->addWidget(DestIP1);

        label_11 = new QLabel(widget_2);
        label_11->setObjectName("label_11");

        horizontalLayout_2->addWidget(label_11);

        DestIP2 = new QLineEdit(widget_2);
        DestIP2->setObjectName("DestIP2");
        sizePolicy4.setHeightForWidth(DestIP2->sizePolicy().hasHeightForWidth());
        DestIP2->setSizePolicy(sizePolicy4);
        DestIP2->setMinimumSize(QSize(40, 0));
        DestIP2->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_2->addWidget(DestIP2);

        label_12 = new QLabel(widget_2);
        label_12->setObjectName("label_12");

        horizontalLayout_2->addWidget(label_12);

        DestIP3 = new QLineEdit(widget_2);
        DestIP3->setObjectName("DestIP3");
        sizePolicy4.setHeightForWidth(DestIP3->sizePolicy().hasHeightForWidth());
        DestIP3->setSizePolicy(sizePolicy4);
        DestIP3->setMinimumSize(QSize(40, 0));
        DestIP3->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_2->addWidget(DestIP3);

        label_13 = new QLabel(widget_2);
        label_13->setObjectName("label_13");

        horizontalLayout_2->addWidget(label_13);

        DestIP4 = new QLineEdit(widget_2);
        DestIP4->setObjectName("DestIP4");
        sizePolicy4.setHeightForWidth(DestIP4->sizePolicy().hasHeightForWidth());
        DestIP4->setSizePolicy(sizePolicy4);
        DestIP4->setMinimumSize(QSize(40, 0));
        DestIP4->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_2->addWidget(DestIP4);

        label_14 = new QLabel(widget_2);
        label_14->setObjectName("label_14");

        horizontalLayout_2->addWidget(label_14);

        SrcPort = new QLineEdit(widget_2);
        SrcPort->setObjectName("SrcPort");
        sizePolicy4.setHeightForWidth(SrcPort->sizePolicy().hasHeightForWidth());
        SrcPort->setSizePolicy(sizePolicy4);
        SrcPort->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_2->addWidget(SrcPort);

        label_15 = new QLabel(widget_2);
        label_15->setObjectName("label_15");

        horizontalLayout_2->addWidget(label_15);

        DestPort = new QLineEdit(widget_2);
        DestPort->setObjectName("DestPort");
        sizePolicy4.setHeightForWidth(DestPort->sizePolicy().hasHeightForWidth());
        DestPort->setSizePolicy(sizePolicy4);
        DestPort->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_2->addWidget(DestPort);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout_2->addWidget(widget_2);

        widget_3 = new QWidget(AlertTab);
        widget_3->setObjectName("widget_3");
        sizePolicy1.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy1);
        widget_3->setMinimumSize(QSize(0, 50));
        widget_3->setMaximumSize(QSize(16777215, 50));
        horizontalLayout_4 = new QHBoxLayout(widget_3);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_2 = new QLabel(widget_3);
        label_2->setObjectName("label_2");

        horizontalLayout_4->addWidget(label_2);

        lineEdit = new QLineEdit(widget_3);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout_4->addWidget(lineEdit);

        horizontalSpacer_6 = new QSpacerItem(511, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);


        verticalLayout_2->addWidget(widget_3);

        widget_4 = new QWidget(AlertTab);
        widget_4->setObjectName("widget_4");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Maximum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(widget_4->sizePolicy().hasHeightForWidth());
        widget_4->setSizePolicy(sizePolicy5);
        widget_4->setMinimumSize(QSize(0, 50));
        widget_4->setMaximumSize(QSize(16777215, 50));
        horizontalLayout_5 = new QHBoxLayout(widget_4);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_5 = new QLabel(widget_4);
        label_5->setObjectName("label_5");

        horizontalLayout_5->addWidget(label_5);

        checkBox_3 = new QCheckBox(widget_4);
        checkBox_3->setObjectName("checkBox_3");
        checkBox_3->setChecked(true);

        horizontalLayout_5->addWidget(checkBox_3);

        pushButton = new QPushButton(widget_4);
        pushButton->setObjectName("pushButton");

        horizontalLayout_5->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget_4);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout_5->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(widget_4);
        pushButton_3->setObjectName("pushButton_3");

        horizontalLayout_5->addWidget(pushButton_3);

        horizontalSpacer_8 = new QSpacerItem(781, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_8);


        verticalLayout_2->addWidget(widget_4);

        AlertList = new QListWidget(AlertTab);
        AlertList->setObjectName("AlertList");

        verticalLayout_2->addWidget(AlertList);

        tabWidget->addTab(AlertTab, QString());
        SessionTab = new QWidget();
        SessionTab->setObjectName("SessionTab");
        gridLayout_4 = new QGridLayout(SessionTab);
        gridLayout_4->setObjectName("gridLayout_4");
        widget_5 = new QWidget(SessionTab);
        widget_5->setObjectName("widget_5");

        gridLayout_4->addWidget(widget_5, 0, 0, 1, 1);

        tabWidget->addTab(SessionTab, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        CamPowerLabel->setText(QCoreApplication::translate("MainWindow", "[Camera] : OFF", nullptr));
        CommandStatusIPLabel->setText(QCoreApplication::translate("MainWindow", "[Command Status(IP)] : OFF", nullptr));
        CameraStatusLabel->setText(QCoreApplication::translate("MainWindow", "[Camera Status] : \354\240\225\354\203\201", nullptr));
        ThreatTypePChartLabel->setText(QCoreApplication::translate("MainWindow", "< \354\271\250\354\236\205\355\203\220\354\247\200 \354\234\204\355\230\221 Top 5 >", nullptr));
        HozTopAttackerTop5Label->setText(QCoreApplication::translate("MainWindow", "< \354\271\250\354\236\205\355\203\220\354\247\200 \354\266\234\353\260\234\354\247\200 IP Top 5 >", nullptr));
        ThreatTypePChartLabel_2->setText(QCoreApplication::translate("MainWindow", "< \354\271\250\354\236\205\355\203\220\354\247\200 \354\234\204\355\227\230\353\217\204 \353\263\204 \355\206\265\352\263\204 >", nullptr));
        ActiveSessionCountLabel->setText(QCoreApplication::translate("MainWindow", "\355\231\234\354\204\261 \354\204\270\354\205\230 \354\210\230: ", nullptr));
        BannedIPCountLabel->setText(QCoreApplication::translate("MainWindow", "\354\260\250\353\213\250\353\220\234 IP \354\210\230: ", nullptr));
        ThreatCountLabel->setText(QCoreApplication::translate("MainWindow", "\355\203\220\354\247\200\353\220\234 \354\234\204\355\230\221 \352\261\264\354\210\230: ", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "< \354\213\234\352\260\204\353\214\200\353\263\204 \354\234\204\355\230\221 \353\271\210\353\217\204 \354\260\250\355\212\270 >", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(DashboardTab), QCoreApplication::translate("MainWindow", "Dashboard", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Time - ", nullptr));
        dateTimeFromOnOff->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "~", nullptr));
        dateTimeUntilOnOff->setText(QString());
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Action", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Accept", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Drop", nullptr));

        radioAlert->setText(QCoreApplication::translate("MainWindow", "Alert", nullptr));
        radioDrop->setText(QCoreApplication::translate("MainWindow", "Drop", nullptr));
        radioReject->setText(QCoreApplication::translate("MainWindow", "Reject", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Severity", nullptr));
        SeveritySelect->setItemText(0, QCoreApplication::translate("MainWindow", "All", nullptr));
        SeveritySelect->setItemText(1, QCoreApplication::translate("MainWindow", "Low", nullptr));
        SeveritySelect->setItemText(2, QCoreApplication::translate("MainWindow", "High", nullptr));
        SeveritySelect->setItemText(3, QCoreApplication::translate("MainWindow", "Critical", nullptr));

        SeveritySelect->setCurrentText(QCoreApplication::translate("MainWindow", "All", nullptr));
        protocolName->setText(QCoreApplication::translate("MainWindow", "Protocol", nullptr));
        ProtocolSelect->setItemText(0, QCoreApplication::translate("MainWindow", "All", nullptr));
        ProtocolSelect->setItemText(1, QCoreApplication::translate("MainWindow", "TCP", nullptr));
        ProtocolSelect->setItemText(2, QCoreApplication::translate("MainWindow", "UDP", nullptr));
        ProtocolSelect->setItemText(3, QCoreApplication::translate("MainWindow", "Http", nullptr));

        label_6->setText(QCoreApplication::translate("MainWindow", "Src IP : ", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Dest IP : ", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Src Port :", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Dest Port : ", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Rule/Signature", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Auto-scroll", nullptr));
        checkBox_3->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Export", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(AlertTab), QCoreApplication::translate("MainWindow", "Alert", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(SessionTab), QCoreApplication::translate("MainWindow", "Session", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
