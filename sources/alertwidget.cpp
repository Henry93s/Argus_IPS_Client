#include "../headers/alertwidget.h"
#include <QVBoxLayout>
#include <QListWidget>

AlertWidget::AlertWidget(QWidget *parent)
    : QWidget{parent}
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    labels[0] = new QLabel("Time", this);
    labels[1] = new QLabel("Src IP", this);
    labels[2] = new QLabel("Dest IP", this);
    labels[3] = new QLabel("Protocol", this);
    labels[4] = new QLabel("Src Port", this);
    labels[5] = new QLabel("Dest Port", this);
    labels[6] = new QLabel("Severity", this);

    for(int i = 0; i <= alertAttributeType::Severity; i++){
        layout->addWidget(labels[i]);
    }

    layout->setStretch(0, 3);
    layout->setStretch(1, 2);
    layout->setStretch(2, 2);
    layout->setStretch(3, 1);
    layout->setStretch(4, 1);
    layout->setStretch(5, 1);
    layout->setStretch(6, 1);

    setLayout(layout);
}

AlertWidget::AlertWidget(const QString (&labelNames)[Severity + 1], QWidget *parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    for(int i = 0; i <= Severity; i++){
        labels[i] = new QLabel(labelNames[i]);
        layout->addWidget(labels[i]);
    }
    layout->setStretch(0, 3);
    layout->setStretch(1, 2);
    layout->setStretch(2, 2);
    layout->setStretch(3, 1);
    layout->setStretch(4, 1);
    layout->setStretch(5, 1);
    layout->setStretch(6, 1);

    setLayout(layout);
}

AlertWidget::AlertWidget(const Alert &alert, int alertIndex, QWidget *parent) : alertIndex(alertIndex)
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    labels[alertAttributeType::Time] = new QLabel(alert.time.toString());
    QString srcIP = QString("%1.%2.%3.%4").arg(alert.srcIp[0]).arg(alert.srcIp[1]).arg(alert.srcIp[2]).arg(alert.srcIp[3]);
    labels[alertAttributeType::SrcIP] = new QLabel(srcIP);

    QString destIP = QString("%1.%2.%3.%4").arg(alert.dstIp[0]).arg(alert.dstIp[1]).arg(alert.dstIp[2]).arg(alert.dstIp[3]);
    labels[alertAttributeType::DestIP] = new QLabel(destIP);

    switch(alert.pType){
    case protocolType::TCP:
        labels[alertAttributeType::Protocol] = new QLabel("TCP");
        break;
    case protocolType::UDP:
        labels[alertAttributeType::Protocol] = new QLabel("UDP");
        break;
    case protocolType::HTTP:
        labels[alertAttributeType::Protocol] = new QLabel("Http");
        break;
    }

    labels[alertAttributeType::SrcPort] = new QLabel(QString::number(alert.srcPort));
    labels[alertAttributeType::DestPort] = new QLabel(QString::number(alert.dstPort));

    switch(alert.sType) {
    case severityType::Low:
        labels[alertAttributeType::Severity] = new QLabel("Low");
        break;
    case severityType::High:
        labels[alertAttributeType::Severity] = new QLabel("High");
        break;
    case severityType::Critical:
        labels[alertAttributeType::Severity] = new QLabel("Critical");
        break;
    }

    for(int i = 0; i <= alertAttributeType::Severity; i++){
        layout->addWidget(labels[i]);
    }

    layout->setStretch(0, 3);
    layout->setStretch(1, 2);
    layout->setStretch(2, 2);
    layout->setStretch(3, 1);
    layout->setStretch(4, 1);
    layout->setStretch(5, 1);
    layout->setStretch(6, 1);



    setLayout(layout);
}

AlertWidget::AlertWidget(Alert &&alert, int alertIndex, QWidget *parent) : alertIndex(alertIndex)
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    labels[alertAttributeType::Time] = new QLabel(alert.time.toString());
    QString srcIP = QString("%1.%2.%3.%4").arg(alert.srcIp[0]).arg(alert.srcIp[1]).arg(alert.srcIp[2]).arg(alert.srcIp[3]);
    labels[alertAttributeType::SrcIP] = new QLabel(srcIP);

    QString destIP = QString("%1.%2.%3.%4").arg(alert.dstIp[0]).arg(alert.dstIp[1]).arg(alert.dstIp[2]).arg(alert.dstIp[3]);
    labels[alertAttributeType::DestIP] = new QLabel(destIP);

    switch(alert.pType){
    case protocolType::TCP:
        labels[alertAttributeType::Protocol] = new QLabel("TCP");
        break;
    case protocolType::UDP:
        labels[alertAttributeType::Protocol] = new QLabel("UDP");
        break;
    case protocolType::HTTP:
        labels[alertAttributeType::Protocol] = new QLabel("Http");
        break;
    }

    labels[alertAttributeType::SrcPort] = new QLabel(QString::number(alert.srcPort));
    labels[alertAttributeType::DestPort] = new QLabel(QString::number(alert.dstPort));

    switch(alert.sType) {
    case severityType::Low:
        labels[alertAttributeType::Severity] = new QLabel("Low");
        break;
    case severityType::High:
        labels[alertAttributeType::Severity] = new QLabel("High");
        break;
    case severityType::Critical:
        labels[alertAttributeType::Severity] = new QLabel("Critical");
        break;
    }

    for(int i = 0; i <= alertAttributeType::Severity; i++){
        layout->addWidget(labels[i]);
    }

    layout->setStretch(0, 3);
    layout->setStretch(1, 2);
    layout->setStretch(2, 2);
    layout->setStretch(3, 1);
    layout->setStretch(4, 1);
    layout->setStretch(5, 1);
    layout->setStretch(6, 1);

    setLayout(layout);
}
