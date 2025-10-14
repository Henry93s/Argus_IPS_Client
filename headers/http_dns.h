#ifndef HTTP_DNS_H
#define HTTP_DNS_H

#include <QWidget>
#include "Alert.h"

namespace Ui {
class HTTP_DNS;
}

class HTTP_DNS : public QWidget
{
    Q_OBJECT

public:
    explicit HTTP_DNS(QWidget *parent = nullptr);
    explicit HTTP_DNS(const Alert* alert, QWidget *parent = nullptr);
    ~HTTP_DNS();

private:
    Ui::HTTP_DNS *ui;
};

#endif // HTTP_DNS_H
