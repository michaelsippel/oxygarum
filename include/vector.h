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

typedef vertex_t vector_t;
typedef unsigned int normal_id;

vector_t *oxygarum_create_vector(vertex_t *o, vertex_t *p);
vector_t *oxygarum_normalize_vector(vector_t *vector);

double oxygarum_vector_multiply_scalar(vector_t *v1, vector_t *v2);
vector_t *oxygarum_vector_multiply_cross(vector_t *v1, vector_t *v2);

#endif

