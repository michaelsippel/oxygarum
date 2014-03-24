/**
 *  src/texture.h
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
#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <stdint.h>
#include <GL/gl.h>

#include "group.h"

typedef unsigned int texture_id;
typedef unsigned int uv_id;

typedef struct uv_t {
  float u;
  float v;
} uv_t;

typedef struct texture_parameter {
  GLenum type;
  GLenum value;
} texture_parameter_t;

typedef struct texture {
  unsigned int width;
  unsigned int height;

  GLenum format;
  uint32_t bpp;  

  uint8_t *data;
  texture_id id;
} texture_t;

texture_t *oxygarum_load_texture_from_file(const char *path, group_t *params);
void oxygarum_load_texture(texture_t *tex, group_t *params);

#endif

