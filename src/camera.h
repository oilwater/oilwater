/*
 * camera.h
 *
 *  Created on: Apr 1, 2015
 *      Author: rainautumn
 */
#ifndef CAMERA_H
#define CAMERA_H

#include "glmath.hpp"
#include "position.h"

struct res_cam
{
    vtx3 normal;
    vtx3 tangent;
    vtx3 bitangent;
};

class Camera : public Position
{
public:
    Camera();

    mtx4 get_matrix();

    void set_default_position(bool value);
    void set_monitor(float h ,float w);

    void set_mouse(double xpos, double ypos);
    void set_keymap(int key, int scancode, int action, int mods);

    res_cam _res_cam;
private:
    float monitor_h, monitor_w;
    void set_res_cam(mtx4 buf_mtx);
    bool default_position;
};

#endif // CAMERA_H
