#ifndef STUDIOWORKER_H
#define STUDIOWORKER_H

#include "studio_tcp_socket.h"

class StudioClientWorker : public QObject {
    Q_OBJECT

public:
    StudioClientWorker();
    ~StudioClientWorker();

    void start();
    void stop();

protected slots:
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError socket_error);
    void onStateChanged(QAbstractSocket::SocketState socket_state);

    void onReceivedPacket(const QByteArray& ba_packet);

private:
    void sendCmdA5();

private:
    StudioTcpSocket* socket_;
};

#endif // STUDIOWORKER_H
