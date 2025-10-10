#include "../headers/payload.h"
#include "ui_payload.h"

Payload::Payload(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Payload)
{
    ui->setupUi(this);
}

Payload::Payload(const Alert *alert, QWidget *parent) : QWidget(parent), ui(new Ui::Payload)
{
    ui->setupUi(this);
}

Payload::~Payload()
{
    delete ui;
}
