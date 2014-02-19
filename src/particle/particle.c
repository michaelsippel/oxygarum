/**
 *  src/particle/particle.c
 *
 *  (C) Copyright 2013-2014 Michael Sippel
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
#include <GL/glext.h>
#include <stdlib.h>
#include <string.h>
#include "particle.h"

static GLuint particle_program;
extern char *particle_vertexshader;
extern char *particle_geometryshader;

GLint loc_aspeed;
GLint loc_gvector;
GLint loc_gvertex;
GLint loc_gspeed;

static GLint random_buffer_id;
static float random_buffer[1024];

float rand_between(float min, float max) {
  float ret;
  float diff = max - min;
  ret = min + (( rand() / (RAND_MAX +1.0)) * diff);
  return ret;
}

particle_emitter_t *oxygarum_create_emitter(particle_t *borders, int max_particles) {
  particle_emitter_t *emitter = malloc(sizeof(particle_emitter_t));
  memset(emitter, 0, sizeof(particle_emitter_t));
  
  emitter->particle_counter = 0;
  emitter->max_particles = max_particles;
  
  particle_t *buffer = malloc(sizeof(particle_t)*emitter->max_particles);
  int i;
  for(i = 0; i < emitter->max_particles; i++) {
    buffer[i].seed = (float)i / emitter->max_particles;
    buffer[i].pos.x = rand_between(borders[0].pos.x, borders[1].pos.x);
    buffer[i].pos.y = rand_between(borders[0].pos.y, borders[1].pos.y);
    buffer[i].pos.z = rand_between(borders[0].pos.z, borders[1].pos.z);
    buffer[i].velocity.x = rand_between(borders[0].velocity.x, borders[1].velocity.x);
    buffer[i].velocity.y = rand_between(borders[0].velocity.y, borders[1].velocity.y);
    buffer[i].velocity.z = rand_between(borders[0].velocity.z, borders[1].velocity.z);
    buffer[i].lifetime = rand_between(borders[0].lifetime, borders[1].lifetime);
    buffer[i].size = rand_between(borders[0].size, borders[1].size);
    buffer[i].color.rgb.r = rand_between(borders[0].color.rgb.r, borders[1].color.rgb.r);
    buffer[i].color.rgb.g = rand_between(borders[0].color.rgb.g, borders[1].color.rgb.g);
    buffer[i].color.rgb.b = rand_between(borders[0].color.rgb.b, borders[1].color.rgb.b);
    buffer[i].color.rgb.a = rand_between(borders[0].color.rgb.a, borders[1].color.rgb.a);
  }
  
  glGenBuffers(1, &emitter->particle_buffer[0]);
  glGenBuffers(1, &emitter->particle_buffer[1]);

  glBindBuffer(GL_ARRAY_BUFFER, emitter->particle_buffer[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(particle_t)*emitter->max_particles, buffer, GL_STATIC_DRAW);
  
  glBindBuffer(GL_ARRAY_BUFFER, emitter->particle_buffer[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(particle_t)*emitter->max_particles, NULL, GL_STATIC_DRAW);  

  return emitter;
}

void oxygarum_init_particle_shader(void) {
  // create noise-texture
  int i;
  for(i = 0; i < 1024; i++) {
    random_buffer[i] = rand_between(0.0f, 1.0f);
  }
  
  glGenTextures(1, &random_buffer_id);
  glBindTexture(GL_TEXTURE_1D, random_buffer_id);
  glTexImage1D(GL_TEXTURE_1D, 0, 1, 256, 0, GL_RGB, GL_FLOAT, &random_buffer);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
  
  // load shaders
  GLuint vertexshader = oxygarum_create_shader(GL_VERTEX_SHADER, particle_vertexshader, strlen(particle_vertexshader));
  
  particle_program = glCreateProgram();
  glAttachShader(particle_program, vertexshader);
  
  const char *varyings[] = {"pos","vel","lifetime","size","color","seed"};
  glTransformFeedbackVaryings(particle_program, 6, varyings, GL_INTERLEAVED_ATTRIBS);
  
  glBindAttribLocation(particle_program, 0, "Pos");
  glBindAttribLocation(particle_program, 1, "Vel");
  glBindAttribLocation(particle_program, 2, "Lifetime");
  glBindAttribLocation(particle_program, 3, "Size");
  glBindAttribLocation(particle_program, 4, "Color");
  glBindAttribLocation(particle_program, 5, "Seed");
  
  oxygarum_link_program(particle_program);
}

void oxygarum_render_particle_system(particle_emitter_t *emitter) {
  glBindBuffer(GL_ARRAY_BUFFER, emitter->particle_buffer[emitter->output]);
  
  glVertexPointer(3, GL_FLOAT, sizeof(particle_t), 0x0);
  glColorPointer(4, GL_FLOAT, sizeof(particle_t), 0x20);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  
  glDrawArrays(GL_POINTS, NULL, emitter->max_particles);
  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
}

void oxygarum_update_particle_system(particle_emitter_t *emitter, float frametime) {
  emitter->input = emitter->output;
  emitter->output = 1 - emitter->output;
  
  glEnable(GL_RASTERIZER_DISCARD);
  glUseProgram(particle_program);
  
  loc_aspeed  = glGetUniformLocation(particle_program, "aspeed");
  loc_gvector = glGetUniformLocation(particle_program, "gvector");
  loc_gvertex = glGetUniformLocation(particle_program, "gvertex");
  loc_gspeed  = glGetUniformLocation(particle_program, "gspeed");
  glUniform1f(loc_aspeed, (GLfloat)frametime);
  glUniform3f(loc_gvector, (GLfloat)emitter->gravity_vector.x, (GLfloat)emitter->gravity_vector.y, (GLfloat)emitter->gravity_vector.z);
  glUniform3f(loc_gvertex, emitter->gravity_vertex.x, emitter->gravity_vertex.y, emitter->gravity_vertex.z);  
  glUniform1f(loc_gspeed, (GLfloat)emitter->gravity_speed);
  
  glBindBuffer(GL_ARRAY_BUFFER, emitter->particle_buffer[emitter->input]);
  glEnable(GL_TEXTURE_1D);
  glBindTexture(GL_TEXTURE_1D, random_buffer_id);
  
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);
  glEnableVertexAttribArray(4);
  glEnableVertexAttribArray(5);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(particle_t), 0x00); // position
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(particle_t), 0x0C); // velocity
  glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(particle_t), 0x18); // lifetime
  glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(particle_t), 0x1C); // size
  glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(particle_t), 0x20); // color
  glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(particle_t), 0x30); // seed
  
  glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, emitter->particle_buffer[emitter->output]);
  
  glBeginTransformFeedback(GL_POINTS);
  glDrawArrays(GL_POINTS, NULL, emitter->max_particles);
  glEndTransformFeedback();
  
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glDisableVertexAttribArray(3);
  glDisableVertexAttribArray(4);
  glDisableVertexAttribArray(5);
  
  glUseProgram(0);
  glDisable(GL_RASTERIZER_DISCARD);
}

