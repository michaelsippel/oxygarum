/**
 *  src/physics/physics.h
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
#include <stdlib.h>
#include "physics.h"
#include "scene.h"
#include "vertex.h"
#include "vector.h"

physics_t *oxygarum_create_physics(void) {
  physics_t *physics = malloc(sizeof(physics_t));
  
  physics->force_field_counter = 0;
  physics->force_fields = NULL;
  
  return physics;
}

force_field_t *oxygarum_create_force_field(void) {
  force_field_t *force_field = malloc(sizeof(force_field_t));
  
  force_field->force.x = 0;
  force_field->force.y = 0;
  force_field->force.z = 0;
  force_field->velocity = 1;
  force_field->type = FORCE_FIELD_TYPE_VECTOR;
  
  return force_field;
}

physics_properties_t *oxygarum_create_physics_properties(void) {
  physics_properties_t *properties = malloc(sizeof(physics_properties_t));
  memset(properties, 0, sizeof(physics_properties_t));

  return properties;
}

int oxygarum_add_force_field(physics_t *physics, force_field_t *force_field) {
  int id = physics->force_field_counter++;
  physics->force_fields = realloc(physics->force_fields, physics->force_field_counter * sizeof(force_field_t*));
  
  physics->force_fields[id] = force_field;
  
  return id;
}

void oxygarum_remove_force_field(physics_t *physics, int id) {
  physics->force_fields[id] = NULL;
}

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

void oxygarum_update_physics(struct scene *scene, float frametime) {
  if(scene->physics == NULL) {
    return;
  }
  
  physics_t *physics = scene->physics;

  int i;
  for(i = 0; i < scene->object3d_counter; i++) {
    object3d_t *obj = scene->objects3d[i];
    if(obj == NULL) continue;
    if(obj->physics_properties == NULL) continue;    

    oxygarum_calc_acceleration(physics, obj->physics_properties, frametime);

    // move object
    obj->pos.x += obj->physics_properties->pos_velocity.x;
    obj->pos.y += obj->physics_properties->pos_velocity.y;
    obj->pos.z += obj->physics_properties->pos_velocity.z;

    obj->rot.x += obj->physics_properties->rot_velocity.x;
    obj->rot.y += obj->physics_properties->rot_velocity.y;
    obj->rot.z += obj->physics_properties->rot_velocity.z;
  }
}

