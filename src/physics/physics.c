/**
 *  src/physics/physics.c
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
#include <string.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include "physics.h"
#include "scene.h"
#include "vertex.h"
#include "vector.h"

physics_t *oxygarum_create_physics(void) {
  physics_t *physics = malloc(sizeof(physics_t));
  
  physics->force_fields = oxygarum_create_group();
  
  GLuint vertexshader = oxygarum_create_shader(GL_VERTEX_SHADER, softbodyshader, strlen(softbodyshader));
  physics->vertex_program = glCreateProgram();
  glAttachShader(physics->vertex_program, vertexshader);
  glLinkProgram(physics->vertex_program);
  
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

void oxygarum_update_physics(struct scene *scene, float frametime) {
  if(scene->physics == NULL) {
    return;
  }
  
  physics_t *physics = scene->physics;
  
  group_entry_t *entry = scene->objects3d->head;
  while(entry != NULL) {
    object3d_t *obj = (object3d_t*) entry->element;
    if(obj == NULL) continue;
    if(obj->physics_properties == NULL) continue;    
    
    // calculate acceleration
    oxygarum_calc_acceleration(physics, obj->physics_properties, frametime);
    
    // if object is softbody, calculate each vertex
    if(obj->physics_properties->softness > 0) {
      oxygarum_calc_softbody(physics, obj->physics_properties, frametime);
    }
    
    // move object
    obj->pos.x += obj->physics_properties->pos_velocity.x;
    obj->pos.y += obj->physics_properties->pos_velocity.y;
    obj->pos.z += obj->physics_properties->pos_velocity.z;
    
    obj->rot.x += obj->physics_properties->rot_velocity.x;
    obj->rot.y += obj->physics_properties->rot_velocity.y;
    obj->rot.z += obj->physics_properties->rot_velocity.z;

    entry = entry->next;
  }
}

