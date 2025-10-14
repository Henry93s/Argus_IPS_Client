#include "../headers/overview.h"
#include "ui_overview.h"

Overview::Overview(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Overview)
{
    ui->setupUi(this);
}

Overview::Overview(const Alert *alert, QWidget *parent) : QWidget(parent), ui(new Ui::Overview)
{
    ui->setupUi(this);
}

Overview::~Overview()
{
    delete ui;
}
