/*
 * physic.h
 *
 *  Created on: May 8, 2016
 *      Author: rainautumn
 */
#ifndef PHYSIC_H
#define PHYSIC_H

#include "kernel.h"

class Physic
{
public:
    Physic();
    void init_kernel(Kernel * kernel);
public:
    void loading();
    Kernel * _kernel;
};

#endif // PHYSIC_H
