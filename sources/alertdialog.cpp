#include "../headers/alertdialog.h"
#include "ui_alertdialog.h"
#include "../headers/overview.h"
#include "../headers/http_dns.h"
#include "../headers/notes.h"
#include "../headers/payload.h"
#include "../headers/rawpacket.h"
#include "../headers/related.h"

alertDialog::alertDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::alertDialog)
{
    ui->setupUi(this);
}

alertDialog::alertDialog(const Alert *alert, QWidget *parent) : QDialog(parent), ui(new Ui::alertDialog), pointingAlert(alert)
{
    ui->setupUi(this);
    initialize();
}

alertDialog::~alertDialog()
{
    delete ui;
}

void alertDialog::initialize()
{
    // Set Severity
    switch(pointingAlert->sType)
    {
    case severityType::Low:
        ui->Severity->setText("Low");
        break;
    case severityType::High:
        ui->Severity->setText("High");
        break;
    case severityType::Critical:
        ui->Severity->setText("Critical");
        break;
    }

    // Set Action
    switch(pointingAlert->aType)
    {
    case actionType::Accept:
        ui->Action->setText("Accept");
        break;
    case actionType::Drop:
        ui->Action->setText("Drop");
        break;
    }

    // Set Time
    ui->Time->setText(pointingAlert->time.toString(Qt::ISODate));

    ui->SrcIPPort->setText(Alert::GetIpStr(pointingAlert->srcIp) + QString(":") + QString::number(pointingAlert->srcPort));
    ui->DstIPPort->setText(Alert::GetIpStr(pointingAlert->dstIp) + QString(":") + QString::number(pointingAlert->dstPort));

    // switch(pointingAlert->pType)
    // {
    // case protocolType::TCP:
    //     ui->Protocol->setText("TCP");
    //     break;
    // case protocolType::UDP:
    //     ui->Protocol->setText("UDP");
    //     break;
    // case protocolType::HTTP:
    //     ui->Protocol->setText("Http");
    //     break;
    // }
    ui->Protocol->setText(protocolNames[pointingAlert->pType]);

    connect(ui->tabBox, &QComboBox::currentTextChanged, this, &alertDialog::tabChanged);

}

void alertDialog::tabChanged(const QString &text)
{
    if(currentTab && layout()){
        layout()->removeWidget(currentTab);
        currentTab->setParent(nullptr);
        delete currentTab;
    }

    QString tabText = ui->tabBox->currentText();
    if(tabText == "Overview"){
        if(layout()){
            currentTab = new Overview(this);

            layout()->addWidget(currentTab);
        }
    }
    else if(tabText == "Payload"){
        if(layout()){
            currentTab = new Payload(this);

            layout()->addWidget(currentTab);
        }
    }
    else if(tabText == "HTTP/DNS"){
        if(layout()){
            currentTab = new HTTP_DNS(this);

            layout()->addWidget(currentTab);
        }
    }
    else if(tabText == "Raw Packet"){
        if(layout()){
            currentTab = new RawPacket(this);

            layout()->addWidget(currentTab);
        }
    }
    else if(tabText == "Related"){
        if(layout()){
            currentTab = new Related(this);

            layout()->addWidget(currentTab);
        }
    }
    else if(tabText == "Notes"){
        if(layout()){
            currentTab = new Notes(this);

            layout()->addWidget(currentTab);
        }
    }
}
