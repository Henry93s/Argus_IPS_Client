#ifndef SESSIONWIDGET_H
#define SESSIONWIDGET_H

#include <QWidget>

namespace Ui {
class SessionWidget;
}

class SessionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SessionWidget(QWidget *parent = nullptr);
    ~SessionWidget();

private:
    Ui::SessionWidget *ui;
};

#endif // SESSIONWIDGET_H
