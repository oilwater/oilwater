/*
 * physic.cpp
 *
 *  Created on: May 8, 2016
 *      Author: rainautumn
 */
#include "physic.h"

#include <vector>
#include <thread>
#include <iostream>

using namespace std;

void thread_typical_calc(vector <SModel*>*models)
{
    for(;;)
    {
        for(int i = 0; i<models->size() ; i++)
        {
            models->at(i)->position.velocity += models->at(i)->position.acceleration;
            models->at(i)->position.position += models->at(i)->position.velocity;
            models->at(i)->position.angular_velocity += models->at(i)->position.angular_acceleration;
            models->at(i)->position.angular_position += models->at(i)->position.angular_velocity;
        }
        usleep(10000);
    }
}

Physic::Physic()
{

}


void Physic::init_kernel(Kernel *kernel)
{
    _kernel = kernel;
}

void Physic::start_physic()
{
    thread typical_calc(thread_typical_calc, &_kernel->models);
    typical_calc.detach();
}

