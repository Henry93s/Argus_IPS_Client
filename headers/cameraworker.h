#ifndef CAMERAWORKER_H
#define CAMERAWORKER_H

// #include <QThread>
#include <QObject>
#include <QImage>
#include <QMutex>



class QTcpSocket;

class CameraWorker : public QObject
{
    Q_OBJECT

public:
    explicit CameraWorker(QObject *parent = nullptr);
    ~CameraWorker();

public slots:
    // 새로운 스레드에서 실행될 실제 로직
    void process(const QString &host, quint16 port);
    void stop(); // 외부에서 중지 신호를 보낼 슬롯

signals:
    void frameReady(const QImage &image);
    void motionDetected(const QString &timestamp);
    void cameraError(const QString &errorString);
    void cameraConnected();
    void cameraDisconnected();
    void finished(); // 작업이 완료되었음을 알리는 시그널

private:
    // YUYV to RGB 변환 함수
    void yuyv_to_rgb24(const unsigned char *yuyv, unsigned char *rgb, int width, int height);
    // 간단한 움직임 탐지 함수
    bool detectMotion(const unsigned char* grayFrame);

    volatile bool m_isRunning;
    QMutex m_mutex;

    // 이미지 크기 및 움직임 탐지용 버퍼
    int m_width;
    int m_height;
    unsigned char* m_prevGrayFrame;
};

#endif // CAMERAWORKER_H
