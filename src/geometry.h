/*
 * geometry.h
 *
 *  Created on: Apr 12, 2015
 *      Author: rainautumn
 */

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "glmath.hpp"

struct res_gem
{
    vtx3 hwl;
    vtx2 hw()
    {
        vtx2 buf;
        buf.init(hwl.v[0], hwl.v[1]);
    }
};

class Geometry
{
public:
    res_gem _res_gem;
};

#endif // GEOMETRY_H
