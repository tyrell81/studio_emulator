#include "tcpclient.h"

TcpClient::TcpClient()
{
}

TcpClient::~TcpClient()
{
}

void TcpClient::connectToServer(const QString& host, int port)
{
}

void TcpClient::send(QString data)
{
}

void TcpClient::send(QByteArray data)
{
}

void TcpClient::onConnected()
{
}

void TcpClient::onReadyRead()
{
    if (bytesAvailable() < PB_PROTOCOL_MIN_IN_SIZE && rx_buff_.isEmpty())
        return;

    while (bytesAvailable() > 0 && rx_buff_.size() < rx_max_size_) {
        uint8_t c = 0;
        if (read(reinterpret_cast<char*>(&c), 1) != 1) {
            qCWarning(logCategory) << "read error:" << errorString();
            continue;
        }

        if (pb_protocol_wait_start_byte_ && c == PB_PROTOCOL_START_BYTE) {
            rx_buff_.append(c);
            pb_protocol_wait_start_byte_ = false;
            continue;
        }

        rx_buff_.append(c);

        int res = pb_protocol_check_packet(rx_buff_.constData(), rx_buff_.size());
        if (res != PB_PROTOCOL_SUCCESS)
            continue;

        res = pb_protocol_unpack(rx_buff_.data(), rx_buff_.size());
        if (res < PB_PROTOCOL_SUCCESS) {
            qCWarning(logCategory, "pb_protocol_unpack packet_size(%d), error(%s)",
                rx_buff_.size(), pb_protocol_strerror(res));
            resetRxBuff();
            continue;
        }

        rx_buff_.resize(res);

        qCDebug(logCategory) << "rx:" << rx_buff_.toHex();
        emit recivedPacket(rx_buff_);
        resetRxBuff();
    }

    if (rx_buff_.size() >= rx_max_size_) {
        qCWarning(logCategory) << "rx_buff_.size() >= rx_max_size_";
        resetRxBuff();
    }
}

void TcpClient::onError(QAbstractSocket::SocketError err)
{
    if (err == QAbstractSocket::HostNotFoundError)
        qCritical("HostNotFoundError");
    else if (err == QAbstractSocket::RemoteHostClosedError)
        qCritical("RemoteHostClosedError");
    else if (err == QAbstractSocket::ConnectionRefusedError)
        qCritical("ConnectionRefusedError");
    else
        qCritical() << tcp_socket_->errorString();

    tcp_socket_->disconnectFromHost();
}
