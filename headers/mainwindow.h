#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Alert.h"

#include <QMainWindow>
#include <QChart>
#include <QLineSeries>
#include <QImage>
#include <QThread>

#include "cameraworker.h"
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
    void on_surveillanceButton_clicked();
    void updateCameraView(const QImage &image);
    void addMotionLog(const QString &timestamp);
    void onCameraError(const QString &errorString);
    void onCameraConnected();
    void onCameraDisconnected();
    void checkDateFilterFrom(Qt::CheckState);
    void checkDateFilterUntil(Qt::CheckState);

    void onAlertItemDoubleClicked(QListWidgetItem *item);

    void sort_alerts(alertAttributeType sortAttribute);
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

    void addAlert(const Alert& alert);
    void addAlertWidget(const Alert& alert);

    void parse_alerts();
    void make_alerts_test();

    void set_alertWidgets_withFilter();

private:
    Ui::MainWindow *ui;

    QTcpSocket* socket = nullptr;

    int expectedSize = -1;
    QByteArray buffer;

    QThread cameraThread;
    CameraWorker *cameraWorker;
    bool isSurveillanceMode;
    alertAttributeType sortType;

    QVector<Alert> alerts;

    bool sortAttributeOrder[alertAttributeType::END] = { false, false, false, false, false, false, false };
};
#endif // MAINWINDOW_H
