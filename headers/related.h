#ifndef RELATED_H
#define RELATED_H

#include <QWidget>
#include "Alert.h"

namespace Ui {
class Related;
}

class Related : public QWidget
{
    Q_OBJECT

public:
    explicit Related(QWidget *parent = nullptr);
    explicit Related(const Alert* alert, QWidget *parent = nullptr);
    ~Related();

private:
    Ui::Related *ui;
};

#endif // RELATED_H
