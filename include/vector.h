/**
 *  include/vector.h
 *
 *  (C) Copyright 2013 Michael Sippel
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _VECTOR_H
#define _VECTOR_H

#include "vertex.h"

typedef vertex3d_t vector3d_t;
typedef vertex2d_t vector2d_t;
typedef unsigned int normal_id;

vector3d_t *oxygarum_create_vector3d(vertex3d_t *o, vertex3d_t *p);
vector3d_t *oxygarum_normalize_vector3d(vector3d_t *vector);
double oxygarum_vector3d_multiply_scalar(vector3d_t *v1, vector3d_t *v2);
vector3d_t *oxygarum_vector3d_multiply_cross(vector3d_t *v1, vector3d_t *v2);

vector2d_t *oxygarum_create_vector2d(vertex2d_t *o, vertex2d_t *p);
vector2d_t *oxygarum_normalize_vector2d(vector2d_t *vector);
double oxygarum_vector2d_multiply_scalar(vector2d_t *v1, vector2d_t *v2);
vector2d_t *oxygarum_vector2d_multiply_cross(vector2d_t *v1, vector2d_t *v2);

#endif

