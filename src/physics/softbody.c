/**
 *  src/physics/softbody.c
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
#include <GL/glew.h>
#include <GL/gl.h>

#include "physics.h"
#include "scene.h"
#include "vertex.h"
#include "vector.h"

char *softbodyshader = 
"void main() {\n"
"	gl_Position = gl_Vertex;\n"
"}\n";

void oxygarum_calc_softbody(physics_t *physics, physics_properties_t *properties, float anim_speed) {
  glUseProgram(physics->vertex_program);
  // TODO
}

