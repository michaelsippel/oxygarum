/**
 *  include/object.h
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
#ifndef _OBJECT_H
#define _OBJECT_H

#include "vertex.h"
#include "face.h"
#include "material.h"

#define OBJECT_VISIBLE         0x1
#define OBJECT_TRANSPARENT     0x2
#define OBJECT_DEPTH_BUFFERING 0x4

typedef struct vbo_vertex {
  uv_t       tex;
  vector3d_t normal;
  vertex3d_t vertex;
} vbo_vertex_t;

typedef struct object3d {
  face_id face_counter;
  vertex_id vertex_counter;
  face_t **faces;
  vertex3d_t **vertices;
  vector3d_t **normals;
  material_t *material;
  
  unsigned int vbo_id;
  unsigned int vbo_vertex_counter;
  vbo_vertex_t *vbo;
} object3d_t;

typedef struct object2d {
  face_id face_counter;
  vertex_id vertex_counter;
  face_t **faces;
  vertex2d_t **vertices;
  material_t *material;
} object2d_t;

typedef struct display_obj3d {
  object3d_t *object;
  vertex3d_t pos;
  vertex3d_t rot;
  vertex2d_t feedback;
  int shade_mode;
  int status;
} display_obj3d_t;

typedef struct display_obj2d {
  object2d_t *object;
  vertex2d_t pos;
  float rot;
  vertex2d_t feedback;
  int status;
} display_obj2d_t;

/// allocates memory and adds faces to the object
object3d_t *oxygarum_create_object3d(vertex_id num_vertices, vertex3d_t **vertices, face_id num_faces, face_t **faces, material_t *material);
object2d_t *oxygarum_create_object2d(vertex_id num_vertices, vertex2d_t **vertices, face_id num_faces, face_t **faces, material_t *material);
void oxygarum_calc_normals(object3d_t *object);
/// draw the object to the OpenGL scene
void oxygarum_display_object3d(object3d_t *object, int shade_mode);
int oxygarum_add_object3d(object3d_t *object, float x, float y, float  z);
void oxygarum_set_shade_mode(int id, int mode);
void oxygarum_enable_object3d_status(int id, int status);
void oxygarum_disable_object3d_status(int id, int status);
vertex2d_t oxygarum_get_object3d_feedback(int id);

void oxygarum_display_object2d(object2d_t *object);
int oxygarum_add_object2d(object2d_t *object, float x, float y);
void oxygarum_enable_object2d_status(int id, int status);
void oxygarum_disable_object2d_status(int id, int status);
vertex2d_t oxygarum_get_object2d_feedback(int id);

/// move and rotate objects
void oxygarum_translate_object3d_to(int id, float new_x, float new_y, float new_z);
void oxygarum_rotate_object3d_to(int id, float new_x, float new_y, float new_z);
void oxygarum_translate_object3d(int id, float x_off, float y_off, float z_off);
void oxygarum_rotate_object3d(int id, float x_off, float y_off, float z_off);

void oxygarum_translate_object2d_to(int id, float new_x, float new_y);
void oxygarum_rotate_object2d_to(int id, float new_r);
void oxygarum_translate_object2d(int id, float x_off, float y_off);
void oxygarum_rotate_object2d(int id, float off);

/// move and rotate the camera
void oxygarum_translate_camera_to(float new_x, float new_y, float new_z);
void oxygarum_rotate_camera_to(float new_x, float new_y, float new_z);
void oxygarum_translate_camera(float x_off, float y_off, float z_off);
void oxygarum_rotate_camera(float x_off, float y_off, float z_off);

#endif

