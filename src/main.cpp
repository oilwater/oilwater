/*
 * main.cpp
 *
 *  Created on: Mar 30, 2015
 *      Author: rainautumn
 */

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <unistd.h>

#include <thread>

#include "model.h"
#include "initbuff.hpp"
#include "camera.h"
#include "terminal.h"
#include "network.h"
#include "kernel.h"
#include "physic.h"

#include <iostream>

using namespace std;

float width;
float height;

bool fscr;

bool run = true;
bool cashing_process = true;

GLFWwindow *window;

vector <Model*>models;


Camera *_camera;
Terminal *_terminal;
Network * _network;
Kernel *_kernel;
Physic *_physic;

int local_fpc = 0;
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

void tread_loading()
{
    models.clear();
    Model *_model;

    _kernel->get_cashing_models_names((char*)"res/list");
    for(int k = 0; k < _kernel->others.size() - 1; k++)
    {
        _model = new Model((char *)_kernel->others.at(k).c_str());
        _model->init_camera(_camera);
        models.push_back(_model);
    }
    _camera->_res_pos.position.init(0,-5,-5);
    cashing_process = false;
}

void thread_fpc()
{
    sleep(5);
    local_fpc = 0;
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

    local_fpc++;
    for(int x = 0; x <  _kernel->models.size(); x++)
    {
        models[_kernel->models[x]->mesh_number]->_res_pos = _kernel->models[x]->position;
        models[_kernel->models[x]->mesh_number]->render();
    }

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

void thread_logo_render()
{
    set_camera_type(LOCK_LOOK);
    _camera->_res_pos.position.init(0,0,0);

    Model *logo_static = new Model((char *)"res/sprites/load_sprite_outside");
    logo_static->init_camera(_camera);
    init_buffers(&logo_static->_res_mod);
    logo_static->_res_pos.position.init(0, 0, -0.1);
    logo_static->_res_pos.angular_position.init(M_PI_2,0,M_PI);
    Model *logo_rotate = new Model((char *)"res/sprites/load_sprite_inside");
    logo_rotate->init_camera(_camera);
    init_buffers(&logo_rotate->_res_mod);
    logo_rotate->_res_pos.angular_position.init(M_PI_2,0,M_PI);

    while (cashing_process)
    {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        logo_static->render();
        logo_rotate->render();
        logo_rotate->_res_pos.angular_position.v[1]+=0.1;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    set_camera_type(FREE_LOOK);
}

void thread_render()
{
    glfwInit();
    glfwWindowHint(GLFW_SAMPLES, 0);
    if(!fscr)
        window = glfwCreateWindow(width, height, "oilwater", NULL, NULL);
    else
        window = glfwCreateWindow(width, height, "oilwater", glfwGetPrimaryMonitor(), NULL);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwShowWindow(window);

    glewInit();

    _terminal = new Terminal(_kernel);


    _kernel->get_network(_network);

    glEnable(GL_DOUBLEBUFFER);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    const GLfloat par0_1[] = {0.2, 0.2, 0.2, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, par0_1);
    const GLfloat par0_2[] = {14.5, 8.0, -14.5};
    glLightfv(GL_LIGHT0, GL_POSITION, par0_2);
    const GLfloat par0_3[] = {0.0, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, par0_3);

    const GLfloat par1_1[] = {0.4, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, par1_1);
    const GLfloat par1_2[] = {-14.5, 8.0, -14.5};
    glLightfv(GL_LIGHT1, GL_POSITION, par1_2);
    const GLfloat par1_3[] = {0.0, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT1, GL_AMBIENT, par1_3);

    const GLfloat par2_1[] = {0.0, 0.5, 0.0, 1.0};
    glLightfv(GL_LIGHT2, GL_DIFFUSE, par2_1);
    const GLfloat par2_2[] = {14.5, 8.0, 14.5};
    glLightfv(GL_LIGHT2, GL_POSITION, par2_2);
    const GLfloat par2_3[] = {0.0, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT2, GL_AMBIENT, par2_3);

    const GLfloat par3_1[] = {0.0, 0.0, 0.5, 1.0};
    glLightfv(GL_LIGHT3, GL_DIFFUSE, par3_1);
    const GLfloat par3_2[] = {-14.5, 8.0, 14.5};
    glLightfv(GL_LIGHT3, GL_POSITION, par3_2);
    const GLfloat par3_3[] = {0.0, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT3, GL_AMBIENT, par3_3);


    glfwSetKeyCallback(window, KeyCall);
    glfwSetCursorPosCallback(window, CursorPosCal);


    thread loading(tread_loading);
    loading.detach();

    thread_logo_render();

    for(int k = 0; k < models.size() - 1; k++)
    {
        init_buffers(&models.at(k)->_res_mod);
    }



    while(run)
        display();
    exit(0);
}

int main(int argc, char** argv)
{
    _kernel = new Kernel(argc, argv);
    _kernel->load_map();

    _physic = new Physic();
    _physic->init_kernel(_kernel);

    width = _kernel->width;
    height = _kernel->height;

    fscr = _kernel->fullscreen;
    _camera = new Camera();
    _camera->set_monitor(height, width);

    _network = new Network();
    _network->init_camera(_camera);

    thread fpc(thread_fpc);
    fpc.detach();

    _physic->start_physic();
    thread_render();
}
