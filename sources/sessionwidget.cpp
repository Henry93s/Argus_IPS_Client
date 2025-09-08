#include "../headers/sessionwidget.h"
#include "ui_sessionwidget.h"

SessionWidget::SessionWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SessionWidget)
{
    ui->setupUi(this);
}

SessionWidget::~SessionWidget()
{
    delete ui;
}
