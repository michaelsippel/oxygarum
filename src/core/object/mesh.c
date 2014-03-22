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
#include <stdio.h>
#include <stdlib.h>

#include "object.h"
#include "mesh.h"

mesh3d_t *oxygarum_create_mesh3d(vertex_id num_vertices, vertex3d_t *vertices, face_id num_faces, face_t **faces, material_t *material) {
  mesh3d_t *mesh = malloc(sizeof(mesh3d_t));
  
  mesh->face_counter = num_faces;
  mesh->vertex_counter = num_vertices;
  mesh->faces = faces;
  mesh->vertices = vertices;
  mesh->material = material;
  
  mesh->normals = calloc(num_vertices, sizeof(vector3d_t));
  oxygarum_calc_normals(mesh);
  
  mesh->instance = NULL;
  
  return mesh;
}

mesh2d_t *oxygarum_create_mesh2d(vertex_id num_vertices, vertex2d_t *vertices, face_id num_faces, face_t **faces, material_t *material) {
  mesh2d_t *mesh = malloc(sizeof(mesh2d_t));
  
  mesh->face_counter = num_faces;
  mesh->vertex_counter = num_vertices;
  mesh->faces = faces;
  mesh->vertices = vertices;
  mesh->material = material;
  
  return mesh;
}

void oxygarum_create_render_instance(mesh3d_t *mesh) {
  render_instance_t *instance = malloc(sizeof(render_instance_t));  
  mesh->instance = instance;  
  
  instance->tex_id = NULL;
  instance->indices = NULL;
  instance->vertices = NULL;
  instance->normals = NULL;  
  instance->tex_choords = NULL;
  
  oxygarum_update_render_instance(mesh);
}

void oxygarum_update_render_instance(mesh3d_t *mesh) {
  int i,j,l,m;
  
  render_instance_t *instance = mesh->instance;  
  
  // indices
  instance->index_counter = 0;
  instance->vertex_counter = 0;
  for(i = 0; i < mesh->material->textures->size; i++) {
    instance->index_counter += mesh->faces[i]->vertex_counter - 2;
    instance->vertex_counter += mesh->faces[i]->vertex_counter;
  }
  instance->index_counter *= 3;
  
  instance->indices  = realloc(instance->indices,  instance->index_counter  * sizeof(unsigned int));
  instance->vertices = realloc(instance->vertices, instance->vertex_counter * sizeof(vertex3d_t));
  instance->normals  = realloc(instance->normals,  instance->vertex_counter * sizeof(vector3d_t));
  instance->tex_id   = realloc(instance->tex_id, mesh->material->textures->size * sizeof(unsigned int));
  
  instance->tex_choords = realloc(instance->tex_choords, sizeof(uv_t*));
  for(i = 0; i < mesh->material->textures->size; i++) {
    instance->tex_choords[i] = calloc(sizeof(uv_t), instance->vertex_counter);
  }
  
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
      for(m = 0; m < mesh->material->textures->size; m++) {
        instance->tex_choords[m][cur_vertex].u = face->uv_map[m][j].u;
        instance->tex_choords[m][cur_vertex].v = face->uv_map[m][j].v;
      }
      cur_vertex++;
    }
  }
  
  glGenBuffers(1, &instance->vertex_id);
  glBindBuffer(GL_ARRAY_BUFFER, instance->vertex_id);
  glBufferData(GL_ARRAY_BUFFER, instance->vertex_counter*sizeof(vertex3d_t), instance->vertices, GL_STATIC_DRAW);
  
  glGenBuffers(1, &instance->normal_id);
  glBindBuffer(GL_ARRAY_BUFFER, instance->normal_id);
  glBufferData(GL_ARRAY_BUFFER, instance->vertex_counter*sizeof(vector3d_t), instance->normals, GL_STATIC_DRAW);
  
  glGenBuffers(1, &instance->index_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, instance->index_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, instance->index_counter*sizeof(unsigned int), instance->indices, GL_STATIC_DRAW);
  
  for(i = 0; i < mesh->material->textures->size; i++) {
    glGenBuffers(1, &instance->tex_id[i]);
    glBindBuffer(GL_ARRAY_BUFFER, instance->tex_id[i]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uv_t) * instance->vertex_counter, instance->tex_choords[i], GL_STATIC_DRAW);
  }
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

