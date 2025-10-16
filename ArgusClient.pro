QT       += core gui charts network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    sources/Alert.cpp \
    sources/alertwidgetitem.cpp \
    sources/http_dns.cpp \
    sources/notes.cpp \
    sources/overview.cpp \
    sources/payload.cpp \
    sources/rawpacket.cpp \
    sources/related.cpp \
    sources/alertdialog.cpp \
    sources/cameraworker.cpp \
    sources/main.cpp \
    sources/mainwindow.cpp \
    sources/alertwidget.cpp

HEADERS += \
    headers/Alert.h \
    headers/alertdialog.h \
    headers/alertwidgetitem.h \
    headers/cameraworker.h \
    headers/http_dns.h \
    headers/mainwindow.h \
    headers/alertwidget.h \
    headers/notes.h \
    headers/overview.h \
    headers/payload.h \
    headers/rawpacket.h \
    headers/related.h

FORMS += \
    forms/alertdialog.ui \
    forms/http_dns.ui \
    forms/mainwindow.ui \
    forms/notes.ui \
    forms/overview.ui \
    forms/payload.ui \
    forms/rawpacket.ui \
    forms/related.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    headers/network/.gitdummy
