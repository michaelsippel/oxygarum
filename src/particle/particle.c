/**
 *  src/particle/particle.c
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
#include <GL/gl.h>
#include <stdlib.h>
#include <string.h>
#include "particle.h"

static GLuint particle_program;
extern char *particle_vertexshader;
extern char *particle_geometryshader;

particle_emitter_t *oxygarum_create_emitter(void) {
  particle_emitter_t *emitter = malloc(sizeof(particle_emitter_t));
  memset(emitter, 0, sizeof(particle_emitter_t));
  
  return emitter;
}

void oxygarum_init_particle_shader(void) {
  GLuint vertexshader = oxygarum_create_shader(GL_VERTEX_SHADER, particle_vertexshader, strlen(particle_vertexshader));
  GLuint geometryshader = oxygarum_create_shader(GL_GEOMETRY_SHADER, particle_geometryshader, strlen(particle_geometryshader));
  
  particle_program = glCreateProgram();
  glAttachShader(particle_program, vertexshader);
  glAttachShader(particle_program, geometryshader);
  glLinkProgram(particle_program);
}

void oxygarum_render_particle_system(particle_emitter_t *emitter) {
  
}

void oxygarum_update_particle_system(particle_emitter_t *emitter, float frametime) {
  glUseProgram(particle_program);
  
  glUseProgram(0);
}

