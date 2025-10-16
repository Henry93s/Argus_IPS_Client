#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"

#include "../headers/alertwidget.h"
#include "../headers/alertdialog.h"

#include <QtCharts/QBarSet>
#include <QJsonDocument>
#include <algorithm>
#include <array>
#include <QTcpSocket>
#include <QMenuBar>
// QtCharts
#include <QtCharts/QChartView>
#include <QVBoxLayout>
#include <QRandomGenerator>
#include <QtCharts/QDateTimeAxis>
#include <QTimer>
#include <QDateTime>
#include <QPixmap>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QJsonObject>
#include <QFlags>
#include <algorithm>
#include <functional>

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
    , isSurveillanceMode(false)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    // socket->connectToHost("192.168.2.98", 8085);
    // socket->connectToHost("192.168.2.29", 8085);
    socket->connectToHost("192.168.32.130", 8085);

    // // test
    // addAlert_test();
    // make_alerts_test();

    initailize_ui();

    connect(ui->AlertList, &QListWidget::itemDoubleClicked, this, &MainWindow::onAlertItemDoubleClicked);

    if (!socket->waitForConnected(3000)) {  // 최대 3초 대기
        qDebug() << "서버 접속 실패:" << socket->errorString();
        // return;
    }
    qDebug() << "서버 접속 성공";

    // threat chart 초기화
    initThreatChart();
    initThreatTop5Chart();
    initSrcIpTop5Chart();

    // 5초마 대시보드 차트를 업데이트하는 타이머 설정
    dashboardTimer = new QTimer(this);
    connect(dashboardTimer, &QTimer::timeout, this, &MainWindow::updateDashboardCharts);
    dashboardTimer->start(5000); // 1초 간격

    QObject::connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readFromServer);

    QObject::connect(socket, &QTcpSocket::disconnected, [&]() {
        qDebug() << "서버 연결 끊김";
        // this->deleteLater();
    });

    // 스레드-워커 설정
    cameraWorker = new CameraWorker();
    cameraWorker->moveToThread(&cameraThread);
    // 카메라 워커 스레드 토글 동작을 위해 주석 처리 1 - 스레드 종료는 메인윈도우가 닫힐 때 처리해야함
    // connect(&cameraThread, &QThread::finished, cameraWorker, &QObject::deleteLater);
    // startCameraProcessing 시그널의 인자가 변경되었으므로, connect도 맞춰서 수정
    connect(this, &MainWindow::startCameraProcessing, cameraWorker, &CameraWorker::process);
    // 카메라 워커 스레드 토글 동작을 위해 주석 처리 2 - 스레드 종료는 메인윈도우가 닫힐 때 처리해야함
    // connect(cameraWorker, &CameraWorker::finished, &cameraThread, &QThread::quit, Qt::DirectConnection);
    connect(cameraWorker, &CameraWorker::frameReady, this, &MainWindow::updateCameraView);
    connect(cameraWorker, &CameraWorker::motionDetected, this, &MainWindow::addMotionLog);
    connect(cameraWorker, &CameraWorker::cameraError, this, &MainWindow::onCameraError);
    connect(cameraWorker, &CameraWorker::cameraConnected, this, &MainWindow::onCameraConnected);
    connect(cameraWorker, &CameraWorker::cameraDisconnected, this, &MainWindow::onCameraDisconnected);
    // 프로그램 종료 전까지 계속 실행
    cameraThread.start();
    // QTimer* timer = new QTimer(this);
    // connect(timer, &QTimer::timeout, this, &MainWindow::updateTick);
    // timer->start(16); // 16ms마다 실행 (약 60fps)
}

MainWindow::~MainWindow()
{
    // 워커에게 먼저 중지 신호를 보냄
    cameraWorker->stop();
    // 스레드를 안전하게 종료
    cameraThread.quit();
    cameraThread.wait(); // 스레드가 완전히 끝날 때까지 대기

    delete ui;
}

