/**
 *  src/object/mesh.c
 *
 *  (C) Copyright 2013 Michael Sippel
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

/**
 * @author Michael Sippel <michamimosa@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object.h"
#include "mesh.h"

mesh3d_t *oxygarum_create_mesh3d(vertex_id num_vertices, vertex3d_t *vertices, uv_id num_texcoords, uv_t *texcoords, face_id num_faces, face_t **faces, material_t *material) {
  mesh3d_t *mesh = malloc(sizeof(mesh3d_t));
  
  mesh->face_counter = num_faces;
  mesh->vertex_counter = num_vertices;
  mesh->faces = faces;
  mesh->vertices = vertices;
  mesh->texcoords = texcoords;  
  mesh->default_material = material;

  mesh->normals = calloc(num_vertices, sizeof(vector3d_t));
  oxygarum_calc_normals(mesh);
  
  mesh->instance = NULL;
  
  return mesh;
}

mesh2d_t *oxygarum_create_mesh2d(vertex_id num_vertices, vertex2d_t *vertices, uv_id num_texcoords, uv_t *texcoords, face_id num_faces, face_t **faces, material_t *material) {
  mesh2d_t *mesh = malloc(sizeof(mesh2d_t));
  
  mesh->face_counter = num_faces;
  mesh->vertex_counter = num_vertices;
  mesh->texcoord_counter = num_texcoords;
  mesh->faces = faces;
  mesh->vertices = vertices;
  mesh->texcoords = texcoords;
  mesh->material = material;
  
  return mesh;
}

void oxygarum_update_render_instance(mesh3d_t *mesh) {
  int i,j,l;
  
  render_instance_t *instance = mesh->instance;  
  
  // indices
  instance->index_counter = 0;
  instance->vertex_counter = 0;
  for(i = 0; i < mesh->face_counter; i++) {
    instance->index_counter += mesh->faces[i]->vertex_counter - 2;
    instance->vertex_counter += mesh->faces[i]->vertex_counter;
  }
  instance->index_counter *= 3;
  
  instance->indices  = realloc(instance->indices,  instance->index_counter  * sizeof(unsigned int));
  instance->vertices = realloc(instance->vertices, instance->vertex_counter * sizeof(vertex3d_t));
  instance->normals  = realloc(instance->normals,  instance->vertex_counter * sizeof(vector3d_t));
  instance->texcoords=realloc(instance->texcoords, instance->vertex_counter * sizeof(uv_t));
  
  int cur_index = 0;
  int cur_vertex = 0;
  for(i = 0; i < mesh->face_counter; i++) {
    face_t *face = mesh->faces[i];
    for(j = 0; j < face->vertex_counter-2; j++) {
      for(l = 0; l < j+3; l++) {
        instance->indices[cur_index] = cur_vertex + l;

        cur_index++;
        if(l == 0) l = j;
      }
    }
    
    for(j = 0; j < face->vertex_counter; j++) {
      instance->vertices[cur_vertex].x = mesh->vertices[face->vertices[j]].x;
      instance->vertices[cur_vertex].y = mesh->vertices[face->vertices[j]].y;
      instance->vertices[cur_vertex].z = mesh->vertices[face->vertices[j]].z;
      instance->normals [cur_vertex].x = mesh->normals [face->vertices[j]].x;
      instance->normals [cur_vertex].y = mesh->normals [face->vertices[j]].y;
      instance->normals [cur_vertex].z = mesh->normals [face->vertices[j]].z;
      instance->texcoords[cur_vertex].u = mesh->texcoords[face->uv_map[j]].u;
      instance->texcoords[cur_vertex].v = mesh->texcoords[face->uv_map[j]].v;
      
      cur_vertex++;
    }
  }
  
  glGenBuffers(1, &instance->vertex_id);
  glBindBuffer(GL_ARRAY_BUFFER, instance->vertex_id);
  glBufferData(GL_ARRAY_BUFFER, instance->vertex_counter*sizeof(vertex3d_t), instance->vertices, GL_STATIC_DRAW);
  
  glGenBuffers(1, &instance->normal_id);
  glBindBuffer(GL_ARRAY_BUFFER, instance->normal_id);
  glBufferData(GL_ARRAY_BUFFER, instance->vertex_counter*sizeof(vector3d_t), instance->normals, GL_STATIC_DRAW);
  
  glGenBuffers(1, &instance->texcoord_id);
  glBindBuffer(GL_ARRAY_BUFFER, instance->texcoord_id);
  glBufferData(GL_ARRAY_BUFFER, instance->vertex_counter * sizeof(uv_t), instance->texcoords, GL_STATIC_DRAW);
  
  glGenBuffers(1, &instance->index_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, instance->index_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, instance->index_counter*sizeof(unsigned int), instance->indices, GL_STATIC_DRAW);
}

void oxygarum_calc_normals(mesh3d_t *mesh) {
  int i, j;
  face_t *face;
  
  int *common_face_count = calloc(mesh->vertex_counter, sizeof(int));
  
  for(i = 0; i < mesh->face_counter; i++) {
    face = mesh->faces[i];    
    
    vector3d_t *edge1 = oxygarum_create_vector3d(&mesh->vertices[face->vertices[0]], &mesh->vertices[face->vertices[1]]);
    vector3d_t *edge2 = oxygarum_create_vector3d(&mesh->vertices[face->vertices[1]], &mesh->vertices[face->vertices[2]]);
    
    vector3d_t *normal = oxygarum_vector3d_multiply_cross(edge1, edge2);
    oxygarum_normalize_vector3d(normal);
    
    free(edge1);
    free(edge2);
    
    face->face_normal.x = normal->x;
    face->face_normal.y = normal->y;
    face->face_normal.z = normal->z;
    
    for(j = 0; j < face->vertex_counter; j++) {
      mesh->normals[face->vertices[j]].x += normal->x;
      mesh->normals[face->vertices[j]].y += normal->y;
      mesh->normals[face->vertices[j]].z += normal->z;
      
      common_face_count[face->vertices[j]]++;
    }
  }
  
  for(i = 0; i < mesh->vertex_counter; i++) {
    if(common_face_count[i]) {
      mesh->normals[i].x /= common_face_count[i];
      mesh->normals[i].y /= common_face_count[i];
      mesh->normals[i].z /= common_face_count[i];
    }
  }

  free(common_face_count);
}

void oxygarum_render_face3d(mesh3d_t *mesh, material_t *material, face_t *face) {
  int i;
  
  if(face->vertex_counter == 3)
    glBegin(GL_TRIANGLES);
  else if(face->vertex_counter == 4)
    glBegin(GL_QUADS);
  else
    glBegin(GL_POLYGON);
  
  for(i = 0; i < face->vertex_counter; i++) {
    vertex_id id = face->vertices[i];
    
    if(mesh->texcoords != NULL && face->uv_map != NULL) {
      int j;
      for(j = 0; j < material->textures->size; j++) {
        glMultiTexCoord2f(GL_TEXTURE0 + j, mesh->texcoords[face->uv_map[i]].u, mesh->texcoords[face->uv_map[i]].v);
      }
    }

    if(mesh->normals != NULL)
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

