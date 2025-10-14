#ifndef RAWPACKET_H
#define RAWPACKET_H

#include <QWidget>
#include "Alert.h"

namespace Ui {
class RawPacket;
}

class RawPacket : public QWidget
{
    Q_OBJECT

public:
    explicit RawPacket(QWidget *parent = nullptr);
    explicit RawPacket(const Alert* alert, QWidget *parent = nullptr);
    ~RawPacket();

private:
    Ui::RawPacket *ui;
};

#endif // RAWPACKET_H
