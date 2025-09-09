#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"

#include "../headers/alertwidget.h"
#include "../headers/sessionwidget.h"

#include <QTcpSocket>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->widget_5->setLayout(new QVBoxLayout);
    ui->widget_5->layout()->setContentsMargins(0, 0, 0, 0);
    ui->widget_5->layout()->addWidget(new SessionWidget(this));

    socket = new QTcpSocket(this);
    socket->connectToHost("192.168.2.29", 8085);

    // test
    addAlert_test();

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
