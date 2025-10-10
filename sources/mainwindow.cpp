#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"

#include "../headers/alertwidget.h"
#include "../headers/alertdialog.h"

#include <QTcpSocket>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    socket->connectToHost("192.168.2.29", 8085);

    // // test
    // addAlert_test();
    make_alerts_test();

    initailize_ui();

    connect(ui->AlertList, &QListWidget::itemDoubleClicked, this, &MainWindow::onAlertItemDoubleClicked);

    if (!socket->waitForConnected(3000)) {  // 최대 3초 대기
        qDebug() << "서버 접속 실패:" << socket->errorString();
        return;
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

void MainWindow::addAlert(const Alert &alert, int alertIndex)
{
    QListWidgetItem * item = new QListWidgetItem(ui->AlertList);

    AlertWidget* newAlert = new AlertWidget(alert, alertIndex, this);

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
    // 시험용으로 쓰는 alert들 만들기. 위의 parse_alerts()를 임시 대체한다.
    alerts.push_back(Alert{QDateTime(QDate(2025, 9, 8),QTime(9, 50, 30)), {192, 168, 2, 16}, {192, 168, 30, 14}, actionType::Accept, protocolType::TCP, 2600, 2500, severityType::Low});
    alerts.push_back(Alert{QDateTime(QDate(2025, 9, 7),QTime(9, 45, 1)), {192, 168, 3, 1}, {192, 168, 1, 9}, actionType::Drop, protocolType::UDP, 20, 35, severityType::Critical});
    alerts.push_back(Alert{QDateTime(QDate(2025, 9, 8),QTime(12, 01, 45)), {192, 168, 50, 9}, {192, 168, 32, 49}, actionType::Drop, protocolType::HTTP, 57, 42, severityType::High});
    alerts.push_back(Alert{QDateTime(QDate(2025, 8, 29),QTime(0, 30, 22)), {192, 168, 62, 31}, {192, 168, 59, 97}, actionType::Drop, protocolType::TCP, 5, 98, severityType::High});

    addAlert_test();

    sort_alerts();

    set_alertWidgets_withFilter();
}

void MainWindow::sort_alerts()
{

}

void MainWindow::set_alertWidgets_withFilter()
{
    ui->AlertList->clear();
    addAlert_test();

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
        else if(ui->ProtocolSelect->currentText() == "Http" && perAlert.pType != protocolType::HTTP){
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

        addAlert(perAlert, i);

        i++;
    }
}
