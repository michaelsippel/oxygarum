/**
 *  src/core/material/material.c
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
#include <stdlib.h>

#include "material.h"

material_t *oxygarum_create_material(void) {
  material_t *material = malloc(sizeof(material_t));
  material->color.rgb = (color_st_t) {.r=1,.g=1,.b=1,.a=1};
  material->textures = oxygarum_create_group();
  
  memcpy(&material->ambient,  (GLfloat[]){ 0.2f, 0.2f, 0.2f, 0.0f }, sizeof(material->ambient));
  memcpy(&material->diffuse,  (GLfloat[]){ 1.0f, 1.0f, 1.0f, 0.0f }, sizeof(material->diffuse));
  memcpy(&material->specular, (GLfloat[]){ 0.5f, 0.5f, 0.5f, 0.0f }, sizeof(material->specular));
  memcpy(&material->shininess,(GLfloat[]){ 1.0f },                   sizeof(material->shininess));
  
  return material;
}

