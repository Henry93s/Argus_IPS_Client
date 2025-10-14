#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Alert.h"

#include <QMainWindow>
#include <QListWidgetItem>

class QTcpSocket;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum RequestType
{
    ALERT = 1,
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void readFromServer();

    void checkDateFilterFrom(Qt::CheckState);
    void checkDateFilterUntil(Qt::CheckState);

    void onAlertItemDoubleClicked(QListWidgetItem *item);

private:
    void initailize_ui();
    void addAlert_test();
    void addAlert(const Alert& alert);
    void addAlertWidget(const Alert& alert);

    void parse_alerts();
    void make_alerts_test();

    void sort_alerts();

    void set_alertWidgets_withFilter();

private:
    Ui::MainWindow *ui;

    QTcpSocket* socket = nullptr;

    int expectedSize = -1;
    QByteArray buffer;

    alertAttributeType sortType;

    QVector<Alert> alerts;
};
#endif // MAINWINDOW_H
