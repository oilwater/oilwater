#include <QDebug>
#include "network.h"
Network::Network()
{
    initSocket();
}

void Network::init_camera(Camera *camera)
{
    _camera = camera;
}

void Network::packet()
{
//    qDebug()<<_camera->_res_pos.angular_position.v[1];
}

void Network::initSocket()
  {
      udpSocket = new QUdpSocket(this);
      udpSocket->bind(QHostAddress::Any, 7755);

      connect(udpSocket, SIGNAL(readyRead()),
              this, SLOT(readPendingDatagrams()));
  }

void Network::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;


        udpSocket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);
        qDebug() << datagram;

        _camera->_res_pos.acceleration.v[0] = 0.3;
    }
}


