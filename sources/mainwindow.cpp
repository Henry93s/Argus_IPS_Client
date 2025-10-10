#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"

#include "../headers/alertwidget.h"

#include <QTcpSocket>
#include <QMenuBar>
// QtCharts
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QVBoxLayout>
#include <QRandomGenerator>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QTimer>
#include <QDateTime>

// 시간대별 위협 차트 초기화
void MainWindow::initThreatChart() {
    threatSeries = new QLineSeries();
    threatSeries->setPointsVisible(true);

    threatChart = new QChart();
    threatChart->addSeries(threatSeries);
    threatChart->legend()->hide();
    threatChart->setTitle(QString("실시간 위협 누적 모니터링 - %1")
                              .arg(QDate::currentDate().toString("yyyy년 MM월 dd일")));
    threatChart->setTitleBrush(QBrush(Qt::white));

    // ---- X축: 하루 동안 1초 주기로 위협 Alert 실시간 카운트 ----
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setFormat("hh:mm:ss");
    axisX->setTitleText("탐지 시각");
    axisX->setLabelsBrush(QBrush(Qt::white));   // 라벨 흰색
    axisX->setTitleBrush(QBrush(Qt::white));    // 제목 흰색
    axisX->setTickCount(6); // 표시 간격 (6개 눈금)

    // ---- Y축: 하루 동안 위협 누적 수치 ----
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 20); // 처음엔 0~20
    axisY->applyNiceNumbers();
    axisY->setLabelsBrush(QBrush(Qt::white));
    axisY->setTitleText("누적 위협 건수");
    axisY->setTitleBrush(QBrush(Qt::white));

    threatChart->addAxis(axisX, Qt::AlignBottom);
    threatChart->addAxis(axisY, Qt::AlignLeft);
    threatSeries->attachAxis(axisX);
    threatSeries->attachAxis(axisY);

    // 차트 배경색
    threatChart->setBackgroundBrush(QBrush(Qt::black));
    threatChart->setPlotAreaBackgroundVisible(true);
    threatChart->setPlotAreaBackgroundBrush(QBrush(Qt::darkGray));

    ui->ThreatBarChartGraphicsView->setChart(threatChart);
    ui->ThreatBarChartGraphicsView->setRenderHint(QPainter::Antialiasing);

    // ---- 상태 관리용 변수 ----
    int *cumulativeThreatCount = new int(0);  // 누적 위협 카운트 저장

    // ---- 타이머로 1초마다 값 추가 ----
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() mutable {
        QDateTime now = QDateTime::currentDateTime();

        // 00:00:00 시점이면 누적값 리셋
        if (now.time().hour() == 0 && now.time().minute() == 0 && now.time().second() == 0) {
            *cumulativeThreatCount = 0;
            threatSeries->clear();
            axisY->setRange(0, 20); // 다시 초기화
        }

        // 랜덤 위협 발생 수 (누적에 더하기)
        int newThreats = QRandomGenerator::global()->bounded(5, 15);
        *cumulativeThreatCount += newThreats;

        // Y축 동적 조정 (20 넘으면 자동 확장)
        if (*cumulativeThreatCount > axisY->max()) {
            axisY->setRange(0, *cumulativeThreatCount + 10); // 여유 있게 늘림
        }

        // 데이터 추가
        qint64 x = now.toMSecsSinceEpoch();  // X값 (시간)
        threatSeries->append(x, *cumulativeThreatCount);

        // X축 범위 현재 시간 기준 30초만 보이도록
        axisX->setRange(now.addSecs(-30), now);
    });
    timer->start(1000); // 1초마다 실행
}

// 시간대별 위협 차트 업데이트
void MainWindow::updateThreatChart(int x, int y) {
    if (!threatSeries) return;

    threatSeries->append(x, y);
    threatChart->update();  // 화면 갱신
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    socket->connectToHost("192.168.2.98", 8085);

    // test
    addAlert_test();


    // threat chart 초기화
    initThreatChart();

    if (!socket->waitForConnected(3000)) {  // 최대 3초 대기
        qDebug() << "서버 접속 실패:" << socket->errorString();
        // return;
    }
    qDebug() << "서버 접속 성공";

    QObject::connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readFromServer);

    QObject::connect(socket, &QTcpSocket::disconnected, [&]() {
        qDebug() << "서버 연결 끊김";
        // this->deleteLater();
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readFromServer()
{
    buffer.append(socket->readAll());

    while (true) {
        if (expectedSize == -1) {
            if (buffer.size() < 4) break; // 길이 정보 아직 도착 안 함
            QDataStream stream(buffer);
            stream.setByteOrder(QDataStream::BigEndian);
            stream >> expectedSize;
            buffer.remove(0, 4);
        }

        if (buffer.size() < expectedSize) break; // 데이터 다 안 옴

        QByteArray msg = buffer.left(expectedSize);
        buffer.remove(0, expectedSize);

        qDebug() << "가변 메시지 수신:" << msg;
        expectedSize = -1;
    }
}

void MainWindow::initailize_ui()
{

}

void MainWindow::addAlert_test()
{
    QListWidgetItem *item = new QListWidgetItem(ui->AlertList);

    // int maxWidth = ui->alertList->viewport()->width() - 20;

    AlertWidget* newAlert = new AlertWidget(this);
    // newAlert->setMaximumWidth(maxWidth);

    // 아이템 크기 위젯 크기에 맞춤
    item->setSizeHint(newAlert->sizeHint());


    ui->AlertList->addItem(item);
    ui->AlertList->setItemWidget(item, newAlert);

    ui->AlertList->setMinimumHeight(40);
    // 스크롤 맨 아래로
    // ui->alertList->scrollToBottom();
}
