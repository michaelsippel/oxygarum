/**
 *  src/object.c
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
#include <stdlib.h>

#include "vertex.h"
#include "face.h"
#include "object.h"

object_t *oxygarum_create_object(vertex_id num_vertices, vertex_t **vertices, face_id num_faces, face_t **faces) {
  object_t *object = malloc(sizeof(object_t));
  
  object->face_counter = num_faces;
  object->vertex_counter = num_vertices;
  object->faces = faces;
  object->vertices = vertices;
  
  object->normals = calloc(num_vertices, sizeof(vector_t*));  
  
  int i;
  for( i = 0; i < num_vertices; i++) {
    object->normals[i] = malloc(sizeof(vector_t));
  }
  
  printf("Calculating normals...\n");
  oxygarum_calc_normals(object);
  
  return object;
}

void oxygarum_calc_normals(object_t *object) {
  int i, j;
  face_t *face;
  
  int *common_face_count = calloc(object->vertex_counter, sizeof(int));
  
  for(i = 0; i < object->face_counter; i++) {
    face = object->faces[i];    
    
    vector_t *edge1 = oxygarum_create_vector(object->vertices[face->vertices[0]], object->vertices[face->vertices[1]]);
    vector_t *edge2 = oxygarum_create_vector(object->vertices[face->vertices[0]], object->vertices[face->vertices[2]]);
    
    vector_t *normal = oxygarum_vector_multiply_cross(edge1, edge2);
    oxygarum_normalize_vector(normal);
    
    free(edge1);
    free(edge2);    
    
    face->face_normal.x = normal->x;
    face->face_normal.y = normal->y;
    face->face_normal.z = normal->z;
    printf("flat: x = %lf, y = %lf, z = %lf\n", face->face_normal.x, face->face_normal.y, face->face_normal.z);    
    
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
    printf("%d: X = %lf, Y = %lf, Z = %lf\n", i, object->normals[i]->x, object->normals[i]->y, object->normals[i]->z);
  }

  free(common_face_count);
}

void oxygarum_display_object(object_t *object) {
  int i;
  for(i = 0; i < object->face_counter; i++) {
    oxygarum_display_face(object, object->faces[i]);
  }
}

