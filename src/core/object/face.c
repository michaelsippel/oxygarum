/**
 *  src/core/object/face.c
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

#include "vertex.h"
#include "face.h"
#include "object.h"

face_t *oxygarum_create_face(unsigned int num, vertex_id *vertices, uv_id *uv_map) {
  face_t *face = malloc(sizeof(face_t));
  
  face->vertex_counter = num;
  face->vertices = vertices;
  face->uv_map = uv_map;
  
  return face;
}

void oxygarum_render_face3d(mesh3d_t *mesh, face_t *face) {
  int i;
  
  if(face->vertex_counter == 3)
    glBegin(GL_TRIANGLES);
  else if(face->vertex_counter == 4)
    glBegin(GL_QUADS);
  else
    glBegin(GL_POLYGON);
  
  for(i = 0; i < face->vertex_counter; i++) {
    vertex_id id = face->vertices[i];
    
    int j;
    //for(j = 0; j < mesh->material->textures->size; j++) {
    //  glMultiTexCoord2f(GL_TEXTURE0 + j, mesh->texcoords[face->uv_map[id]].u, mesh->texcoords[face->uv_map[id]].v);
    //}
    glTexCoord2f(mesh->texcoords[face->uv_map[id]].u, mesh->texcoords[face->uv_map[id]].v);
    glNormal3f(mesh->normals[id].x, mesh->normals[id].y, mesh->normals[id].z);
    glVertex3f(
 	mesh->vertices[id].x,
 	mesh->vertices[id].y,
 	mesh->vertices[id].z
    );
  }
  glEnd();
}

void oxygarum_render_face2d(mesh2d_t *mesh, face_t *face) {
  int i;
  
  if(face->vertex_counter == 3)
    glBegin(GL_TRIANGLES);
  else if(face->vertex_counter == 4)
    glBegin(GL_QUADS);
  else
    glBegin(GL_POLYGON);
  
  for(i = 0; i < face->vertex_counter; i++) {
    vertex_id id = face->vertices[i];
    
    int j;
    for(j = 0; j < mesh->material->textures->size; j++) {
      glMultiTexCoord2f(GL_TEXTURE0 + j, mesh->texcoords[face->uv_map[j]].u, mesh->texcoords[face->uv_map[j]].v);
    }
    
    glVertex2f(
 	mesh->vertices[id].x,
 	mesh->vertices[id].y
    );
  }
  
  glEnd();
}

