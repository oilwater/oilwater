/*
 * position.h
 *
 *  Created on: Apr 1, 2015
 *      Author: rainautumn
 */
#ifndef POSITION_H
#define POSITION_H

#include "glmath.hpp"

struct res_pos
{
    vtx3 position;
    vtx3 velocity;
    vtx3 acceleration;

    vtx3 angular_position;
    vtx3 angular_velocity;
    vtx3 angular_acceleration;
};

class Position
{
public:
    res_pos _res_pos;
    mtx4 get_position_matrix();
    mtx4 get_position_matrix_sprite();
};

#endif // POSITION_H
