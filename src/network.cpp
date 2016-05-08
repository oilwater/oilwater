#include <QDebug>
#include "network.h"
Network::Network()
{

}

void Network::init_camera(Camera *camera)
{
    _camera = camera;
}

void Network::packet()
{
//    qDebug()<<_camera->_res_pos.angular_position.v[1];

}
