/********************************************************************************
** Form generated from reading UI file 'sessionwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SESSIONWIDGET_H
#define UI_SESSIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SessionWidget
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_17;
    QSpacerItem *horizontalSpacer_3;
    QToolBox *toolBox;
    QWidget *page_7;
    QTableWidget *tableWidget_4;
    QWidget *page_8;
    QTableWidget *tableWidget_5;
    QWidget *page_9;
    QTableWidget *tableWidget_6;
    QWidget *page_10;

    void setupUi(QWidget *SessionWidget)
    {
        if (SessionWidget->objectName().isEmpty())
            SessionWidget->setObjectName("SessionWidget");
        SessionWidget->resize(1167, 683);
        gridLayout_2 = new QGridLayout(SessionWidget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        horizontalSpacer = new QSpacerItem(538, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        label_17 = new QLabel(SessionWidget);
        label_17->setObjectName("label_17");

        gridLayout->addWidget(label_17, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(548, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        toolBox = new QToolBox(SessionWidget);
        toolBox->setObjectName("toolBox");
        page_7 = new QWidget();
        page_7->setObjectName("page_7");
        page_7->setGeometry(QRect(0, 0, 1141, 491));
        tableWidget_4 = new QTableWidget(page_7);
        tableWidget_4->setObjectName("tableWidget_4");
        tableWidget_4->setGeometry(QRect(10, 0, 1081, 461));
        toolBox->addItem(page_7, QString::fromUtf8("TCP"));
        page_8 = new QWidget();
        page_8->setObjectName("page_8");
        page_8->setGeometry(QRect(0, 0, 1141, 491));
        tableWidget_5 = new QTableWidget(page_8);
        tableWidget_5->setObjectName("tableWidget_5");
        tableWidget_5->setGeometry(QRect(10, 0, 1081, 461));
        toolBox->addItem(page_8, QString::fromUtf8("UDP"));
        page_9 = new QWidget();
        page_9->setObjectName("page_9");
        page_9->setGeometry(QRect(0, 0, 1141, 491));
        tableWidget_6 = new QTableWidget(page_9);
        tableWidget_6->setObjectName("tableWidget_6");
        tableWidget_6->setGeometry(QRect(10, 0, 1081, 461));
        toolBox->addItem(page_9, QString::fromUtf8("ICMP"));
        page_10 = new QWidget();
        page_10->setObjectName("page_10");
        page_10->setGeometry(QRect(0, 0, 1141, 491));
        toolBox->addItem(page_10, QString::fromUtf8("View State"));

        gridLayout->addWidget(toolBox, 1, 0, 1, 3);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(SessionWidget);

        toolBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SessionWidget);
    } // setupUi

    void retranslateUi(QWidget *SessionWidget)
    {
        SessionWidget->setWindowTitle(QCoreApplication::translate("SessionWidget", "Form", nullptr));
        label_17->setText(QCoreApplication::translate("SessionWidget", "IPv4", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_7), QCoreApplication::translate("SessionWidget", "TCP", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_8), QCoreApplication::translate("SessionWidget", "UDP", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_9), QCoreApplication::translate("SessionWidget", "ICMP", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_10), QCoreApplication::translate("SessionWidget", "View State", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SessionWidget: public Ui_SessionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SESSIONWIDGET_H
