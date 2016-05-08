#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QUdpSocket>
#include "camera.h"
class Network:QObject
{
    Q_OBJECT
public:
    Network();
    void init_camera(Camera * camera);
    void packet();
    void initSocket();
private:
    Camera * _camera;
    QUdpSocket * udpSocket;
private slots:
    void readPendingDatagrams();
};

#endif // NETWORK_H
