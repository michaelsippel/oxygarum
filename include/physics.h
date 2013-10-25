/**
 *  include/physics.h
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
#ifndef _PHYSICS_H
#define _PHYSICS_H

#include "scene.h"
#include "vector.h"

#define PHYSICS_STATIC  0x0
#define PHYSICS_DYNAMIC 0x1

#define FORCE_FIELD_TYPE_VECTOR 0x0
#define FORCE_FIELD_TYPE_VERTEX 0x1

typedef struct force_field {
  vector3d_t force;
  float velocity;
  int type;
} force_field_t;

typedef struct physics {
  int force_field_counter;
  force_field_t **force_fields;
} physics_t;

physics_t *oxygarum_create_physics(void);
void oxygarum_update_physics(struct scene *scene);

#endif

