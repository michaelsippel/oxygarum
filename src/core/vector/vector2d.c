/**
 *  src/core/vector/vector2d.c
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
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "vector.h"

vector2d_t *oxygarum_create_vector2d(vertex2d_t *o, vertex2d_t *p) {
  vector2d_t *vector = malloc(sizeof(vector2d_t));
  
  vector->x = o->x - p->x;
  vector->y = o->y - p->y;
  
  return oxygarum_normalize_vector2d(vector);
}

vector2d_t *oxygarum_normalize_vector2d(vector2d_t *vector) {
  float len = sqrt(
    vector->x * vector->x + 
    vector->y * vector->y
  );
  
  vector->x /= len;
  vector->y /= len;
  
  return vector;
}

float oxygarum_vector2d_multiply_scalar(vector2d_t *v1, vector2d_t *v2) {
  return (v1->x * v2->x + 
          v1->y * v2->y);
}

vector2d_t *oxygarum_vector2d_multiply_cross(vector2d_t *v1, vector2d_t *v2) {
  vector2d_t *vector = malloc(sizeof(vector2d_t));
  
  vector->x = (v1->y * v2->x) - (v1->x * v2->y);
  vector->y = (v1->x * v2->y) - (v1->y * v2->x);
  
  return vector;
}

