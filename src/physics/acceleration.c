/**
 *  src/physics/acceleration.c
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
#include "physics.h"
#include "vector.h"

void oxygarum_calc_acceleration(physics_t *physics, physics_properties_t *properties, float anim_speed) {
  int i;

  for(i = 0; i < physics->force_field_counter; i++) {
    force_field_t *force_field = physics->force_fields[i];
    if(force_field == NULL) {
      continue;
    }
    
    switch(force_field->type) {
      case FORCE_FIELD_TYPE_VECTOR:
        properties->pos_velocity.x += force_field->force.x * force_field->velocity * anim_speed;
        properties->pos_velocity.y += force_field->force.y * force_field->velocity * anim_speed;
        properties->pos_velocity.z += force_field->force.z * force_field->velocity * anim_speed;
        break;
      case FORCE_FIELD_TYPE_VERTEX:
        //TODO
        break;
    }
  }
}



