/**
 *  src/vector.c
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

vector_t *oxygarum_create_vector(vertex_t *o, vertex_t *p) {
  vector_t *vector = malloc(sizeof(vector_t));

  vector->x = o->x - p->x;
  vector->y = o->y - p->y;
  vector->z = o->z - p->z;
  
  return oxygarum_normalize_vector(vector);
}

vector_t *oxygarum_normalize_vector(vector_t *vector) {
  double len = sqrt(
    vector->x * vector->x + 
    vector->y * vector->y + 
    vector->z * vector->z
  );
  
  vector->x /= len;
  vector->y /= len;
  vector->z /= len;
  
  return vector;
}

double oxygarum_vector_multiply_scalar(vector_t *v1, vector_t *v2) {
  return (v1->x * v2->x + 
          v1->y * v2->y + 
          v1->z * v2->z);
}

vector_t *oxygarum_vector_multiply_cross(vector_t *v1, vector_t *v2) {
  vector_t *vector = malloc(sizeof(vector_t));
  
  vector->x = (v1->y * v2->z) - (v1->z * v2->y);
  vector->y = (v1->z * v2->x) - (v1->x * v2->z);
  vector->z = (v1->x * v2->y) - (v1->y * v2->x);
  
  return vector;
}


