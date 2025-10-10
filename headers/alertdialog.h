#ifndef ALERTDIALOG_H
#define ALERTDIALOG_H

#include <QDialog>

#include "Alert.h"

namespace Ui {
class alertDialog;
}

class alertDialog : public QDialog
{
    Q_OBJECT

public:
    explicit alertDialog(QWidget *parent = nullptr);
    explicit alertDialog(const Alert* alert, QWidget *parent = nullptr);
    ~alertDialog();

private:
    void initialize();

private slots:
    void tabChanged(const QString &text);

private:
    Ui::alertDialog *ui;

    const Alert* pointingAlert = nullptr;
    QWidget* currentTab = nullptr;
};

#endif // ALERTDIALOG_H
