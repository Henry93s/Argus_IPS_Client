#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChart>
#include <QLineSeries>
#include <QImage>
#include <QThread>
#include "Alert.h"
#include "cameraworker.h"

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
    void on_surveillanceButton_clicked();
    void updateCameraView(const QImage &image);
    void addMotionLog(const QString &timestamp);
    void onCameraError(const QString &errorString);
    void onCameraConnected();
    void onCameraDisconnected();

signals:
    // Worker에게 작업을 시작하라고 보낼 시그널
    void startCameraProcessing(const QString &host, quint16 port);

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

    QThread cameraThread;
    CameraWorker *cameraWorker;
    bool isSurveillanceMode;
};
#endif // MAINWINDOW_H
