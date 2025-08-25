#include "../headers/alertwidget.h"
#include <QVBoxLayout>
#include <QListWidget>

AlertWidget::AlertWidget(QWidget *parent)
    : QWidget{parent}
{
    label = new QLabel(this);
    label->setWordWrap(true); // 줄바꿈 허용

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->setContentsMargins(10, 5, 10, 5); // 내부 여백
    setLayout(layout);

    setStyleSheet("background-color: lightblue; border-radius: 8px;");

    adjustSizeToText();
}
