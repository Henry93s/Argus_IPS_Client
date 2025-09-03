#ifndef ALERTWIDGET_H
#define ALERTWIDGET_H

#include <QWidget>
#include <QLabel>

#include "Alert.h"

enum labelType {
    Time,
    SrcIP,
    DestIP,
    Protocol,
    SrcPort,
    DestPort,
    Severity
};

class AlertWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AlertWidget(QWidget *parent = nullptr);
    explicit AlertWidget(const QString (&labels)[Severity + 1], QWidget *parent = nullptr);
    explicit AlertWidget(const Alert& alert, QWidget *parent = nullptr);
    explicit AlertWidget(Alert&& alert, QWidget *parent = nullptr);

private:
    void adjustSizeToText() {
        // // 메시지 길이에 따라 라벨 크기 계산
        // int maxWidth = 250; // 최대 너비
        // label->setMaximumWidth(maxWidth);

        // // 라벨 크기에 맞춰 위젯 크기 조정
        // label->adjustSize();
        // setFixedSize(label->sizeHint().width() + 20, label->sizeHint().height() + 10);
    }

private:
    QLabel* labels[Severity + 1];
signals:
};

#endif // ALERTWIDGET_H
