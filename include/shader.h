/**
 *  include/shader.h
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
#ifndef _SHADER_H
#define _SHADER_H

#include <GL/gl.h>

#include "group.h"

#define INT1 0x0
#define INT2 0x1
#define INT3 0x2
#define INT4 0x3
#define FLOAT1 0x4
#define FLOAT2 0x5
#define FLOAT3 0x6
#define FLOAT4 0x7

typedef struct shader_input {
  GLint location;
  int type;
  void *pointer;
} shader_input_t;

GLuint oxygarum_create_shader(GLuint type, char *text, int len);
GLuint oxygarum_create_shader_from_file(GLuint type, const char *shader_path);

void oxygarum_use_shader(GLuint program, group_t *inputs);

#endif

