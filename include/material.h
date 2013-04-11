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

#include "texture.h"

typedef unsigned int material_id;

typedef struct color_st {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} color_st_t;

typedef union color {
  color_st_t rgb;
  unsigned char color[3];
} color_t;

typedef struct material {
  const char *name;
  material_id id;
  color_t color;
  texture_t *texture;
} material_t;

material_t *oxygarum_create_material(const char *name);
void oxygarum_set_texture(material_id material, texture_t *texture);
void oxygarum_set_color(material_id material, color_t color);

#endif

