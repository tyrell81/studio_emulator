#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QDataStream>
#include <QObject>
#include <QTcpSocket>

class TcpClient {
public:
    TcpClient();
    ~TcpClient();

public:
    void connectToServer(const QString& host, int port); // Подключение к серверу
    void send(QString data);
    void send(QByteArray data);

signals:
    void connected();
    void dataReceived(QByteArray data);

private slots:
    void onConnected();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError error);

private:
    QTcpSocket* tcp_socket_;
    int rx_max_size_{ 1024 * 1024 };
    bool pb_protocol_wait_start_byte_{ true };
    QByteArray rx_buff_;
};

#endif // TCPCLIENT_H
