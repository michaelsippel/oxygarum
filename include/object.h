/**
 *  include/object.h
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
#ifndef _OBJECT_H
#define _OBJECT_H

#include "vertex.h"
#include "face.h"

#define OBJECT_VISIBLE   0x0
#define OBJECT_INVISIBLE 0x1

typedef struct object {
  face_id face_counter;
  vertex_id vertex_counter;
  face_t **faces;
  vertex_t **vertices;
  vector_t **normals;
} object_t;

typedef struct display_obj {
  object_t *object;
  vertex_t pos;
  vertex_t rot;
  int shade_mode;
  int status;
} display_obj_t;

/// allocates memory and adds faces to the object
object_t *oxygarum_create_object(vertex_id num_vertices, vertex_t **vertices, face_id num_faces, face_t **faces);
void oxygarum_calc_normals(object_t *object);
/// draw the object to the OpenGL scene
void oxygarum_display_object(object_t *object, int shade_mode);
int oxygarum_add_object(object_t *object, float x, float y, float  z);
void oxygarum_set_shade_mode(int id, int mode);
void oxygarum_set_object_status(int id, int status);

/// move and rotate objects
void oxygarum_move_object_to(int id, float new_x, float new_y, float new_z);
void oxygarum_rotate_object_to(int id, float new_x, float new_y, float new_z);
void oxygarum_translate_object(int id, float x_off, float y_off, float z_off);
void oxygarum_rotate_object(int id, float x_off, float y_off, float z_off);

/// move and rotate the camera
void oxygarum_translate_camera_to(float new_x, float new_y, float new_z);
void oxygarum_rotate_camera_to(float new_x, float new_y, float new_z);
void oxygarum_translate_camera(float x_off, float y_off, float z_off);
void oxygarum_rotate_camera(float x_off, float y_off, float z_off);

#endif

