#include "../headers/notes.h"
#include "ui_notes.h"

Notes::Notes(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Notes)
{
    ui->setupUi(this);
}

Notes::Notes(const Alert *alert, QWidget *parent) : QWidget(parent), ui(new Ui::Notes)
{
    ui->setupUi(this);
}

Notes::~Notes()
{
    delete ui;
}
