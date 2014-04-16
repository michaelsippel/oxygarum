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
#include "shader.h"

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
  group_t *textures;
  
  color_t color;
  float roughness;
  float emission;
  float refractivity;
  
  GLfloat gl_ambient[4];
  GLfloat gl_diffuse[4];
  GLfloat gl_specular[4];
  GLfloat gl_emission[4];
  GLfloat gl_shininess[1];
  
  GLuint shade_program;
  group_t *shader_inputs;
} material_t;

material_t *oxygarum_create_material(void);
void oxygarum_update_material_values(material_t *material);
void oxygarum_use_material(material_t *material);

#endif

