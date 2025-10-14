#ifndef OVERVIEW_H
#define OVERVIEW_H

#include <QWidget>
#include "Alert.h"

namespace Ui {
class Overview;
}

class Overview : public QWidget
{
    Q_OBJECT

public:
    explicit Overview(QWidget *parent = nullptr);
    explicit Overview(const Alert* alert, QWidget *parent = nullptr);
    ~Overview();

private:
    Ui::Overview *ui;
};

#endif // OVERVIEW_H
