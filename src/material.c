/**
 *  src/material.c
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
#include <GL/glut.h>

#define _MATERIALS
#include "material.h"

material_t *materials[MAX_MATERIALS];
static material_id material_counter = 0;

material_id oxygarum_create_material(const char *name, color_t color) {
  material_id id = material_counter++;
  materials[id] = malloc(sizeof(material_t));
  
  materials[id]->id = id;
  materials[id]->name = name;
  materials[id]->color = color;
  
  return id;
}
