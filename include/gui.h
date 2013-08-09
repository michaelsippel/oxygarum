/**
 *  include/gui.h
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
#ifndef _GUI_H
#define _GUI_H

#include <material.h>
#include <face.h>
#include <object.h>

#define OXYGARUM_WINDOW_TOP_LEFT      0x0
#define OXYGARUM_WINDOW_TOP_CENTER    0x1
#define OXYGARUM_WINDOW_TOP_RIGHT     0x2
#define OXYGARUM_WINDOW_MIDDLE_LEFT   0x3
#define OXYGARUM_WINDOW_MIDDLE_CENTER 0x4
#define OXYGARUM_WINDOW_MIDDLE_RIGHT  0x5
#define OXYGARUM_WINDOW_BOTTOM_LEFT   0x6
#define OXYGARUM_WINDOW_BOTTOM_CENTER 0x7
#define OXYGARUM_WINDOW_BOTTOM_RIGHT  0x8

#define NUM_WINDOW_VERTICES 36
#define NUM_WINDOW_FACES    9

typedef struct oxygarum_window {
  vertex2d_t size;
  
  vertex2d_t *vertices[NUM_WINDOW_VERTICES];
  face_t *faces[NUM_WINDOW_FACES];
  material_t *material;
  object2d_t *obj;
} oxygarum_window_t;

oxygarum_window_t *oxygarum_create_window(float width, float height, texture_t *texture);
face_t *oxygarum_create_window_part(oxygarum_window_t *win, int part, uv_t *uv_map, float width, float height);
object2d_t *oxygarum_create_window_obj(oxygarum_window_t *win);

#endif

