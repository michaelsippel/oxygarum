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

typedef struct physics_properties {
  vector3d_t pos_velocity;
  vector3d_t rot_velocity;
  float softness;
} physics_properties_t;

physics_t *oxygarum_create_physics(void);
force_field_t *oxygarum_create_force_field(void);
physics_properties_t *oxygarum_create_physics_properties(void);
int oxygarum_add_force_field(physics_t *physics, force_field_t *force_field);
void oxygarum_remove_force_field(physics_t *physics, int id);

void oxygarum_calc_acceleration(physics_t *physics, physics_properties_t *properties, float anim_speed);
void oxygarum_update_physics(struct scene *scene, float frametime);

#endif

