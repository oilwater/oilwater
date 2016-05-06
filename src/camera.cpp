/*
 * camera.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: rainautumn
 */
#include "camera.h"
#include <iostream>
#include <GLFW/glfw3.h>

#define sence 1000.0
using namespace std;


Camera::Camera()
{
    cam_type = 0;
    Position();
    lock_position = false;
	monitor_h = 1;
	monitor_w = 1;
    _res_pos.angular_position.init(0, 0, 0);
    _res_pos.position.init(0, 0, 0);
}

void Camera::set_default_position(bool value)
{
    lock_position = value;
}

void Camera::set_monitor(float h ,float w)
{
	monitor_h = h;
	monitor_w = w;
}

mtx4 Camera::get_matrix()
{
    mtx4 buf_position;
	mtx4 buf_angular;
    if(lock_position)
	{
		buf_position.init();
        _res_pos.angular_position.init(0, 0, 0);
		buf_angular.tranform_angle(_res_pos.angular_position);
	}
	else
	{
		_res_pos.acceleration -= _res_pos.acceleration / 10;
		_res_pos.velocity -= _res_pos.velocity / 10;
	    _res_pos.velocity += _res_pos.acceleration / 4;
	    _res_pos.position += _res_pos.velocity / 4;
		buf_position.tranform_position(_res_pos.position);
		buf_angular.tranform_angle(_res_pos.angular_position);
	}
    mtx4 buf_perspective;
    buf_perspective.perspective(0.3, 0.3 * monitor_w/monitor_h, 0.3, 150);

    set_res_cam(buf_angular);

    return buf_perspective * buf_angular * buf_position;
}

mtx4 Camera::get_matrix_sprite()
{
    mtx4 buf_position;
    mtx4 buf_angular;
    if(lock_position)
    {
        buf_position.init();
        _res_pos.angular_position.init(0, 0, 0);
        buf_angular.tranform_angle(_res_pos.angular_position);
    }
    else
    {
        _res_pos.acceleration -= _res_pos.acceleration / 10;
        _res_pos.velocity -= _res_pos.velocity / 10;
        _res_pos.velocity += _res_pos.acceleration / 4;
        _res_pos.position += _res_pos.velocity / 4;
        buf_position.tranform_position(_res_pos.position);
        buf_angular.tranform_angle(_res_pos.angular_position);
    }
    mtx4 buf_perspective;
    buf_perspective.perspective(0.3, 0.3 * monitor_w/monitor_h, 0.3, 150);

    return buf_perspective * buf_angular * buf_position;
}

mtx4 Camera::get_matrix_hp()
{
    mtx4 buf_perspective;
    buf_perspective.perspective(0.3, 0.3 * monitor_w/monitor_h, 0.3, 150);

    return buf_perspective;
}

void Camera::set_mouse(double xpos, double ypos)
{
    _res_pos.angular_position.v[1] += (monitor_w/2.0 - xpos) / sence;
    if (_res_pos.angular_position.v[1] > M_PI)
        _res_pos.angular_position.v[1] = -M_PI;
    else if (_res_pos.angular_position.v[1] < -M_PI)
        _res_pos.angular_position.v[1] = M_PI;
    _res_pos.angular_position.v[0] += (monitor_h/2.0 - ypos) / sence;
    if (_res_pos.angular_position.v[0] > M_PI_2)
        _res_pos.angular_position.v[0] = M_PI_2;
    else if (_res_pos.angular_position.v[0] < -M_PI_2)
        _res_pos.angular_position.v[0] = -M_PI_2;
}

void Camera::set_keymap(int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_W && action == GLFW_PRESS)
        _res_pos.acceleration = _res_cam.normal.orterisation() / 5;
    if(key == GLFW_KEY_S && action == GLFW_PRESS)
        _res_pos.acceleration = - _res_cam.normal.orterisation() / 5;

    if(key == GLFW_KEY_A && action == GLFW_PRESS)
        _res_pos.acceleration = _res_cam.tangent.orterisation() / 5;
    if(key == GLFW_KEY_D && action == GLFW_PRESS)
        _res_pos.acceleration = - _res_cam.tangent.orterisation() / 5;
}

void Camera::set_res_cam(mtx4 buf_mtx)
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
