#ifndef NETWORK_H
#define NETWORK_H

#include "camera.h"

#define DEF_PORT 33333

class Network
{
public:
    Network();
    void init_camera(Camera * camera);
    void packet();
    void initSocket();
private:
    Camera * _camera;
};

#endif // NETWORK_H
