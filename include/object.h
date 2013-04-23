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

typedef struct object {
  face_id face_counter;
  face_t **faces;
} object_t;

typedef struct display_obj {
  object_t *object;
  vertex_t pos;
  vertex_t rot;
} display_obj_t;

#ifndef _OBJECT_OFFSET
#define _OBJECT_OFFSET
extern vertex_t object_offset;
#endif

/// allocates memory and adds faces to the object
object_t *oxygarum_create_object(unsigned int num, face_t **faces);
/// draw the object to the OpenGL scene
void oxygarum_display_object(object_t *object);
int oxygarum_add_object(object_t *object, double x, double y, double  z);

/// move and rotate objects
void oxygarum_move_object_to(int id, double new_x, double new_y, double new_z);
void oxygarum_rotate_object_to(int id, double new_x, double new_y, double new_z);

/// move and rotate the camera
void oxygarum_translate_camera_to(double new_x, double new_y, double new_z);
void oxygarum_rotate_camera_to(double new_x, double new_y, double new_z);

#endif

