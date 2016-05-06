/*
 * camera.h
 *
 *  Created on: Apr 1, 2015
 *      Author: rainautumn
 */
#ifndef CAMERA_H
#define CAMERA_H


#define FREE_LOOK 0
#define LOCK_LOOK 1
#define TERMINAL_LOOK 2

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
    mtx4 get_matrix_sprite();
    mtx4 get_matrix_hp();
    void set_default_position(bool value);
    void set_monitor(float h ,float w);

    void set_mouse(double xpos, double ypos);
    void set_keymap(int key, int scancode, int action, int mods);

    res_cam _res_cam;

    char cam_type;

    bool lock_position;
private:
    float monitor_h, monitor_w;
    void set_res_cam(mtx4 buf_mtx);
};

#endif // CAMERA_H
