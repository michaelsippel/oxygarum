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

object3d_t *oxygarum_create_object3d(vertex_id num_vertices, vertex3d_t **vertices, face_id num_faces, face_t **faces, material_t *material) {
  object3d_t *object = malloc(sizeof(object3d_t));
  
  object->face_counter = num_faces;
  object->vertex_counter = num_vertices;
  object->faces = faces;
  object->vertices = vertices;
  object->material = material;
  
  object->normals = calloc(num_vertices, sizeof(vector3d_t*));  
  
  int i;
  for( i = 0; i < num_vertices; i++) {
    object->normals[i] = malloc(sizeof(vector3d_t));
  }
  
  oxygarum_calc_normals(object);
  
  // creating VBO
  glGenBuffers(1, &object->vbo_id);
  glBindBuffer(GL_ARRAY_BUFFER, object->vbo_id);
  
  object->vbo = malloc(sizeof(vbo_vertex_t) * object->vbo_vertex_counter);//(vbo_vertex_t*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
  oxygarum_update_object3d_buffer(object);
  //glUnmapBuffer(GL_ARRAY_BUFFER);
  
  return object;
}

void oxygarum_update_object3d_buffer(object3d_t *object) {
  int i,j,k = 0,l=0;
  
  object->vbo_vertex_counter = 0;
  for(i = 0; i < object->face_counter; i++) {
    object->vbo_vertex_counter += object->faces[i]->vertex_counter - 2;
  }
  object->vbo_vertex_counter *= 3;

  object->vbo = realloc(object->vbo, sizeof(vbo_vertex_t) * object->vbo_vertex_counter);  
  for(i = 0; i < object->face_counter; i++) {
    face_t *face = object->faces[i];
    for(j = 0; j < face->vertex_counter-2; j++) {
      
      for(l = 0; l < j+3; l++) {
        object->vbo[k].vertex.x = object->vertices[face->vertices[l]]->x;
        object->vbo[k].vertex.y = object->vertices[face->vertices[l]]->y;
        object->vbo[k].vertex.z = object->vertices[face->vertices[l]]->z;
        object->vbo[k].normal.x = object->normals[face->vertices[l]]->x;
        object->vbo[k].normal.y = object->normals[face->vertices[l]]->y;
        object->vbo[k].normal.z = object->normals[face->vertices[l]]->z;
        object->vbo[k].tex.u = face->uv_map[l].u;
        object->vbo[k].tex.v = face->uv_map[l].v;
        
        k++;
        if(l == 0) l = j;
      }
    }
  }
  glBufferData(GL_ARRAY_BUFFER, object->vbo_vertex_counter*sizeof(vbo_vertex_t), object->vbo, GL_STATIC_DRAW);
}

void oxygarum_calc_normals(object3d_t *object) {
  int i, j;
  face_t *face;
  
  int *common_face_count = calloc(object->vertex_counter, sizeof(int));
  
  for(i = 0; i < object->face_counter; i++) {
    face = object->faces[i];    
    
    vector3d_t *edge1 = oxygarum_create_vector3d(object->vertices[face->vertices[0]], object->vertices[face->vertices[1]]);
    vector3d_t *edge2 = oxygarum_create_vector3d(object->vertices[face->vertices[1]], object->vertices[face->vertices[2]]);
    
    vector3d_t *normal = oxygarum_vector3d_multiply_cross(edge1, edge2);
    oxygarum_normalize_vector3d(normal);
    
    free(edge1);
    free(edge2);
    
    face->face_normal.x = normal->x;
    face->face_normal.y = normal->y;
    face->face_normal.z = normal->z;
    
    for(j = 0; j < face->vertex_counter; j++) {
      object->normals[face->vertices[j]]->x += normal->x;
      object->normals[face->vertices[j]]->y += normal->y;
      object->normals[face->vertices[j]]->z += normal->z;
      
      common_face_count[face->vertices[j]]++;
    }
  }
  
  for(i = 0; i < object->vertex_counter; i++) {
    if(common_face_count[i]) {
      object->normals[i]->x /= common_face_count[i];
      object->normals[i]->y /= common_face_count[i];
      object->normals[i]->z /= common_face_count[i];
    }
  }

  free(common_face_count);
}

object2d_t *oxygarum_create_object2d(vertex_id num_vertices, vertex2d_t **vertices, face_id num_faces, face_t **faces, material_t *material) {
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

