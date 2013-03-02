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

face_t *oxygarum_create_face(unsigned int num, vertex_id *vertices, material_id material) {
  face_t face;
  
  face.vertex_counter = num;
  face.vertices = vertices;
  face.material = material;
  
  return &face;
}

void oxygarum_display_face(face_t *face) {
  int i;
//   glColor4f(materials[face.material].color.color[0], 
// 	    materials[face.material].color.color[1],
// 	    materials[face.material].color.color[2],
// 	    1);
//   glBegin(GL_POLYGON);
//   for(i = 0; i < face->vertex_counter; i++) {
//     glVertex3f(
//  	vertices[face->vertices[i]].x,
//  	vertices[face->vertices[i]].y,
//  	vertices[face->vertices[i]].z
//     );
//   }
//   glEnd();
}
