/**
 *  include/material.h
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
#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <GL/gl.h>
#include "group.h"
#include "texture.h"

typedef struct color_st {
  float r;
  float g;
  float b;
  float a;
} color_st_t;

typedef union color {
  color_st_t rgb;
  float color[4];
} color_t;

typedef struct material {
  color_t color;
  group_t *textures;
  
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess[1];
} material_t;

material_t *oxygarum_create_material(void);

#endif

