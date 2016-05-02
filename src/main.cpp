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

#include <iostream>
using namespace std;

float width;
float height;

bool run = true;
bool lock_cursor = false;
GLFWwindow *window;



vector <Model*>models;
Camera *_camera;

void loading()
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    models.clear();
    _camera->set_default_position(true);

     Model *_model;
    _model = new Model((char*)"res/load_sprite_inside");
    _model->_res_pos.position.init(0, 1.8, 0);
        _model->_res_pos.angular_acceleration.init(0.0, 0.001, 0.0);
    _model->init_camera(_camera);
    init_buffers(&_model->_res_mod);
    models.push_back(_model);


    _model = new Model((char*)"res/load_sprite_outside");
    _model->_res_pos.position.init(0, 2, 0);
    _model->init_camera(_camera);
    init_buffers(&_model->_res_mod);
    models.push_back(_model);

    _model = new Model((char*)"res/load_sprite_inside");
    _model->_res_pos.position.init(0, 4.8, 0);
     _model->_res_pos.angular_acceleration.init(0.0, 0.001, 0.0);
    _model->init_camera(_camera);
    init_buffers(&_model->_res_mod);
    models.push_back(_model);


    _model = new Model((char*)"res/load_sprite_outside");
    _model->_res_pos.position.init(0, 5, 0);
    _model->init_camera(_camera);
    init_buffers(&_model->_res_mod);
    models.push_back(_model);

    _model = new Model((char*)"res/map_test");
    _model->_res_pos.position.init(0, -15, 0);
    _model->init_camera(_camera);
    init_buffers(&_model->_res_mod);
    models.push_back(_model);

    _model = new Model((char*)"res/box_red");
    _model->_res_pos.position.init(-2, -7.8, 4);
     _model->_res_pos.angular_acceleration.init(0.0, 0.00001, 0.0);
    _model->init_camera(_camera);
    init_buffers(&_model->_res_mod);
    models.push_back(_model);

    _model = new Model((char*)"res/box_red");
    _model->_res_pos.position.init(-2, -8.8, 0);
    _model->init_camera(_camera);
    init_buffers(&_model->_res_mod);
    models.push_back(_model);
}

void unlock_camera()
{
    sleep(2);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(window, width/2, height/2);
    lock_cursor = true;
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
    _camera->set_keymap(key, scancode, action, mods);
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		run = false;
		cout << "exit" << endl;
	}
}

void CursorPosCal(GLFWwindow *window, double xpos, double ypos)
{
    _camera->set_mouse(xpos, ypos);
    if (lock_cursor)
        glfwSetCursorPos(window, width/2, height/2);
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

    loading();
    thread thr(unlock_camera);
    thr.detach();

    glEnable(GL_DOUBLEBUFFER);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
//    glEnable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);

    glfwSetKeyCallback(window, KeyCall);
    glfwSetCursorPosCallback(window, CursorPosCal);

    while(run)
        display();
    return 0;
}
