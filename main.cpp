/*
 * main.cpp
 *
 *  Created on: Mar 30, 2015
 *      Author: rainautumn
 */

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <unistd.h>

#include <QCoreApplication>
#include <thread>

#include "model.h"
#include "initbuff.hpp"
#include "camera.h"
#include "terminal.h"
#include "network.h"
#include "kernel.h"

#include <iostream>

using namespace std;

float width;
float height;

bool run = true;

GLFWwindow *window;

vector <Model*>models;


Camera *_camera;
Terminal *_terminal;
Network * _network;
Kernel *_kernel;

unsigned int local_fpc = 0;

void set_camera_type(char type)
{
    _camera->cam_type = type;
    switch (_camera->cam_type) {
    case LOCK_LOOK:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        _camera->lock_position = true;
        break;
    case FREE_LOOK:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPos(window, width/2, height/2);
        _camera->lock_position = false;
        break;
    case TERMINAL_LOOK:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        break;
    default:
        break;
    }
}

void loading()
{
    models.clear();
    Model *_model;

    _model = new Model((char*)"res/load_sprite_inside");
    _model->type = MODEL_SPRITE_HP;
    _model->init_camera(_camera);
    _model->_res_pos.angular_position.init(M_PI_2,0,0);
    _model->_res_pos.position.init(0,0,-2);
    _model->_res_pos.angular_acceleration.init(0,0.3,0);
    init_buffers(&_model->_res_mod);
    models.push_back(_model);

    _model = new Model((char*)"res/load_sprite_outside");
    _model->type = MODEL_SPRITE_HP;
    _model->init_camera(_camera);
    _model->_res_pos.angular_position.init(M_PI_2,0,0);
    _model->_res_pos.position.init(0,0,-2.2);
    init_buffers(&_model->_res_mod);
    models.push_back(_model);
}

void fpc_void()
{
    while(true)
    {
        sleep(1);
        if(local_fpc > _kernel->fpc_info.fpc_max)
            _kernel->fpc_info.fpc_max = local_fpc;
        if(local_fpc < _kernel->fpc_info.fpc_min)
            _kernel->fpc_info.fpc_min = local_fpc;
        _kernel->fpc_info.fpc = local_fpc;
        local_fpc = 0;
    }
}

void display()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _network->packet();

    local_fpc++;

    if (models[0]->_res_pos.angular_velocity.v[1] > 0.1)
        models[0]->_res_pos.angular_acceleration.v[1] = -0.3;
    else
        models[0]->_res_pos.angular_acceleration.v[1] = 0.0003;

    for(int x = models.size() - 1; x >= 0; x--)
        models[x]->render();
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void KeyCall(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS)
    {
        if(_camera->cam_type != TERMINAL_LOOK)
                set_camera_type(TERMINAL_LOOK);

        else
        {
            if(_camera->lock_position)
                    set_camera_type(LOCK_LOOK);
            else
                    set_camera_type(FREE_LOOK);
        }
    }

    switch (_camera->cam_type) {
    case FREE_LOOK:
        _camera->set_keymap(key, scancode, action, mods);
        break;
    case TERMINAL_LOOK:
        _terminal->set_keymap(key, scancode, action, mods);
        break;
    default:
        break;
    }
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		run = false;
		cout << "exit" << endl;
	}
}

void CursorPosCal(GLFWwindow *window, double xpos, double ypos)
{
    switch (_camera->cam_type) {
    case FREE_LOOK:
         _camera->set_mouse(xpos, ypos);
         glfwSetCursorPos(window, width/2, height/2);
        break;
    case TERMINAL_LOOK:

        break;
    default:
        break;
    }
}

int main(int argc, char** argv)
{
    QCoreApplication a(argc, argv);

    _kernel = new Kernel(argc, argv);

    thread fpc(fpc_void);
    fpc.detach();

    width = _kernel->width;
    height = _kernel->height;

    glfwInit();
    window = glfwCreateWindow(width, height, "oilwater", NULL, NULL);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    glfwShowWindow(window);

    glewInit();

    _camera = new Camera();
    _camera->set_monitor(height, width);

    _terminal = new Terminal(_kernel);

    loading();
    _network = new Network();
    _network->init_camera(_camera);

    glEnable(GL_DOUBLEBUFFER);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

    set_camera_type(FREE_LOOK);

    glfwSetKeyCallback(window, KeyCall);
    glfwSetCursorPosCallback(window, CursorPosCal);

    while(run)
        display();
    return 0;
}
