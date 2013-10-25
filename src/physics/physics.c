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

int oxygarum_add_force_field(physics_t *physics, force_field_t *force_field) {
  int id = physics->force_field_counter++;
  physics->force_fields = realloc(physics->force_fields, physics->force_field_counter * sizeof(force_field_t*));
  
  physics->force_fields[id] = force_field;
  
  return id;
}

void oxygarum_remove_force_field(physics_t *physics, int id) {
  physics->force_fields[id] = NULL;
}

void oxygarum_update_physics(scene_t *scene) {
  if(scene->physics == NULL) {
    return;
  }
  
  int i;
  
  physics_t *physics = scene->physics;
  for(i = 0; i < physics->force_field_counter; i++) {
    // TODO
  }
}

