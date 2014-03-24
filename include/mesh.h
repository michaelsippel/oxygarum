/**
 *  include/mesh.h
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
#ifndef _MESH_H
#define _MESH_H

#include "vertex.h"
#include "face.h"
#include "material.h"

typedef struct render_instance {
  unsigned int index_id;
  unsigned int vertex_id;
  unsigned int normal_id;
  unsigned int tex_id;
  
  unsigned int index_counter;
  unsigned int vertex_counter;
  unsigned int *indices;
  vertex3d_t *vertices;
  vector3d_t *normals;
  uv_t *texcoords;
} render_instance_t;

typedef struct mesh3d {
  vertex_id vertex_counter;
  vertex3d_t *vertices;
  vector3d_t *normals;
  
  uv_id texcoord_counter;
  uv_t *texcoords;
  
  face_id face_counter;
  face_t **faces;
  
  material_t *material;
  render_instance_t *instance;
} mesh3d_t;

typedef struct mesh2d {
  vertex_id vertex_counter;
  vertex2d_t *vertices;
  
  uv_id texcoord_counter;
  uv_t *texcoords;  
  
  face_t **faces;
  face_id face_counter;
  
  material_t *material;
} mesh2d_t;

mesh3d_t *oxygarum_create_mesh3d(vertex_id num_vertices, vertex3d_t *vertices, uv_id num_texcoords, uv_t *texcoords, face_id num_faces, face_t **faces, material_t *material);
mesh2d_t *oxygarum_create_mesh2d(vertex_id num_vertices, vertex2d_t *vertices, uv_id num_texcoords, uv_t *texcoords, face_id num_faces, face_t **faces, material_t *material);

void oxygarum_calc_normals(mesh3d_t *mesh);
void oxygarum_create_render_instance(mesh3d_t *mesh);
void oxygarum_update_render_instance(mesh3d_t *mesh);

#endif

