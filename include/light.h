/**
 *  include/light.h
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
#ifndef _LIGHT_H
#define _LIGHT_H

#include <GL/gl.h>
#include "vertex.h"

#define LIGHT_POSITION_ABSOLUTE 0x0
#define LIGHT_POSITION_RELATIVE 0x1

typedef struct light {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat pos[4];
  GLenum gl_light;
} light_t;

int oxygarum_add_light(light_t *light, int light_position);
void oxygarum_remove_light(int id);

#endif