void MainWindow::readFromServer()
{
    buffer.append(socket->readAll());

    // 2️⃣ JSON 파싱
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(buffer, &parseError);

    if (parseError.error == QJsonParseError::NoError && jsonDoc.isObject())
    {
        // 3️⃣ QJsonObject 추출
        QJsonObject jsonObj = jsonDoc.object();

        Alert alert;
        alert.dstIp[0] = jsonObj["dstIp0"].toInt();
        alert.dstIp[1] = jsonObj["dstIp1"].toInt();
        alert.dstIp[2] = jsonObj["dstIp2"].toInt();
        alert.dstIp[3] = jsonObj["dstIp3"].toInt();
        alert.dstPort = jsonObj["dstPort"].toInt();
        alert.srcIp[0] = jsonObj["srcIp0"].toInt();
        alert.srcIp[1] = jsonObj["srcIp1"].toInt();
        alert.srcIp[2] = jsonObj["srcIp2"].toInt();
        alert.srcIp[3] = jsonObj["srcIp3"].toInt();
        alert.srcPort = jsonObj["srcPort"].toInt();
        alert.pType = (protocolType)jsonObj["proto"].toInt();
        alert.sType = (severityType)jsonObj["severity"].toInt();
        alert.aType = actionType::Accept;

        QString timeStr = jsonObj["time"].toString();

        alert.time = QDateTime::fromString(timeStr, "yyyy-MM-dd HH:mm:ss");

        addAlert(alert);
        addAlertWidget(alert);

        threatData[alert.pType]++; // 프로토콜 타입별 카운트 증가
        QString srcIP = Alert::GetIpStr2(alert.srcIp);
        if(srcIP != "0.0.0.0") srcIpData[srcIP]++;
    }
    else
    {
        qWarning() << "JSON parse error:" << parseError.errorString();
    }

    buffer.clear();

    socket->write("Success");

    // while (true) {
    //     if (expectedSize == -1) {
    //         if (buffer.size() < 4) break; // 길이 정보 아직 도착 안 함
    //         QDataStream stream(buffer);
    //         stream.setByteOrder(QDataStream::BigEndian);
    //         stream >> expectedSize;
    //         buffer.remove(0, 4);
    //     }

    //     if (buffer.size() < expectedSize) break; // 데이터 다 안 옴

    //     QByteArray msg = buffer.left(expectedSize);
    //     buffer.remove(0, expectedSize);

    //     qDebug() << "가변 메시지 수신:" << msg;
    //     expectedSize = -1;
    // }
}

void MainWindow::checkDateFilterFrom(Qt::CheckState state)
{

}

void MainWindow::checkDateFilterUntil(Qt::CheckState state)
{

}

void MainWindow::onAlertItemDoubleClicked(QListWidgetItem *item)
{
    // 해당 item에 연결된 AlertWidget 가져오기
    QWidget *w = ui->AlertList->itemWidget(item);
    auto *alertWidget = qobject_cast<AlertWidget*>(w);

    if (alertWidget) {
        // Alert 데이터를 다이얼로그에 전달하고 실행
        alertDialog dlg(&alerts[alertWidget->GetAlertIndex()], this);
        dlg.exec(); // 모달 다이얼로그
    }
}

