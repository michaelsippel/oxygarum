/**
 *  src/object/object.c
 *
 *  (C) Copyright 2012-2013 Michael Sippel
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
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include "vertex.h"
#include "face.h"
#include "object.h"

object3d_t *oxygarum_create_object3d(vertex_id num_vertices, vertex3d_t *vertices, face_id num_faces, face_t **faces, material_t *material) {
  object3d_t *object = malloc(sizeof(object3d_t));
  
  object->face_counter = num_faces;
  object->vertex_counter = num_vertices;
  object->faces = faces;
  object->vertices = vertices;
  object->material = material;
  
  object->normals = calloc(num_vertices, sizeof(vector3d_t));
  oxygarum_calc_normals(object);
  
  // creating VBO
  render_instance_t *instance = malloc(sizeof(render_instance_t));  
  object->instance = instance;  
  
  instance->tex_id = NULL;
  instance->indices = NULL;
  instance->vertices = NULL;
  instance->normals = NULL;  
  instance->tex = calloc(instance->tex, object->material->texture_counter * sizeof(uv_t*));
  
  oxygarum_update_render_instance(object);
  
  glGenBuffers(1, &instance->vertex_id);
  glBindBuffer(GL_ARRAY_BUFFER, instance->vertex_id);
  glBufferData(GL_ARRAY_BUFFER, instance->vertex_counter*sizeof(vertex3d_t), instance->vertices, GL_STATIC_DRAW);
  
  glGenBuffers(1, &instance->normal_id);
  glBindBuffer(GL_ARRAY_BUFFER, instance->normal_id);
  glBufferData(GL_ARRAY_BUFFER, instance->vertex_counter*sizeof(vector3d_t), instance->normals, GL_STATIC_DRAW);
  
  glGenBuffers(1, &instance->index_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, instance->index_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, instance->index_counter*sizeof(unsigned int), instance->indices, GL_STATIC_DRAW);
  
  int i;
  for(i = 0; i < object->material->texture_counter; i++) {
    glGenBuffers(1, &instance->tex_id[i]);
    glBindBuffer(GL_ARRAY_BUFFER, instance->tex_id[i]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uv_t) * instance->vertex_counter, instance->tex[i], GL_STATIC_DRAW);
  }
  
  return object;
}

void oxygarum_update_render_instance(object3d_t *object) {
  int i,j,k1,k2,l,m;
  
  render_instance_t *instance = object->instance;  
  
  // indices
  instance->index_counter = 0;
  instance->vertex_counter = 0;
  for(i = 0; i < object->face_counter; i++) {
    instance->index_counter += object->faces[i]->vertex_counter - 2;
    instance->vertex_counter += object->faces[i]->vertex_counter;
  }
  instance->index_counter *= 3;
  
  instance->indices  = realloc(instance->indices,  instance->index_counter  * sizeof(unsigned int));
  instance->vertices = realloc(instance->vertices, instance->vertex_counter * sizeof(vertex3d_t));
  instance->normals  = realloc(instance->normals,  instance->vertex_counter * sizeof(vector3d_t));
  instance->tex_id   = realloc(instance->tex_id, object->material->texture_counter * sizeof(unsigned int*));
  
  instance->tex = realloc(instance->tex, object->material->texture_counter * sizeof(uv_t*));
  for(i = 0; i < object->material->texture_counter; i++) {
    instance->tex[i] = realloc(instance->tex[i], sizeof(uv_t) * instance->vertex_counter);
  }
  
  k1 = 0;
  k2 = 0;
  for(i = 0; i < object->face_counter; i++) {
    face_t *face = object->faces[i];
    for(j = 0; j < face->vertex_counter-2; j++) {
      for(l = 0; l < j+3; l++) {
        instance->indices[k1] = k2+l;
        
        k1++;
        if(l == 0) l = j;
      }
    }
    
    for(j = 0; j < face->vertex_counter; j++) {
      instance->vertices[k2].x = object->vertices[face->vertices[j]].x;
      instance->vertices[k2].y = object->vertices[face->vertices[j]].y;
      instance->vertices[k2].z = object->vertices[face->vertices[j]].z;
      instance->normals [k2].x = object->normals [face->vertices[j]].x;
      instance->normals [k2].y = object->normals [face->vertices[j]].y;
      instance->normals [k2].z = object->normals [face->vertices[j]].z;
      for(m = 0; m < object->material->texture_counter; m++) {
        instance->tex[0][k2].u = face->uv_map[0][j].u;
        instance->tex[0][k2].v = face->uv_map[0][j].v;
      }
      k2++;
    }
  }
}

void oxygarum_calc_normals(object3d_t *object) {
  int i, j;
  face_t *face;
  
  int *common_face_count = calloc(object->vertex_counter, sizeof(int));
  
  for(i = 0; i < object->face_counter; i++) {
    face = object->faces[i];    
    
    vector3d_t *edge1 = oxygarum_create_vector3d(&object->vertices[face->vertices[0]], &object->vertices[face->vertices[1]]);
    vector3d_t *edge2 = oxygarum_create_vector3d(&object->vertices[face->vertices[1]], &object->vertices[face->vertices[2]]);
    
    vector3d_t *normal = oxygarum_vector3d_multiply_cross(edge1, edge2);
    oxygarum_normalize_vector3d(normal);
    
    free(edge1);
    free(edge2);
    
    face->face_normal.x = normal->x;
    face->face_normal.y = normal->y;
    face->face_normal.z = normal->z;
    
    for(j = 0; j < face->vertex_counter; j++) {
      object->normals[face->vertices[j]].x += normal->x;
      object->normals[face->vertices[j]].y += normal->y;
      object->normals[face->vertices[j]].z += normal->z;
      
      common_face_count[face->vertices[j]]++;
    }
  }
  
  for(i = 0; i < object->vertex_counter; i++) {
    if(common_face_count[i]) {
      object->normals[i].x /= common_face_count[i];
      object->normals[i].y /= common_face_count[i];
      object->normals[i].z /= common_face_count[i];
    }
  }

  free(common_face_count);
}

object2d_t *oxygarum_create_object2d(vertex_id num_vertices, vertex2d_t *vertices, face_id num_faces, face_t **faces, material_t *material) {
  object2d_t *object = malloc(sizeof(object2d_t));
  
  object->face_counter = num_faces;
  object->vertex_counter = num_vertices;
  object->faces = faces;
  object->vertices = vertices;
  object->material = material;
  
  return object;
}

void oxygarum_display_object3d(object3d_t *object) {
  int i;
  for(i = 0; i < object->face_counter; i++) {
    oxygarum_display_face3d(object, object->faces[i]);
  }
}

void oxygarum_display_object2d(object2d_t *object) {
  int i;
  for(i = 0; i < object->face_counter; i++) {
    oxygarum_display_face2d(object, object->faces[i]);
  }
}

