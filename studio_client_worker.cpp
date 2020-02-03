#include "studio_client_worker.h"
#include "qt_helpers.h"
//#include "studio_packets.h"
#include "studio_packets_util.h"
#include "tcp_packets.h"

#define HOST "192.168.0.19" //"127.0.0.1"
#define PORT 20002
#define DEVICE_SERIAL 0x00000000

Q_LOGGING_CATEGORY(hfCoreStudioClientWorker, "hf.core.studio.worker")

StudioClientWorker::StudioClientWorker()
    : socket_{ new StudioTcpSocket() }
{
    connect(socket_, &StudioTcpSocket::connected, this, &StudioClientWorker::onConnected);
    connect(socket_, &StudioTcpSocket::disconnected, this, &StudioClientWorker::onDisconnected);
    //    connect(socket_, &StudioTcpSocket::error, this, &StudioClientWorker::onError);
    connect(socket_, &StudioTcpSocket::stateChanged, this, &StudioClientWorker::onStateChanged);
    connect(socket_, &StudioTcpSocket::recivedPacket, this, &StudioClientWorker::onReceivedPacket);
}

StudioClientWorker::~StudioClientWorker()
{
    stop();
    if (socket_) {
        socket_->deleteLater();
        socket_ = Q_NULLPTR;
    }
}

void StudioClientWorker::start()
{
    qCDebug(hfCoreStudioClientWorker()) << "before";
    socket_->connectToHost(HOST, PORT);
}

void StudioClientWorker::stop()
{
    if (socket_->state() != QAbstractSocket::SocketState::UnconnectedState && socket_->state() != QAbstractSocket::SocketState::ClosingState) {
        qCDebug(hfCoreStudioClientWorker) << "Close socket";
        socket_->close();
    }
}

void StudioClientWorker::onConnected()
{
    qCDebug(hfCoreStudioClientWorker) << "Socket connected";
    sendCmdA5();
}

void StudioClientWorker::onDisconnected()
{
    qCDebug(hfCoreStudioClientWorker) << "Socket disconnected";
}

void StudioClientWorker::onError(QAbstractSocket::SocketError socket_error)
{
    qCWarning(hfCoreStudioClientWorker) << "Socket ERROR:" << socket_error;
}

void StudioClientWorker::onStateChanged(QAbstractSocket::SocketState socket_state)
{
    qCDebug(hfCoreStudioClientWorker) << "Socket state changed:" << socket_state;
}

void StudioClientWorker::onReceivedPacket(const QByteArray& ba_recv_packet)
{
    qCDebug(hfCoreStudioClientWorker) << ba_recv_packet.toHex();
    StudioPacketIn<studio_packet_header_t> recv_packet(ba_recv_packet);

    switch (recv_packet->cmd) {
    case 0xa5: {
        if (ba_recv_packet.size() < sizeof(studio_packet_result)) {
            qCWarning(hfCoreStudioClientWorker()) << "Wrong buffer size:" << ba_recv_packet.size();
        }
        studio_packet_result* res = (studio_packet_result*)ba_recv_packet.constData();
        qCDebug(hfCoreStudioClientWorker()) << "Command 0xa5 result:" << res->result;
        if (res->result == 0)
            qCInfo(hfCoreStudioClientWorker()) << "Result OK!";
        else
            sendCmdA5();
        break;
     }
    default:
        qCWarning(hfCoreStudioClientWorker()) << "Unknown command:" << QString("cmd_%1").arg(recv_packet->cmd, 2, 16, QChar('0'));
        break;
    }
}

void StudioClientWorker::sendCmdA5()
{
    qCDebug(hfCoreStudioClientWorker);
    studio_packet_request request_packet;
    request_packet.header.addr = 0x00000000;
    request_packet.header.cmd = 0xa5;
    QByteArray ba(reinterpret_cast<char*>(&request_packet), sizeof(studio_packet_request));
    //    StudioPacketIn<studio_packet_header_t> packet(QByteArray ba);
    qCDebug(hfCoreStudioClientWorker()) << "ba.size:" << ba.size() << ":" << ba.toHex();
    socket_->sendPacket(ba);
}
