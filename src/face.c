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
#include <GL/glut.h>
#include "vertex.h"
#include "face.h"

face_t *oxygarum_create_face(unsigned int num, vertex_id *vertices, material_t *material, uv_t *uv_map) {
  face_t *face = malloc(sizeof(face_t));
  
  face->vertex_counter = num;
  face->vertices = vertices;
  face->material = material;
  face->uv_map = uv_map;  
  
  return face;
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
    glTexCoord2f(face->uv_map[i].u, face->uv_map[i].v);
    glVertex3f(
 	vertices[face->vertices[i]].x,
 	vertices[face->vertices[i]].y,
 	vertices[face->vertices[i]].z
    );
  }
  glEnd();
}

