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
#include "mesh.h"

#define OBJECT_VISIBLE         0x1
#define OBJECT_TRANSPARENT     0x2
#define OBJECT_DEPTH_BUFFERING 0x4
#define OBJECT_RENDER_VBO      0x8

typedef struct object3d {
  mesh3d_t *mesh;
  vertex3d_t pos;
  vertex3d_t rot;
  vertex2d_t feedback;
  
  GLuint shade_program;
  GLuint shade_model;
  int status;
} object3d_t;

typedef struct object2d {
  mesh2d_t *mesh;
  vertex2d_t pos;
  float rot;
  vertex2d_t feedback;
  int status;
} object2d_t;

object3d_t *oxygarum_create_object3d(void);
object2d_t *oxygarum_create_object2d(void);

void oxygarum_render_object3d(object3d_t *object);
void oxygarum_render_object2d(object2d_t *object);

#endif

