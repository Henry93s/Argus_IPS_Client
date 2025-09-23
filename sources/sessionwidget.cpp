#include "../headers/sessionwidget.h"
#include "ui_sessionwidget.h"
#include <QHeaderView>
#include <QTableWidgetItem>

#include <QWebEngineView>
#include <QVBoxLayout>
#include <QUrl>
// #include <QDebug>

SessionWidget::SessionWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::SessionWidget)
{
    ui->setupUi(this);
    initTable();
    initViewState();
}

SessionWidget::~SessionWidget()
{
    delete ui;
}

QTableWidget* SessionWidget::tableForProto(const QString& l4Proto) const
{
    const QString p = l4Proto.toUpper();
    if (p == "TCP")  return ui->tableWidget_4;  // page_7
    if (p == "UDP")  return ui->tableWidget_5;  // page_8
    // 기본은 ICMP로
    return ui->tableWidget_6;                   // page_9
}

void SessionWidget::initTable()
{
    auto initOne = [](QTableWidget* tw){
        tw->clear();
        tw->setColumnCount(6);
        tw->setHorizontalHeaderLabels(
            {"Address A","Address B","Packets","Bytes","Packets A->B","Packets B->A"});
        tw->setRowCount(0);
        tw->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tw->setSelectionBehavior(QAbstractItemView::SelectRows);
        tw->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tw->setAlternatingRowColors(true);
    };

    initOne(ui->tableWidget_4); // TCP
    initOne(ui->tableWidget_5); // UDP
    initOne(ui->tableWidget_6); // ICMP
}

void SessionWidget::clearAll()
{
    ui->tableWidget_4->setRowCount(0);
    ui->tableWidget_5->setRowCount(0);
    ui->tableWidget_6->setRowCount(0);
    rowOf.clear();
}

SessionWidget::Key SessionWidget::makeKey(const QString& src, quint16 sport,
                                          const QString& dst, quint16 dport,
                                          const QString& l4Proto) const
{
    const QString proto = l4Proto.toUpper();
    auto ep = [&](const QString& ip, quint16 port){
        return (proto == "ICMP") ? ip : (ip + ":" + QString::number(port));
    };

    QString a = ep(src, sport);
    QString b = ep(dst, dport);
    if (a <= b) return {a, b, proto};
    return {b, a, proto};
}

void SessionWidget::upsertSession(const QString& src, quint16 sport,
                                  const QString& dst, quint16 dport,
                                  const QString& l4Proto, quint32 bytes,
                                  bool dirAToB)
{
    // proto에 맞는 테이블 선택
    QTableWidget* tw = tableForProto(l4Proto);
    const auto key = makeKey(src, sport, dst, dport, l4Proto);

    int row;
    if (!rowOf.contains(key)) {
        row = tw->rowCount();
        tw->insertRow(row);
        tw->setItem(row, 0, new QTableWidgetItem(key.a));  // Address A
        tw->setItem(row, 1, new QTableWidgetItem(key.b));  // Address B
        tw->setItem(row, 2, new QTableWidgetItem("0"));    // Packets
        tw->setItem(row, 3, new QTableWidgetItem("0"));    // Bytes
        tw->setItem(row, 4, new QTableWidgetItem("0"));    // A->B
        tw->setItem(row, 5, new QTableWidgetItem("0"));    // B->A
        rowOf.insert(key, row);
    } else {
        row = rowOf.value(key);
    }

    auto inc = [&](int c, quint64 v){
        auto *it = tw->item(row, c);
        it->setText(QString::number(it->text().toULongLong() + v));
    };

    // 누적
    inc(2, 1);         // Packets +1
    inc(3, bytes);     // Bytes +bytes
    if (dirAToB) inc(4, 1); else inc(5, 1);
}

// View State init container
void SessionWidget::initViewState() {
    QWidget* box=this->findChild<QWidget*>("widget");
    if (!box) box=this->findChild<QWidget*>("viewStateBox");
    if (!box) return;

    // if do not have layout
    QVBoxLayout* lay=qobject_cast<QVBoxLayout*>(box->layout());
    if (!lay) {
        lay=new QVBoxLayout(box);
        lay->setContentsMargins(0,0,0,0);
    }
    // no duplication
    if (!viewStateView) {
        viewStateView=new QWebEngineView(box);
        viewStateView->setUrl(QUrl(QStringLiteral("http://127.0.0.1:8086")));
        lay->addWidget(viewStateView);
    }
}
