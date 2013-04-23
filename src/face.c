/**
 *  src/face.c
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
#include <string.h>
#include <GL/glut.h>

#include "vertex.h"
#include "face.h"
#include "object.h"

face_t *oxygarum_create_face(unsigned int num, vertex_id *vertices, material_t *material, uv_t *uv_map) {
  face_t *face = malloc(sizeof(face_t));
  
  face->vertex_counter = num;
  face->vertices = vertices;
  face->material = material;
  face->uv_map = uv_map;
  
  printf("Calcultating Normals...\n");
  oxygarum_calc_normals(face);
  
  return face;
}

void oxygarum_calc_normals(face_t *face) {
  int i;
  vector_t **vectors = calloc(face->vertex_counter, sizeof(vector_t));
  vector_t *product;
  for(i = 0; i < face->vertex_counter-1; i++) {
    vectors[i] = oxygarum_create_vector(&vertices[face->vertices[0]], &vertices[face->vertices[i+1]]);
  }
  
  product = oxygarum_vector_multiply_cross(vectors[0], vectors[1]);
  for(i = 0; i < face->vertex_counter-1; i++) {
    product = oxygarum_vector_multiply_cross(product, vectors[i]);
    oxygarum_normalize_vector(product);
  }
  face->normal = product;
}

void oxygarum_display_face(face_t *face) {
  int i;
  glColor4f(face->material->color.color[0], 
	    face->material->color.color[1],
	    face->material->color.color[2],
	    0.5);
  glBindTexture(GL_TEXTURE_2D, face->material->texture->id);
  glBegin(GL_POLYGON);
  for(i = 0; i < face->vertex_counter; i++) {
    glNormal3f(face->normal->x, face->normal->y, face->normal->z);
    glTexCoord2f(face->uv_map[i].u, face->uv_map[i].v);
    glVertex3f(
 	vertices[face->vertices[i]].x + object_offset.x,
 	vertices[face->vertices[i]].y + object_offset.y,
 	vertices[face->vertices[i]].z + object_offset.z
    );
  }
  glEnd();
}

