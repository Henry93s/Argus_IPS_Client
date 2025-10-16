#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Alert.h"
#include <QMainWindow>
#include <QImage>
#include <QThread>
#include "cameraworker.h"
#include <QListWidgetItem>
#include <QVector> // QVector 추가
#include <QMap>   // QMap 추가

#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QHorizontalBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

class QTcpSocket;
class QTimer; // QTimer 전방 선언

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
    void updateDashboardCharts(); // 대시보드 차트를 주기적으로 업데이트할 슬롯
    void sort_alerts(alertAttributeType sortAttribute);
signals:
    // Worker에게 작업을 시작하라고 보낼 시그널
    void startCameraProcessing(const QString &host, quint16 port);

private:
    void initailize_ui();
    void addAlert_test();

    void updateThreatChart(int x, int y/*const std::vector<Alert> &alerts*/);
    void initThreatChart();
    void initThreatTop5Chart();   // 위협 Top 5 차트 초기화 함수 선언
    void initSrcIpTop5Chart();    // 출발지 IP Top 5 차트 초기화 함수 선언

    void addAlert(const Alert& alert);
    void addAlertWidget(const Alert& alert);

    void parse_alerts();
    void make_alerts_test();

    void set_alertWidgets_withFilter();

    // 1. 실시간 위협 누적 차트
    QChart *threatChart;
    QLineSeries *threatSeries;

    // 2. 위협 Top 5 차트 (프로토콜 기반)
    QChart *threatTop5Chart;
    QHorizontalBarSeries *threatTop5Series;
    QBarCategoryAxis *threatAxisY;
    QValueAxis *threatAxisX;
    QMap<protocolType, int> threatData; // 프로토콜별 카운트

    // 3. 출발지 IP Top 5 차트
    QChart *srcIpTop5Chart;
    QHorizontalBarSeries *srcIpTop5Series;
    QBarCategoryAxis *srcIpAxisY;
    QValueAxis *srcIpAxisX;
    QMap<QString, int> srcIpData; // IP 주소별 카운트

    // 대시보드 업데이트 타이머
    QTimer *dashboardTimer;

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
