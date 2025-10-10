#include "../headers/http_dns.h"
#include "ui_http_dns.h"

HTTP_DNS::HTTP_DNS(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HTTP_DNS)
{
    ui->setupUi(this);
}

HTTP_DNS::HTTP_DNS(const Alert *alert, QWidget *parent) :QWidget(parent), ui(new Ui::HTTP_DNS)
{
    ui->setupUi(this);
}

HTTP_DNS::~HTTP_DNS()
{
    delete ui;
}
