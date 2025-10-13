#include "../headers/cameraworker.h"
#include <QDateTime>
#include <QDebug>
#include <QTcpSocket>
#include <QThread>
#include <vector>

CameraWorker::CameraWorker(QObject *parent)
    : QObject(parent), m_isRunning(false),
    m_width(640), m_height(480), m_prevGrayFrame(nullptr)
{
}

CameraWorker::~CameraWorker()
{
    qDebug() << "CameraWorker 중지";
    if (m_prevGrayFrame) {
        delete[] m_prevGrayFrame;
    }
}

void CameraWorker::stop()
{
    QMutexLocker locker(&m_mutex);
    m_isRunning = false;
}

void CameraWorker::process(const QString &host, quint16 port)
{
    {
        QMutexLocker locker(&m_mutex);
        m_isRunning = true;
    }

    QTcpSocket socket;
    socket.connectToHost(host, port);

    if (!socket.waitForConnected(5000)) {
        emit cameraError(QString("카메라 서버 연결 실패: %1").arg(socket.errorString()));
        emit finished();
        return;
    }
    emit cameraConnected();

    const int frameSize = m_width * m_height * 2; // YUYV (픽셀당 2바이트)
    QByteArray buffer;

    // 이전 프레임 버퍼가 없다면 할당
    if (!m_prevGrayFrame) {
        m_prevGrayFrame = new unsigned char[m_width * m_height];
    }
    memset(m_prevGrayFrame, 0, m_width * m_height);

    while (true) {
        {
            QMutexLocker locker(&m_mutex);
            if (!m_isRunning) break;
        }

        while (socket.bytesAvailable() < frameSize) {
            if (!socket.waitForReadyRead(1000)) {
                if (socket.state() == QAbstractSocket::UnconnectedState) {
                    emit cameraError("카메라 서버 연결 끊김.");
                    goto cleanup;
                }
            }
            if(!m_isRunning) goto cleanup;
        }

        buffer = socket.read(frameSize);
        if (buffer.size() < frameSize) continue; // 데이터가 충분하지 않으면 무시

        // --- YUYV to RGB 변환 ---
        unsigned char* rgb_buffer = new unsigned char[m_width * m_height * 3];
        yuyv_to_rgb24((const unsigned char*)buffer.constData(), rgb_buffer, m_width, m_height);

        // --- 움직임 감지 ---
        unsigned char* gray_buffer = new unsigned char[m_width * m_height];
        for (int i = 0; i < m_width * m_height; ++i) {
            gray_buffer[i] = ((const unsigned char*)buffer.constData())[i*2]; // Y값만 추출
        }
        if (detectMotion(gray_buffer)) {
            emit motionDetected(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        }
        memcpy(m_prevGrayFrame, gray_buffer, m_width * m_height);
        delete[] gray_buffer;

        // --- QImage로 변환 및 시그널 발생 ---
        QImage image(rgb_buffer, m_width, m_height, QImage::Format_RGB888,
                     [](void *info){ delete[] (unsigned char*)info; }, rgb_buffer);
        emit frameReady(image.copy());
    }

cleanup:
    socket.disconnectFromHost();
    emit cameraDisconnected();
    qDebug() << "카메라 작업 루프 종료.";
    emit finished();
}


// YUYV 형식의 픽셀 데이터를 RGB888 형식으로 변환하는 함수.
void CameraWorker::yuyv_to_rgb24(const unsigned char *yuyv, unsigned char *rgb, int width, int height)
{
    // YUYV(YUV422) 포맷은 4바이트 묶음(Y1, U, Y2, V)이 2개의 픽셀 정보를 표현
    // 즉, 2개의 Y(밝기) 값은 각각의 픽셀에 적용되고, 1개의 U, V(색상차) 값은 두 픽셀에 공통으로 적용

    // 루프는 (width * height / 2) 번 반복하여 전체 픽셀을 처리
    for (int i = 0; i < width * height / 2; ++i) {
        // 1. YUYV 데이터 묶음에서 각 성분 추출
        // i * 4 는 현재 처리할 YUYV 묶음의 시작 위치
        int y1 = yuyv[i * 4 + 0]; // 첫 번째 픽셀의 밝기(Y)
        int u  = yuyv[i * 4 + 1]; // 두 픽셀의 공통 색상차(U)
        int y2 = yuyv[i * 4 + 2]; // 두 번째 픽셀의 밝기(Y)
        int v  = yuyv[i * 4 + 3]; // 두 픽셀의 공통 색상차(V)

        // 2. YUV를 RGB로 변환하기 위한 중간 값 계산
        // 표준 변환 공식(ITU-R BT.601)을 정수 연산에 맞게 조정
        // 부동 소수점 연산은 성능 저하를 유발할 수 있으므로 정수 연산을 사용
        int c1 = y1 - 16;
        int c2 = y2 - 16;
        int d = u - 128;
        int e = v - 128;

        // 3. 각 픽셀의 R, G, B 값을 계산
        // 비트 쉬프트(>> 8) 연산은 256으로 나누는 것과 동일한 효과의 빠른 연산

        // 첫 번째 픽셀 (Y1, U, V) -> (R1, G1, B1)
        int r1 = (298 * c1 + 409 * e + 128) >> 8;
        int g1 = (298 * c1 - 100 * d - 208 * e + 128) >> 8;
        int b1 = (298 * c1 + 516 * d + 128) >> 8;

        // 두 번째 픽셀 (Y2, U, V) -> (R2, G2, B2)
        int r2 = (298 * c2 + 409 * e + 128) >> 8;
        int g2 = (298 * c2 - 100 * d - 208 * e + 128) >> 8;
        int b2 = (298 * c2 + 516 * d + 128) >> 8;

        // 4. 계산된 RGB 값이 유효한 범위(0~255)를 벗어나지 않도록 보정(클램핑(Clamping))
        auto clamp = [](int val) { return val < 0 ? 0 : (val > 255 ? 255 : val); };

        // 5. 최종 RGB 값을 출력 버퍼에 저장
        // QImage::Format_RGB888 은 픽셀당 3바이트(R, G, B 순서)를 사용
        // YUYV 4바이트가 RGB 6바이트로 변환되므로, 출력 버퍼의 인덱스는 i * 6

        // 첫 번째 픽셀의 RGB 값 저장
        rgb[i * 6 + 0] = clamp(r1); // red
        rgb[i * 6 + 1] = clamp(g1); // green
        rgb[i * 6 + 2] = clamp(b1); // blue

        // 두 번째 픽셀의 RGB 값 저장
        rgb[i * 6 + 3] = clamp(r2); // red
        rgb[i * 6 + 4] = clamp(g2); // green
        rgb[i * 6 + 5] = clamp(b2); // blu
    }
}

// 이전 프레임과 현재 프레임의 차이를 계산하는 간단한 움직임 탐지
bool CameraWorker::detectMotion(const unsigned char* grayFrame)
{
    // 1. 픽셀 밝기 변화를 감지하는 민감도 (값이 낮을수록 민감)
    // 두 프레임 간의 픽셀 밝기 차이가 얼마 이상일 때 '변화'로 인정할 것인가? 를 결정
    const int diff_threshold = 25;

    // 2. 움직임으로 판단할 최소 픽셀 비율 (값이 높을수록 둔감)
    // 변화된 픽셀의 총 개수가 얼마 이상일 때 '의미 있는 움직임'으로 판단할 것인가? 를 결정

    // 기존 : 1% (640x480 기준 약 3,072개 픽셀)만 변해도 움직임
    // 변경:  전체 화면의 20% (3072 * 20 개 픽셀) 이상이 변해야 움직임으로 간주
    const int motion_pixels_threshold = (m_width * m_height) * 0.20;

    int motion_pixels_count = 0;
    for (int i = 0; i < m_width * m_height; ++i) {
        if (abs(grayFrame[i] - m_prevGrayFrame[i]) > diff_threshold) {
            motion_pixels_count++;
        }
    }

    return motion_pixels_count > motion_pixels_threshold;
}
