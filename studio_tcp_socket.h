/* Copyright Prosoft-Biometrics */

#ifndef HARDWARE_FRAMEWORK_CORE_STUDIO_STUDIO_TCP_SOCKET_H_
#define HARDWARE_FRAMEWORK_CORE_STUDIO_STUDIO_TCP_SOCKET_H_

#include <QByteArray>
#include <QHostAddress>
#include <QTcpSocket>

//#include "core/studio/studio_sharedlib.h"

//namespace core {

class StudioTcpSocket : public QTcpSocket {
    Q_OBJECT

public:
    explicit StudioTcpSocket(QObject* const parent = Q_NULLPTR);
    ~StudioTcpSocket();

    virtual void init();

public slots:
    void sendPacket(const QByteArray& ba_packet);

signals:
    void recivedPacket(const QByteArray& ba_packet);
    void sendedPacket(const bool status);

protected:
    bool send(const QByteArray& ba_packet);

    virtual const QLoggingCategory& logCategory() const;

protected slots:
    virtual void onStateChanged(const QAbstractSocket::SocketState state);
    virtual void onError(const QAbstractSocket::SocketError socketError);

private slots:
    void onReadyRead();
    void resetRxBuff();

private:
    int rx_max_size_{ 1024 * 1024 };
    bool pb_protocol_wait_start_byte_{ true };
    QByteArray rx_buff_;
};

//} // namespace core

#endif // HARDWARE_FRAMEWORK_CORE_STUDIO_STUDIO_TCP_SOCKET_H_
