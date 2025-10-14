#include "../headers/rawpacket.h"
#include "ui_rawpacket.h"

RawPacket::RawPacket(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RawPacket)
{
    ui->setupUi(this);
}

RawPacket::RawPacket(const Alert *alert, QWidget *parent) : QWidget(parent), ui(new Ui::RawPacket)
{
    ui->setupUi(this);
}

RawPacket::~RawPacket()
{
    delete ui;
}
