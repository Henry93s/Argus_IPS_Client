#ifndef SESSIONWIDGET_H
#define SESSIONWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QHash>
#include <QString>

namespace Ui { class SessionWidget; }

class SessionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SessionWidget(QWidget *parent = nullptr);
    ~SessionWidget();

    void clearAll();

    // 세션 집계/업데이트: dirAToB=true면 A->B 패킷/바이트 카운트
    void upsertSession(const QString& src, quint16 sport,
                       const QString& dst, quint16 dport,
                       const QString& l4Proto, quint32 bytes,
                       bool dirAToB);

private:
    Ui::SessionWidget *ui;

public:
    struct Key {
        QString a, b, proto;                // 정규화된 endpoint A/B, 대문자 PROTO
        bool operator==(const Key& o) const { return a==o.a && b==o.b && proto==o.proto; }
        friend uint qHash(const Key& k, uint seed) noexcept;  // ← friend 선언
    };

private:
    // proto별 테이블의 행 인덱스 저장 (Key에 proto 포함됨)
    QHash<Key, int> rowOf;

    // 주소/포트 정규화 + A/B 정렬
    Key makeKey(const QString& src, quint16 sport,
                const QString& dst, quint16 dport,
                const QString& l4Proto) const;

    // UI 초기화 (세 개 테이블 공통 헤더 적용)
    void initTable();

    // "TCP"/"UDP"/"ICMP" → 해당 TableWidget 반환
    QTableWidget* tableForProto(const QString& l4Proto) const;
};

// Key 해시 (friend로 선언되어 있어야 템플릿 인스턴스 가능 타이밍 안전)
inline uint qHash(const SessionWidget::Key &k, uint seed) noexcept {
    return qHash(k.a, seed) ^ qHash(k.b, seed << 1) ^ qHash(k.proto, seed << 2);
}

#endif // SESSIONWIDGET_H
