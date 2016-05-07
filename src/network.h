#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include "camera.h"
class Network
{
public:
    Network();
    void init_camera(Camera * camera);
    void packet();
private:
    Camera * _camera;
};

#endif // NETWORK_H
