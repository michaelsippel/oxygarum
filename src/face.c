/**
 *  src/face.c
 *
 *  (C) Copyright 2012 Michael Sippel
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

face_t *cliter_create_face(unsigned int num, vertex_id *vertices) {
  face_t *face = malloc(sizeof(face_t));
  
  face->vertex_counter = num;
  face->vertices = vertices;
  
  return face;
}

void cliter_display_face(face_t *face) {
  int i;
  glBegin(GL_POLYGON);
  for(i = 0; i < face->vertex_counter; i++) {
    glVertex3f(
 	vertices[i].x,
 	vertices[i].y,
 	vertices[i].z
    );
  }
  glEnd();
}
