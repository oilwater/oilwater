/*
 * position.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: rainautumn
 */
#include "position.h"

Position::Position()
{
    _res_pos.acceleration.drop();
    _res_pos.angular_acceleration.drop();
    _res_pos.position.drop();
    _res_pos.angular_position.drop();
    _res_pos.angular_velocity.drop();
    _res_pos.velocity.drop();
}

mtx4 Position::get_position_matrix()
{
    mtx4 buf_position;
    buf_position.drop();
    buf_position.tranform_position(_res_pos.position);

    mtx4 buf_angle;
    buf_angle.drop();
    buf_angle.tranform_angle(_res_pos.angular_position);

    return buf_position * buf_angle;
}

mtx4 Position::get_position_matrix_sprite()
{
    mtx4 buf_position;
    buf_position.drop();
    buf_position.tranform_position(_res_pos.position);

    mtx4 buf_angle;
    buf_angle.drop();
    buf_angle.tranform_angle(_res_pos.angular_position);

    return buf_position * buf_angle ;
}

