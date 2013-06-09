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
#include "opengl.h"
#include "object.h"

face_t *oxygarum_create_face(unsigned int num, vertex_id *vertices, material_t *material, uv_t *uv_map) {
  face_t *face = malloc(sizeof(face_t));
  
  face->vertex_counter = num;
  face->vertices = vertices;
  face->material = material;
  face->uv_map = uv_map;
  
  return face;
}

void oxygarum_display_face3d(object3d_t *object, face_t *face, int shade_mode) {
  int i;
  
  glColor4f(face->material->color.color[0], 
	    face->material->color.color[1],
	    face->material->color.color[2],
	    face->material->color.color[3]);
  glBindTexture(GL_TEXTURE_2D, face->material->texture->id);
  glMaterialfv(GL_FRONT, GL_AMBIENT, face->material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, face->material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, face->material->specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, face->material->shininess);
  
  if(shade_mode == SHADE_FLAT)
  glNormal3f(face->face_normal.x, face->face_normal.y, face->face_normal.z);  
  
  if(face->vertex_counter == 3)
    glBegin(GL_TRIANGLES);
  else if(face->vertex_counter == 4)
    glBegin(GL_QUADS);
  else
    glBegin(GL_POLYGON);
  
  for(i = 0; i < face->vertex_counter; i++) {
    vertex_id id = face->vertices[i];
    
    glTexCoord2f(face->uv_map[i].u, face->uv_map[i].v);
    if(shade_mode == SHADE_SMOOTH)
    glNormal3f(object->normals[id]->x, object->normals[id]->y, object->normals[id]->z);
    glVertex3f(
 	object->vertices[id]->x,
 	object->vertices[id]->y,
 	object->vertices[id]->z
    );
  }
  glEnd();
}

void oxygarum_display_face2d(object2d_t *object, face_t *face) {
  int i;
  
  glColor4f(face->material->color.color[0], 
	    face->material->color.color[1],
	    face->material->color.color[2],
	    face->material->color.color[3]);
  glBindTexture(GL_TEXTURE_2D, face->material->texture->id);
  
  if(face->vertex_counter == 3)
    glBegin(GL_TRIANGLES);
  else if(face->vertex_counter == 4)
    glBegin(GL_QUADS);
  else
    glBegin(GL_POLYGON);
  
  for(i = 0; i < face->vertex_counter; i++) {
    vertex_id id = face->vertices[i];
    
    glTexCoord2f(face->uv_map[i].u, face->uv_map[i].v);
    glVertex2f(
 	object->vertices[id]->x,
 	object->vertices[id]->y
    );
  }
  
  glEnd();
}

