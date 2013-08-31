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
  object->vbo_indices = NULL;
  object->vbo_vertices = NULL;
  object->vbo_normals = NULL;
  object->vbo_tex_id = NULL;
  object->tex = NULL;
  
  oxygarum_update_object3d_buffer(object);
  
  glGenBuffers(1, &object->vbo_vertex_id);
  glBindBuffer(GL_ARRAY_BUFFER, object->vbo_vertex_id);
  glBufferData(GL_ARRAY_BUFFER, object->vbo_vertex_counter*sizeof(vertex3d_t), object->vbo_vertices, GL_STATIC_DRAW);
  
  glGenBuffers(1, &object->vbo_normal_id);
  glBindBuffer(GL_ARRAY_BUFFER, object->vbo_normal_id);
  glBufferData(GL_ARRAY_BUFFER, object->vbo_vertex_counter*sizeof(vector3d_t), object->vbo_normals, GL_STATIC_DRAW);
  
  glGenBuffers(1, &object->vbo_index_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->vbo_index_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, object->vbo_index_counter*sizeof(unsigned int), object->vbo_indices, GL_STATIC_DRAW);
  
  int i;
  for(i = 0; i < object->material->texture_counter; i++) {
    glGenBuffers(1, &object->vbo_tex_id[i]);
    glBindBuffer(GL_ARRAY_BUFFER, object->vbo_tex_id[i]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uv_t) * object->vbo_vertex_counter, object->tex[i], GL_STATIC_DRAW);
  }
  
  return object;
}

void oxygarum_update_object3d_buffer(object3d_t *object) {
  int i,j,k1,k2,l,m;
  
  // indices
  object->vbo_index_counter = 0;
  object->vbo_vertex_counter = 0;
  for(i = 0; i < object->face_counter; i++) {
    object->vbo_index_counter += object->faces[i]->vertex_counter - 2;
    object->vbo_vertex_counter += object->faces[i]->vertex_counter;
  }
  object->vbo_index_counter *= 3;
  
  if(object->vbo_indices == NULL) {
    object->vbo_indices = malloc(sizeof(unsigned int) * object->vbo_index_counter);
  } else {
    object->vbo_indices = realloc(object->vbo_indices, sizeof(unsigned int) * object->vbo_index_counter);
  }
  
  // vertices & normals
  if(object->vbo_vertices == NULL) {
    object->vbo_vertices = malloc(object->vbo_vertex_counter * sizeof(vertex3d_t));
  } else {
    object->vbo_vertices = realloc(object->vbo_vertices, object->vbo_vertex_counter * sizeof(vertex3d_t));
  }
  
  if(object->vbo_normals == NULL) {
    object->vbo_normals = malloc(object->vbo_vertex_counter * sizeof(vector3d_t));
  } else {
    object->vbo_normals = realloc(object->vbo_normals, object->vbo_vertex_counter * sizeof(vector3d_t));
  }
  
  // texture coords
  if(object->vbo_tex_id == NULL) {
    object->vbo_tex_id = malloc(object->material->texture_counter * sizeof(unsigned int*));
  } else {
    object->vbo_tex_id = realloc(object->vbo_tex_id, object->material->texture_counter * sizeof(unsigned int*));
  }
  
  if(object->tex == NULL) {
    object->tex = malloc(object->material->texture_counter * sizeof(uv_t*));
    for(i = 0; i < object->material->texture_counter; i++) {
      object->tex[i] = malloc(sizeof(uv_t) * object->vbo_vertex_counter);
    }
  } else {
    object->tex = realloc(object->tex, object->material->texture_counter * sizeof(uv_t*));
    for(i = 0; i < object->material->texture_counter; i++) {
      object->tex[i] = realloc(object->tex[i], sizeof(uv_t) * object->vbo_vertex_counter);
    }
  }
  
  k1 = 0;
  k2 = 0;
  for(i = 0; i < object->face_counter; i++) {
    face_t *face = object->faces[i];
    for(j = 0; j < face->vertex_counter-2; j++) {
      for(l = 0; l < j+3; l++) {
        object->vbo_indices[k1] = k2+l;
        
        k1++;
        if(l == 0) l = j;
      }
    }
    
    for(j = 0; j < face->vertex_counter; j++) {
      object->vbo_vertices[k2].x = object->vertices[face->vertices[j]].x;
      object->vbo_vertices[k2].y = object->vertices[face->vertices[j]].y;
      object->vbo_vertices[k2].z = object->vertices[face->vertices[j]].z;
      object->vbo_normals[k2].x = object->normals[face->vertices[j]].x;
      object->vbo_normals[k2].y = object->normals[face->vertices[j]].y;
      object->vbo_normals[k2].z = object->normals[face->vertices[j]].z;
      for(m = 0; m < object->material->texture_counter; m++) {
        object->tex[m][k2].u = face->uv_map[m][j].u;
        object->tex[m][k2].v = face->uv_map[m][j].v;
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

