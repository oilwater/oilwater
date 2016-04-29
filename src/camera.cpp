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
    _res_pos.position.drop();
    _res_pos.angular_position.drop();
    _res_pos.position.init(0, -2, -10);
}

void Camera::set_perspective(bool value)
{
	perspective = value;
}

void Camera::set_default_position(bool value)
{
	default_position = value;
}

mtx4 Camera::get_matrix()
{
    mtx4 buf_position;
	mtx4 buf_angular;
	if(default_position)
	{
		buf_position.init();
		buf_angular.init();
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
    if(perspective)
    	buf_perspective.perspective(1,1,1,150);
    else
    	buf_perspective.init();
    set_res_cam(buf_angular);

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
        _res_pos.acceleration = _res_cam.normal.orterisation();
    if(key == GLFW_KEY_S && action == GLFW_PRESS)
        _res_pos.acceleration = - _res_cam.normal.orterisation();

    if(key == GLFW_KEY_A && action == GLFW_PRESS)
        _res_pos.acceleration = _res_cam.tangent.orterisation();
    if(key == GLFW_KEY_D && action == GLFW_PRESS)
        _res_pos.acceleration = - _res_cam.tangent.orterisation();
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
