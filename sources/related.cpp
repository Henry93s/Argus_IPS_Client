#include "../headers/related.h"
#include "ui_related.h"

Related::Related(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Related)
{
    ui->setupUi(this);
}

Related::Related(const Alert *alert, QWidget *parent) : QWidget(parent), ui(new Ui::Related)
{
    ui->setupUi(this);
}

Related::~Related()
{
    delete ui;
}
