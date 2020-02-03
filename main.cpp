#include <QCoreApplication>
#include "studio_client_worker.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    StudioClientWorker* worker = new StudioClientWorker();
    worker->start();

    qDebug("NEAR");
    a.exec();
    qDebug("STOPPED");
//    return a.exec();
}
