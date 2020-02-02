#include "studio_client_worker.h"
#include "qt_helpers.h"

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
}

void StudioClientWorker::sendCmdA5()
{
    qCDebug(hfCoreStudioClientWorker);
}
