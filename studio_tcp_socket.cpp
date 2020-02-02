/* Copyright Prosoft-Biometrics */

#include "studio_tcp_socket.h"

#include "pb_protocol.h"
#include "qt_helpers.h"
#include <QTimer>

//#include "core/database/settings.h"

//namespace core {

Q_LOGGING_CATEGORY(hfCoreSTSocket, "hf.core.studio.tcp.socket")

StudioTcpSocket::StudioTcpSocket(QObject* const parent)
    : QTcpSocket(parent)
{
    qCDebug(logCategory);
    connect(this, &QTcpSocket::readyRead, this, &StudioTcpSocket::onReadyRead);
    connect(this, qOverload<QAbstractSocket::SocketError>(&QAbstractSocket::error), this, &StudioTcpSocket::onError);
    connect(this, &QTcpSocket::disconnected, this, &StudioTcpSocket::resetRxBuff);
}

void StudioTcpSocket::init()
{
    auto inactive_timer = new QTimer(this);
    inactive_timer->setSingleShot(true);
    const auto& setting_tcp_timeout = 7000;
    inactive_timer->setInterval(setting_tcp_timeout * 10000);

    connect(this, &QTcpSocket::disconnected, inactive_timer, &QTimer::stop);
    connect(this, &StudioTcpSocket::recivedPacket, inactive_timer, qOverload(&QTimer::start));
    connect(inactive_timer, &QTimer::timeout, this, [=] {
        qCWarning(logCategory) << "inactive_timer timeout";
        disconnectFromHost();
    });

    inactive_timer->start();
}

void StudioTcpSocket::sendPacket(const QByteArray& ba_packet)
{
    qCDebug(logCategory);
    bool res = send(ba_packet);
    qCDebug(logCategory) << "res:" << res;
    emit sendedPacket(res);
}

bool StudioTcpSocket::send(const QByteArray& ba_packet)
{
    qCDebug(logCategory) << "tx:" << ba_packet.toHex();

    QByteArray buff(PB_PROTOCOL_OUT_SIZE(ba_packet.size()), 0);

    const auto res = pb_protocol_pack(buff.data(), buff.size(), ba_packet.constData(), ba_packet.size());
    if (res < PB_PROTOCOL_SUCCESS) {
        qCCritical(logCategory) << "pack failed";
        return false;
    }

    auto sent = write(buff.constData(), res);
    if (sent != (qint64)res) {
        qCCritical(logCategory) << QString("tx not full package: %1/%2").arg(sent).arg(res);
        return false;
    }

    if (!flush())
        qCWarning(logCategory) << "tx not flush";

    qCDebug(logCategory) << "tx packed:" << buff.mid(0, res).toHex();
    return true;
}

const HFLoggingCategory& StudioTcpSocket::logCategory() const
{
    return hfCoreSTSocket();
}

void StudioTcpSocket::onStateChanged(const QAbstractSocket::SocketState state)
{
    qCInfo(logCategory) << peerAddress() << peerPort() << state;
}

void StudioTcpSocket::onError(const QAbstractSocket::SocketError error)
{
    qCWarning(logCategory) << peerAddress() << peerPort() << error;
    disconnectFromHost();
}

void StudioTcpSocket::onReadyRead()
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

void StudioTcpSocket::resetRxBuff()
{
    pb_protocol_wait_start_byte_ = true;
    rx_buff_.resize(0);
}

StudioTcpSocket::~StudioTcpSocket()
{
    if (state() == QAbstractSocket::ConnectedState)
        disconnectFromHost();

    qCDebug(logCategory);
}

//} // namespace core