void MainWindow::initailize_ui()
{
    connect(ui->dateTimeFromOnOff, &QCheckBox::checkStateChanged, this, &MainWindow::checkDateFilterFrom);
    connect(ui->dateTimeUntilOnOff, &QCheckBox::checkStateChanged, this, &MainWindow::checkDateFilterUntil);

    connect(ui->SrcIP1, &QLineEdit::textChanged, this, &MainWindow::set_alertWidgets_withFilter);
    connect(ui->SrcIP2, &QLineEdit::textChanged, this, &MainWindow::set_alertWidgets_withFilter);
    connect(ui->SrcIP3, &QLineEdit::textChanged, this, &MainWindow::set_alertWidgets_withFilter);
    connect(ui->SrcIP4, &QLineEdit::textChanged, this, &MainWindow::set_alertWidgets_withFilter);

    connect(ui->DestIP1, &QLineEdit::textChanged, this, &MainWindow::set_alertWidgets_withFilter);
    connect(ui->DestIP2, &QLineEdit::textChanged, this, &MainWindow::set_alertWidgets_withFilter);
    connect(ui->DestIP3, &QLineEdit::textChanged, this, &MainWindow::set_alertWidgets_withFilter);
    connect(ui->DestIP4, &QLineEdit::textChanged, this, &MainWindow::set_alertWidgets_withFilter);

    connect(ui->SrcPort, &QLineEdit::textChanged, this, &MainWindow::set_alertWidgets_withFilter);
    connect(ui->DestPort, &QLineEdit::textChanged, this, &MainWindow::set_alertWidgets_withFilter);

    connect(ui->dateTimeFromOnOff, &QCheckBox::stateChanged, this, &MainWindow::set_alertWidgets_withFilter);
    connect(ui->dateTimeUntilOnOff, &QCheckBox::stateChanged, this, &MainWindow::set_alertWidgets_withFilter);

    connect(ui->dateTimeFrom, &QDateTimeEdit::dateTimeChanged, this, &MainWindow::set_alertWidgets_withFilter);
    connect(ui->dateTimeUntil, &QDateTimeEdit::dateTimeChanged, this, &MainWindow::set_alertWidgets_withFilter);

    connect(ui->radioAlert, &QRadioButton::clicked, this, &MainWindow::set_alertWidgets_withFilter);
    connect(ui->radioDrop, &QRadioButton::clicked, this, &MainWindow::set_alertWidgets_withFilter);

    connect(ui->ProtocolSelect, &QComboBox::currentIndexChanged, this, &MainWindow::set_alertWidgets_withFilter);

    connect(ui->SeveritySelect, &QComboBox::currentIndexChanged, this, &MainWindow::set_alertWidgets_withFilter);

    // sort
    connect(ui->TimeSort, &QPushButton::clicked, this, [this](){sort_alerts(alertAttributeType::Time);});
    connect(ui->SourceIPSort, &QPushButton::clicked, this, [this](){sort_alerts(alertAttributeType::SrcIP);});
    connect(ui->DestinationIPSort, &QPushButton::clicked, this, [this](){sort_alerts(alertAttributeType::DestIP);});
    connect(ui->ProtocolSort, &QPushButton::clicked, this, [this](){sort_alerts(alertAttributeType::Protocol);});
    connect(ui->SourcePortSort, &QPushButton::clicked, this, [this](){sort_alerts(alertAttributeType::SrcPort);});
    connect(ui->DestinationPortSort, &QPushButton::clicked, this, [this](){sort_alerts(alertAttributeType::DestPort);});
    connect(ui->SeveritySort, &QPushButton::clicked, this, [this](){sort_alerts(alertAttributeType::Severity);});
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

// "감시 모드" 버튼 클릭 시 호출되는 슬롯
void MainWindow::on_surveillanceButton_clicked()
{
    isSurveillanceMode = !isSurveillanceMode; // toggle

    if (isSurveillanceMode) {
        ui->surveillanceButton->setText("연결 중...");
        ui->surveillanceButton->setEnabled(false);
        // IP와 포트만 시그널로 전달
        emit startCameraProcessing("192.168.2.98", 5088);
    } else {
        // 워커에게 중지 신호를 보냄
        cameraWorker->stop();
    }
}

void MainWindow::updateCameraView(const QImage &image)
{
    if (!ui->cameraViewLabel->isVisible()) return;
    ui->cameraViewLabel->setPixmap(QPixmap::fromImage(image).scaled(
        ui->cameraViewLabel->size(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation));
}

void MainWindow::addMotionLog(const QString &timestamp)
{
    QString logMessage = QString("[%1] 움직임이 감지되었습니다.").arg(timestamp);
    QListWidgetItem *item = new QListWidgetItem(logMessage);
    item->setForeground(Qt::red);
    ui->motionLogList->addItem(item);
    ui->motionLogList->scrollToBottom();
}

// 카메라 관련 에러가 발생했을 때 호출되는 슬롯
void MainWindow::onCameraError(const QString &errorString)
{
    QMessageBox::critical(this, "카메라 오류", errorString);
    // 에러 발생 시 감시 모드 강제 해제
    if (isSurveillanceMode) {
        isSurveillanceMode = false;
        ui->surveillanceButton->setText("감시 모드 시작");
        ui->cameraViewLabel->clear();
        ui->cameraViewLabel->setStyleSheet("background-color: black;");
        ui->cameraViewLabel->setText("카메라 오류 발생");
        ui->CamPowerLabel->setText("[Camera] : OFF");
        ui->CameraStatusLabel->setText("[Camera Status] : 비정상 동작");
    }
    ui->CamPowerLabel->setText("[Camera] : OFF");
    ui->CameraStatusLabel->setText("[Camera Status] : 비정상 동작");
}

void MainWindow::onCameraConnected()
{
    qDebug() << "카메라 서버 연결 성공";
    ui->surveillanceButton->setText("감시 모드 해제");
    ui->surveillanceButton->setEnabled(true);
    ui->CamPowerLabel->setText("[Camera] : ON");
    ui->CameraStatusLabel->setText("[Camera Status] : 정상 동작 중");
    ui->CommandStatusIPLabel->setText("[Command Status(IP)] : 192.168.2.98");
}

void MainWindow::onCameraDisconnected()
{
    qDebug() << "카메라 서버 연결 종료";
    isSurveillanceMode = false;
    ui->surveillanceButton->setText("감시 모드 시작");
    ui->cameraViewLabel->clear();
    ui->surveillanceButton->setEnabled(true);
    ui->cameraViewLabel->setStyleSheet("background-color: black;");
    ui->cameraViewLabel->setText("카메라 연결 끊김");
    ui->CamPowerLabel->setText("[Camera] : OFF");
    ui->CameraStatusLabel->setText("[Camera Status] : 정상 동작 중");
    ui->CommandStatusIPLabel->setText("[Command Status(IP)] : 192.168.2.98");
}
void MainWindow::addAlert(const Alert &alert)
{
    alerts.push_back(alert);
}

void MainWindow::addAlertWidget(const Alert &alert)
{
    QListWidgetItem * item = new QListWidgetItem(ui->AlertList);

    AlertWidget* newAlert = new AlertWidget(alert, (int)alerts.size(), this);

    item->setSizeHint(newAlert->sizeHint());

    ui->AlertList->addItem(item);
    ui->AlertList->setItemWidget(item, newAlert);

    ui->AlertList->setMinimumHeight(40);
}

void MainWindow::parse_alerts()
{
    // 버퍼를 써서 alerts들을 만든다.
}

void MainWindow::make_alerts_test()
{
    // // 시험용으로 쓰는 alert들 만들기. 위의 parse_alerts()를 임시 대체한다.
    // alerts.push_back(Alert{QDateTime(QDate(2025, 9, 8),QTime(9, 50, 30)), {192, 168, 2, 16}, {192, 168, 30, 14}, actionType::Accept, protocolType::TCP, 2600, 2500, severityType::Low});
    // alerts.push_back(Alert{QDateTime(QDate(2025, 9, 7),QTime(9, 45, 1)), {192, 168, 3, 1}, {192, 168, 1, 9}, actionType::Drop, protocolType::UDP, 20, 35, severityType::Critical});
    // alerts.push_back(Alert{QDateTime(QDate(2025, 9, 8),QTime(12, 01, 45)), {192, 168, 50, 9}, {192, 168, 32, 49}, actionType::Drop, protocolType::HTTP, 57, 42, severityType::High});
    // alerts.push_back(Alert{QDateTime(QDate(2025, 8, 29),QTime(0, 30, 22)), {192, 168, 62, 31}, {192, 168, 59, 97}, actionType::Drop, protocolType::TCP, 5, 98, severityType::High});

    // addAlert_test();

    // sort_alerts();

    // set_alertWidgets_withFilter();
}

void MainWindow::sort_alerts(alertAttributeType sortAttribute)
{
    int ip1 = 0;
    int ip2 = 0;
    std::function<bool(const Alert& a1, const Alert& a2)> sortFunc;

    sortAttributeOrder[sortAttribute] = !sortAttributeOrder[sortAttribute];

    if(sortAttributeOrder[sortAttribute]){
        switch(sortAttribute)
        {
            case alertAttributeType::SrcIP:
                sortFunc = [](const Alert& a1, const Alert& a2){
                    if(a1.srcIp[0] == a2.srcIp[0]){
                        if(a1.srcIp[1] == a2.srcIp[1]){
                            if(a1.srcIp[2] == a2.srcIp[2]){
                                return a1.srcIp[3] < a2.srcIp[3];
                            }
                            return a1.srcIp[2] < a2.srcIp[2];
                        }
                        return a1.srcIp[1] < a2.srcIp[1];
                    }
                    return a1.srcIp[0] < a2.srcIp[0];
                };
                break;

            case alertAttributeType::DestIP:
                sortFunc = [](const Alert& a1, const Alert& a2){
                    if(a1.dstIp[0] == a2.dstIp[0]){
                        if(a1.dstIp[1] == a2.dstIp[1]){
                            if(a1.dstIp[2] == a2.dstIp[2]){
                                return a1.dstIp[3] < a2.dstIp[3];
                            }
                            return a1.dstIp[2] < a2.dstIp[2];
                        }
                        return a1.dstIp[1] < a2.dstIp[1];
                    }
                    return a1.dstIp[0] < a2.dstIp[0];
                };
                break;

            case alertAttributeType::Protocol:
                sortFunc = [](const Alert& a1, const Alert& a2){
                    return a1.pType < a2.pType;
                };
                break;

            case alertAttributeType::SrcPort:
                sortFunc = [](const Alert& a1, const Alert& a2){
                    return a1.srcPort < a2.srcPort;
                };
                break;

            case alertAttributeType::DestPort:
                sortFunc = [](const Alert& a1, const Alert& a2){
                    return a1.dstPort < a2.dstPort;
                };
                break;

            case alertAttributeType::Severity:
                sortFunc = [](const Alert& a1, const Alert& a2){
                    return a1.sType < a2.sType;
                };
                break;
            default:
                sortFunc = [](const Alert& a1, const Alert& a2){
                    return a1.time < a2.time;
                };
                break;
        }
    }
    else{
        switch(sortAttribute)
        {
        case alertAttributeType::SrcIP:
            sortFunc = [](const Alert& a1, const Alert& a2){
                if(a1.srcIp[0] == a2.srcIp[0]){
                    if(a1.srcIp[1] == a2.srcIp[1]){
                        if(a1.srcIp[2] == a2.srcIp[2]){
                            return a1.srcIp[3] > a2.srcIp[3];
                        }
                        return a1.srcIp[2] > a2.srcIp[2];
                    }
                    return a1.srcIp[1] > a2.srcIp[1];
                }
                return a1.srcIp[0] > a2.srcIp[0];
            };
            break;

        case alertAttributeType::DestIP:
            sortFunc = [](const Alert& a1, const Alert& a2){
                if(a1.dstIp[0] == a2.dstIp[0]){
                    if(a1.dstIp[1] == a2.dstIp[1]){
                        if(a1.dstIp[2] == a2.dstIp[2]){
                            return a1.dstIp[3] > a2.dstIp[3];
                        }
                        return a1.dstIp[2] > a2.dstIp[2];
                    }
                    return a1.dstIp[1] > a2.dstIp[1];
                }
                return a1.dstIp[0] > a2.dstIp[0];
            };
            break;

        case alertAttributeType::Protocol:
            sortFunc = [](const Alert& a1, const Alert& a2){
                return a1.pType > a2.pType;
            };
            break;

        case alertAttributeType::SrcPort:
            sortFunc = [](const Alert& a1, const Alert& a2){
                return a1.srcPort > a2.srcPort;
            };
            break;

        case alertAttributeType::DestPort:
            sortFunc = [](const Alert& a1, const Alert& a2){
                return a1.dstPort > a2.dstPort;
            };
            break;

        case alertAttributeType::Severity:
            sortFunc = [](const Alert& a1, const Alert& a2){
                return a1.sType > a2.sType;
            };
            break;
        default:
            sortFunc = [](const Alert& a1, const Alert& a2){
                return a1.time > a2.time;
            };
            break;
        }
    }

    std::sort(alerts.begin(), alerts.end(), sortFunc);

    set_alertWidgets_withFilter();
}

void MainWindow::set_alertWidgets_withFilter()
{
    ui->AlertList->clear();






    int i = 0;
    for(auto& perAlert : alerts){
        // 시작 데이트타임 체크
        if(ui->dateTimeFromOnOff->checkState() == Qt::Checked && perAlert.time < ui->dateTimeFrom->dateTime()){
            continue;
        }
        // 끝 데이터타임 체크
        if(ui->dateTimeUntilOnOff->checkState() == Qt::Checked && perAlert.time > ui->dateTimeUntil->dateTime()){
            continue;
        }
        // action check
        if(!(ui->radioAlert->isChecked() && perAlert.aType == actionType::Accept) && !(ui->radioDrop->isChecked() && perAlert.aType == actionType::Drop)){
            continue;
        }
        // severity check. All이면 그냥 통과
        if(ui->SeveritySelect->currentText() == "Low" && perAlert.sType != severityType::Low)
        {
            continue;
        }
        else if(ui->SeveritySelect->currentText() == "High" && perAlert.sType != severityType::High){
            continue;
        }
        else if(ui->SeveritySelect->currentText() == "Critical" && perAlert.sType != severityType::Critical){
            continue;
        }
        // ProtocolSelect
        if(ui->ProtocolSelect->currentText() == "TCP" && perAlert.pType != protocolType::TCP){
            continue;
        }
        else if(ui->ProtocolSelect->currentText() == "UDP" && perAlert.pType != protocolType::UDP){
            continue;
        }
        else if(ui->ProtocolSelect->currentText() == "ICMP" && perAlert.pType != protocolType::ICMP){
            continue;
        }
        // Src ip 같지 않으면 continue. ip넣지 않으면 그냥 통과.
        if((!ui->SrcIP1->text().isEmpty() && ui->SrcIP1->text() != QString::number(perAlert.srcIp[0])) || (!ui->SrcIP2->text().isEmpty() && ui->SrcIP2->text() != QString::number(perAlert.srcIp[1]))
            || (!ui->SrcIP3->text().isEmpty() && ui->SrcIP3->text() != QString::number(perAlert.srcIp[2]) || (!ui->SrcIP4->text().isEmpty() && ui->SrcIP4->text() != QString::number(perAlert.srcIp[3])))){
            continue;
        }

        // Dest ip 같지 않으면 continue.
        if(!ui->DestIP1->text().isEmpty() && ui->DestIP1->text() != QString::number(perAlert.dstIp[0])){
            continue;
        }
        if(!ui->DestIP2->text().isEmpty() && ui->DestIP2->text() != QString::number(perAlert.dstIp[1])){
            continue;
        }
        if(!ui->DestIP3->text().isEmpty() && ui->DestIP3->text() != QString::number(perAlert.dstIp[2])){
            continue;
        }
        if(!ui->DestIP4->text().isEmpty() && ui->DestIP4->text() != QString::number(perAlert.dstIp[3])){
            continue;
        }

        // SrcPort 같지 않으면 continue.
        if(!ui->SrcPort->text().isEmpty() && ui->SrcPort->text() != QString::number(perAlert.srcPort)){
            continue;
        }
        // DstPort 같지 않으면 continue.
        if(!ui->DestPort->text().isEmpty() && ui->DestPort->text() != QString::number(perAlert.dstPort)){
            continue;
        }

        // addAlert(perAlert);
        addAlertWidget(perAlert);

        i++;
    }
}

// <침입탐지 위협 Top 5> 차트 초기화 함수
void MainWindow::initThreatTop5Chart()
{
    threatTop5Series = new QHorizontalBarSeries();
    threatTop5Chart = new QChart();
    threatTop5Chart->addSeries(threatTop5Series);
    threatTop5Chart->setTitle("침입탐지 위협 Top 5");
    threatTop5Chart->setAnimationOptions(QChart::SeriesAnimations);
    threatTop5Chart->legend()->hide();

    threatAxisY = new QBarCategoryAxis();
    threatTop5Chart->addAxis(threatAxisY, Qt::AlignLeft);
    threatTop5Series->attachAxis(threatAxisY);

    threatAxisX = new QValueAxis();
    threatAxisX->setRange(0, 10);
    threatTop5Chart->addAxis(threatAxisX, Qt::AlignBottom);
    threatTop5Series->attachAxis(threatAxisX);

    ui->threatTop5_widget->setChart(threatTop5Chart);
    ui->threatTop5_widget->setRenderHint(QPainter::Antialiasing);
}

// <침입탐지 출발지 IP Top 5> 차트 초기화 함수
void MainWindow::initSrcIpTop5Chart()
{
    srcIpTop5Series = new QHorizontalBarSeries();
    srcIpTop5Chart = new QChart();
    srcIpTop5Chart->addSeries(srcIpTop5Series);
    srcIpTop5Chart->setTitle("침입탐지 출발지 IP Top 5");
    srcIpTop5Chart->setAnimationOptions(QChart::SeriesAnimations);
    srcIpTop5Chart->legend()->hide();

    srcIpAxisY = new QBarCategoryAxis();
    srcIpTop5Chart->addAxis(srcIpAxisY, Qt::AlignLeft);
    srcIpTop5Series->attachAxis(srcIpAxisY);

    srcIpAxisX = new QValueAxis();
    srcIpAxisX->setRange(0, 10);
    srcIpTop5Chart->addAxis(srcIpAxisX, Qt::AlignBottom);
    srcIpTop5Series->attachAxis(srcIpAxisX);

    ui->startIPTop5_widget->setChart(srcIpTop5Chart);
    ui->startIPTop5_widget->setRenderHint(QPainter::Antialiasing);
}

// 5초마 모든 대시보드 차트를 업데이트하는 메인 슬롯
void MainWindow::updateDashboardCharts()
{
    // --- 1. 실시간 위협 누적 차트 업데이트 ---
    QDateTime now = QDateTime::currentDateTime();
    qint64 x = now.toMSecsSinceEpoch();
    int currentTotalAlerts = alerts.size(); // 현재까지 수신된 총 Alert 개수

    threatSeries->append(x, currentTotalAlerts);

    // X축 범위 조정 (최근 30초)
    if (!threatChart->axes(Qt::Horizontal).isEmpty()) {
        // QChart에서 수평 축(Horizontal Axis)을 가져와 QDateTimeAxis로 형변환
        auto *axisX = qobject_cast<QDateTimeAxis*>(threatChart->axes(Qt::Horizontal).first());
        if (axisX) {
            axisX->setRange(now.addSecs(-30), now);
        }
    }

    // Y축 범위 동적 조정
    if (!threatChart->axes(Qt::Vertical).isEmpty()) {
        // QChart에서 수직 축(Vertical Axis)을 가져와 QValueAxis로 형변환
        auto *axisY = qobject_cast<QValueAxis*>(threatChart->axes(Qt::Vertical).first());
        if (axisY && currentTotalAlerts > axisY->max()) {
            // Y축의 최대값을 현재 누적 위협 건수보다 약간 크게 설정
            axisY->setMax(currentTotalAlerts + currentTotalAlerts / 5 + 10);
        }
    }

    // --- 2. 위협 Top 5 차트 업데이트 (프로토콜 기반) ---
    QList<QPair<protocolType, int>> threatList;
    for(auto it = threatData.constBegin(); it != threatData.constEnd(); ++it) {
        threatList.append({it.key(), it.value()});
    }
    std::sort(threatList.begin(), threatList.end(), [](const auto& a, const auto& b) { return a.second > b.second; });

    QBarSet *newThreatSet = new QBarSet("Count");
    QStringList newThreatCategories;
    int maxThreatCount = (threatList.isEmpty() ? 10 : threatList.first().second);
    for (int i = 0; i < 5 && i < threatList.size(); ++i) {
        *newThreatSet << threatList[i].second;
        // protocolNames 배열을 사용하여 enum을 문자열로 변환
        newThreatCategories.prepend(protocolNames[threatList[i].first]);
    }
    threatTop5Series->clear();
    threatAxisY->clear();
    threatTop5Series->append(newThreatSet);
    threatAxisY->append(newThreatCategories);
    threatAxisX->setMax(maxThreatCount + maxThreatCount/5 + 1);

    // --- 3. 출발지 IP Top 5 차트 업데이트 ---
    QList<QPair<QString, int>> srcIpList;
    for(auto it = srcIpData.constBegin(); it != srcIpData.constEnd(); ++it) {
        srcIpList.append({it.key(), it.value()});
    }
    std::sort(srcIpList.begin(), srcIpList.end(), [](const auto& a, const auto& b) { return a.second > b.second; });

    QBarSet *newSrcIpSet = new QBarSet("Count");
    QStringList newSrcIpCategories;
    int maxIpCount = (srcIpList.isEmpty() ? 10 : srcIpList.first().second);
    for (int i = 0; i < 5 && i < srcIpList.size(); ++i) {
        *newSrcIpSet << srcIpList[i].second;
        newSrcIpCategories.prepend(srcIpList[i].first);
    }

    srcIpTop5Series->clear();
    srcIpTop5Series->append(newSrcIpSet);

    // Y축(카테고리) 업데이트: Qt::AlignLeft -> Qt::Vertical
    if (!srcIpTop5Chart->axes(Qt::Vertical).isEmpty()) {
        auto *axisY = qobject_cast<QBarCategoryAxis*>(srcIpTop5Chart->axes(Qt::Vertical).first());
        if (axisY) {
            axisY->clear();
            axisY->append(newSrcIpCategories);
        }
    }

    // X축(값) 업데이트: Qt::AlignBottom -> Qt::Horizontal
    if (!srcIpTop5Chart->axes(Qt::Horizontal).isEmpty()) {
        auto *axisX = qobject_cast<QValueAxis*>(srcIpTop5Chart->axes(Qt::Horizontal).first());
        if (axisX) {
            axisX->setMax(maxIpCount + maxIpCount/5 + 1);
        }
    }
}
