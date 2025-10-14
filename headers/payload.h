#ifndef PAYLOAD_H
#define PAYLOAD_H

#include <QWidget>
#include "Alert.h"

namespace Ui {
class Payload;
}

class Payload : public QWidget
{
    Q_OBJECT

public:
    explicit Payload(QWidget *parent = nullptr);
    explicit Payload(const Alert* alert, QWidget *parent =nullptr);
    ~Payload();

private:
    Ui::Payload *ui;
};

#endif // PAYLOAD_H
