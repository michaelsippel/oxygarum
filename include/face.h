/**
 *  include/face.h
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
#ifndef _FACE_H
#define _FACE_H

#include "vertex.h"
#include "vector.h"
#include "material.h"

typedef struct face {
  vertex_id vertex_counter;
  vertex_id *vertices;
  vector3d_t face_normal;
  uv_t *uv_map;
  material_t *material;
} face_t;

typedef unsigned int face_id;

#ifndef _OBJECT_H
#include "object.h"

/// allocates memory and adds vertices to the face
face_t *oxygarum_create_face(unsigned int num, vertex_id *vertices, material_t *material, uv_t *uv_map);
/// Draw the face to the OpenGL scene
void oxygarum_display_face3d(object3d_t *object, face_t *face, int shade_mode);

#endif
#endif
