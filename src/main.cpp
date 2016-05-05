/*
 * main.cpp
 *
 *  Created on: Mar 30, 2015
 *      Author: rainautumn
 */
#include <QCoreApplication>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <unistd.h>

#include "model.h"
#include "initbuff.hpp"
#include "camera.h"
#include "kernel.h"
#include "terminal.h"

#include <iostream>

using namespace std;

float width;
float height;

bool run = true;

GLFWwindow *window;

vector <Model*>models;
Camera *_camera;
Terminal *_terminal;


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
    _camera->set_default_position(true);

     Model *_model;
    _model = new Model((char*)"res/load_sprite_inside");
    _model->_res_pos.position.init(0, 0,- 2);
    _model->_res_pos.angular_position.init(M_PI_2, 0 ,0);
    _model->_res_pos.angular_acceleration.init(0.0, 0.001, 0.0);
    _model->init_camera(_camera);
    init_buffers(&_model->_res_mod);
    models.push_back(_model);


    _model = new Model((char*)"res/load_sprite_outside");
    _model->_res_pos.position.init(0, 0,- 2.1);
    _model->_res_pos.angular_position.init(M_PI_2, 0 ,0);
    _model->init_camera(_camera);
    init_buffers(&_model->_res_mod);
    models.push_back(_model);

    _model = new Model((char*)"res/map_test");
    _model->_res_pos.position.init(-20, -7, -30);
    _model->init_camera(_camera);
    init_buffers(&_model->_res_mod);
    models.push_back(_model);


}

void unlock_camera()
{
    sleep(1);
    set_camera_type(FREE_LOOK);
    glfwSetCursorPos(window, width/2, height/2);
    _camera->set_default_position(false);
}

void display()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
        {
                set_camera_type(TERMINAL_LOOK);
            cout << "console open" <<endl;
        }
        else
        {
            if(_camera->lock_position)
                    set_camera_type(LOCK_LOOK);
            else
                    set_camera_type(FREE_LOOK);
            cout << "console close" <<endl;
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
    Kernel *kernel = new Kernel(argc, argv);

    width = kernel->width;
    height = kernel->height;

    glfwInit();
    window = glfwCreateWindow(width, height, "oilwater", NULL, NULL);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwShowWindow(window);

    glewInit();

    _camera = new Camera();
    _camera->set_monitor(height, width);
    set_camera_type(LOCK_LOOK);

    _terminal = new Terminal(kernel);

    loading();
    thread thr(unlock_camera);
    thr.detach();

    glEnable(GL_DOUBLEBUFFER);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

    glfwSetKeyCallback(window, KeyCall);
    glfwSetCursorPosCallback(window, CursorPosCal);

    while(run)
        display();
    return 0;
}
