#include <QDebug>
#include "network.h"
Network::Network()
{

}

void Network::init_camera(Camera *camera)
{
    _camera = camera;
    initSocket();
}

void Network::packet()
{

//    qDebug()<<_camera->_res_pos.angular_position.v[1];

}

void Network::initSocket()
  {
      udpSocket = new QUdpSocket(this);
      udpSocket->bind(QHostAddress::LocalHost, 7755);

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

        //processTheDatagram(datagram);
    }
}


