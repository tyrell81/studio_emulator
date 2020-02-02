#include "studio_client_worker.h"
#include "qt_helpers.h"
//#include "studio_packets.h"
#include "tcp_packets.h"
#include "studio_packets_util.h"

#define HOST "127.0.0.1"
#define PORT 20002

Q_LOGGING_CATEGORY(hfCoreStudioClientWorker, "hf.core.studio.worker")

StudioClientWorker::StudioClientWorker()
    : socket_{ new StudioTcpSocket() }
{
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

void StudioClientWorker::onReceivedPacket(const QByteArray &ba_packet)
{
    qCDebug(hfCoreStudioClientWorker) << ba_packet.toHex();
    studio_packet_out_cmd_a5_t cmd_a5;
    cmd_a5.header.cmd = 0xa5;
    cmd_a5.header.addr = 0x00000000;
//    cmd_a5.
}

void StudioClientWorker::sendCmdA5()
{
    qCDebug(hfCoreStudioClientWorker);
    studio_packet_request request_packet;
    request_packet.header.addr = 0x00000000;
    request_packet.header.cmd = 0xa5;
    QByteArray ba(reinterpret_cast<char*>(&request_packet), sizeof(studio_packet_request));
//    StudioPacketIn<studio_packet_header_t> packet(QByteArray ba);
    qCDebug(hfCoreStudioClientWorker()) <<
}
