/*
 * camera.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: rainautumn
 */
#include "camera.h"
#include <iostream>
#include <GLFW/glfw3.h>

#define sence 4000.0
using namespace std;


Camera::Camera()
{
    _res_pos.position.drop();
    _res_pos.angular_position.drop();
    _res_pos.position.init(0, 0, -10);
}

mtx4 Camera::get_matrix()
{
    mtx4 buf_position;
    buf_position.tranform_position(_res_pos.position);
    mtx4 buf_angular;
    buf_angular.tranform_angle(_res_pos.angular_position);
    mtx4 buf_perspective;
    buf_perspective.perspective(1,1,0.5,150);
    get_res_cam(buf_angular);

    return buf_perspective * buf_angular * buf_position;
}

void Camera::set_mouse(double xpos, double ypos)
{
    _res_pos.angular_position.v[1] += (400 - xpos) / sence;
    _res_pos.angular_position.v[0] += (400 - ypos) / sence;
}

void Camera::set_keymap(int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_W && action == GLFW_PRESS)
        _res_pos.position += _res_cam.normal.orterisation();
    if(key == GLFW_KEY_S && action == GLFW_PRESS)
        _res_pos.position -= _res_cam.normal.orterisation();

    if(key == GLFW_KEY_A && action == GLFW_PRESS)
        _res_pos.position += _res_cam.tangent.orterisation();
    if(key == GLFW_KEY_D && action == GLFW_PRESS)
        _res_pos.position -= _res_cam.tangent.orterisation();
}

void Camera::get_res_cam(mtx4 buf_mtx)
{
    _res_cam.tangent.init(buf_mtx.m[0][0],
                          buf_mtx.m[0][1],
                          buf_mtx.m[0][2]);

    _res_cam.bitangent.init(buf_mtx.m[1][0],
                            buf_mtx.m[1][1],
                            buf_mtx.m[1][2]);

    _res_cam.normal.init(buf_mtx.m[2][0],
                         buf_mtx.m[2][1],
                         buf_mtx.m[2][2]);
}
