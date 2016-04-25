/*
 * position.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: rainautumn
 */
#include "position.h"

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
    return buf_position;
}
