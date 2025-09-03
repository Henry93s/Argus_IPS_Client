#ifndef ALERT_H
#define ALERT_H

#include <QDateTime>

enum protocolType {
    TCP,
    UDP,
    HTTP
};

enum severityType {
    Low,
    High,
    Critical
};

typedef struct alert{
    QDateTime time;
    unsigned char srcIp[4];
    unsigned char dstIp[4];
    protocolType pType;
    unsigned short srcPort;
    unsigned short dstPort;
    severityType sType;
} Alert;

#endif // ALERT_H
