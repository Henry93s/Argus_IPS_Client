#ifndef ALERT_H
#define ALERT_H

#include <QDateTime>

enum alertAttributeType {
    Time,
    SrcIP,
    DestIP,
    Protocol,
    SrcPort,
    DestPort,
    Severity
};

enum actionType{
    Accept,
    Drop
};

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
    actionType aType;
    protocolType pType;
    unsigned short srcPort;
    unsigned short dstPort;
    severityType sType;

    static QString GetIpStr(const unsigned char ip[4]) { return QString::number(ip[0]) + QString(".") + QString::number(ip[1]) + QString(".") + QString::number(ip[1]) + QString(".")
                                         + QString::number(ip[2]) + QString(".") + QString::number(ip[3]);}
} Alert;

#endif // ALERT_H
