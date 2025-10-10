#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChart>
#include <QLineSeries>
#include "Alert.h"

class QTcpSocket;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void readFromServer();

private:
    QChart *threatChart;
    QLineSeries *threatSeries;
    void initailize_ui();
    void addAlert_test();
    void updateThreatChart(int x, int y/*const std::vector<Alert> &alerts*/);
    void initThreatChart();

private:
    Ui::MainWindow *ui;

    QTcpSocket* socket = nullptr;

    int expectedSize = -1;
    QByteArray buffer;
};
#endif // MAINWINDOW_H
