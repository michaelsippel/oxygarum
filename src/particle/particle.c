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
#include <GL/glu.h>
#include <stdlib.h>
#include <string.h>
#include "particle.h"

static GLuint particle_program;
extern char *particle_vertexshader;
extern char *particle_geometryshader;

static int loc_anim_speed;
static int loc_seed;
static int loc_gvector;
static int loc_gvertex;
static int loc_gspeed;

particle_emitter_t *oxygarum_create_emitter(void *borders) {
  particle_emitter_t *emitter = malloc(sizeof(particle_emitter_t));
  memset(emitter, 0, sizeof(particle_emitter_t));
  time(&emitter->seed);
  
  emitter->particle_counter = 2;  
  
  glGenTransformFeedbacks(2, &emitter->transform_feedback);
  glGenBuffers(2, &emitter->particle_buffer);
  
  int i;
  for(i = 0; i < 2; i++) {
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, emitter->transform_feedback[i]);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, emitter->particle_buffer[i]);
    glBindBuffer(GL_ARRAY_BUFFER, emitter->particle_buffer[i]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particle_t)*2, borders, GL_DYNAMIC_DRAW);
  }
  
  return emitter;
}

void oxygarum_init_particle_shader(void) {
  GLuint vertexshader = oxygarum_create_shader(GL_VERTEX_SHADER, particle_vertexshader, strlen(particle_vertexshader));
  GLuint geometryshader = oxygarum_create_shader(GL_GEOMETRY_SHADER, particle_geometryshader, strlen(particle_geometryshader));
  
  particle_program = glCreateProgram();
  glAttachShader(particle_program, vertexshader);
  glAttachShader(particle_program, geometryshader);
  
  const GLchar* varyings[] = {"pos","vel","lifetime","size","color"};
  glTransformFeedbackVaryings(particle_program, 5, varyings, GL_SEPARATE_ATTRIBS);
  
  loc_anim_speed = glGetUniformLocation(particle_program, "anim_speed");
  loc_seed       = glGetUniformLocation(particle_program, "seed");
  loc_gvector    = glGetUniformLocation(particle_program, "gravity_vector");
  loc_gvertex    = glGetUniformLocation(particle_program, "gravity_vertex");
  loc_gspeed     = glGetUniformLocation(particle_program, "gravity_speed");
  glBindAttribLocation(particle_program, 0, "Pos");
  glBindAttribLocation(particle_program, 1, "Vel");
  glBindAttribLocation(particle_program, 2, "Lifetime");
  glBindAttribLocation(particle_program, 3, "Size");
  glBindAttribLocation(particle_program, 4, "Color");
  
  oxygarum_link_program(particle_program);
}

void oxygarum_render_particle_system(particle_emitter_t *emitter) {
  glBindBuffer(GL_ARRAY_BUFFER, emitter->particle_buffer[emitter->current_vb]);
  
  glVertexPointer(3, GL_FLOAT, sizeof(particle_t), 0x0);
  glColorPointer(4, GL_FLOAT, sizeof(particle_t), 0x20);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  
  glDrawArrays(GL_POINTS, 0, emitter->particle_counter);
  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
}

void oxygarum_update_particle_system(particle_emitter_t *emitter, float frametime) {
  emitter->current_vb = emitter->current_tfb;
  emitter->current_tfb = 1 - emitter->current_vb;
  
  glUseProgram(particle_program); 
  glUniform1f(loc_anim_speed, frametime);
  glUniform1f(loc_seed, emitter->seed);
  glUniform3f(loc_gvector, emitter->gravity_vector);
  glUniform4f(loc_gvertex, emitter->gravity_vertex);  
  
  glBindBuffer(GL_ARRAY_BUFFER, emitter->particle_buffer[emitter->current_vb]);
  glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, emitter->transform_feedback[emitter->current_tfb]);
  //glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, emitter->transform_feedback[emitter->current_tfb]);
  
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);
  glEnableVertexAttribArray(4);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(particle_t), 0x00); // position
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(particle_t), 0x0C); // velocity
  glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(particle_t), 0x18); // lifetime
  glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(particle_t), 0x1C); // size
  glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(particle_t), 0x20); // color
  
  glEnable(GL_RASTERIZER_DISCARD);
  glBeginTransformFeedback(GL_POINTS);
  glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, 0);
  
  glDrawArrays(GL_POINTS, 0, emitter->particle_counter);
  
  glEndTransformFeedback();
  glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
  glGetQueryObjectuiv(0, GL_QUERY_RESULT, &emitter->particle_counter);
  glDisable(GL_RASTERIZER_DISCARD);  

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glDisableVertexAttribArray(3);
  glDisableVertexAttribArray(4);
  
  glUseProgram(0);
}

