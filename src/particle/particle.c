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
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include "particle.h"

static GLuint particle_program;
extern char *particle_vertexshader;
extern char *particle_geometryshader;

GLint loc_seed0;
GLint loc_seed1;
GLint loc_seed2;
GLint loc_rand_tex;
GLint loc_aspeed;
GLint loc_spawn_point;
GLint loc_gvector;
GLint loc_gvertex;
GLint loc_gspeed;

GLint loc_pos_min;
GLint loc_pos_max;
GLint loc_vel_min;
GLint loc_vel_max;
GLint loc_col_min;
GLint loc_col_max;
GLint loc_life_min;
GLint loc_life_max;

GLint rand_tex_id;
GLfloat random_buffer[1024];

float noise(void) {
  static int x = 1;
  x++;
  x = (x<<13) ^ x;
  return (float)( 1.0 - ( (x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

float rand_between(float min, float max) {
  float ret;
  float diff = max - min;
  ret = min + (0.5 + noise()*0.5) * diff;

  //printf("random: %f\n", ret);  

  return ret;
}

particle_emitter_t *oxygarum_create_emitter(particle_t *borders, int max_particles) {
  particle_emitter_t *emitter = malloc(sizeof(particle_emitter_t));
  memset(emitter, 0, sizeof(particle_emitter_t));
  
  emitter->borders = borders;
  emitter->max_particles = max_particles;
  
  particle_t *buffer = calloc(sizeof(particle_t), emitter->max_particles);
  int i;
  for(i = 0; i < max_particles; i++) {
    buffer[i].seed_off = ((float)i / max_particles);
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
  
  glGenTextures(1, &rand_tex_id);
  glBindTexture(GL_TEXTURE_1D, rand_tex_id);
  glTexImage1D(GL_TEXTURE_1D, 0, 4, 256, 0, GL_RGBA, GL_FLOAT, &random_buffer);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
  // load shaders
  GLuint vertexshader = oxygarum_create_shader(GL_VERTEX_SHADER, particle_vertexshader, strlen(particle_vertexshader));
  
  particle_program = glCreateProgram();
  glAttachShader(particle_program, vertexshader);
  
  const char *varyings[] = {"pos","vel","lifetime","size","color","seed_off"};
  glTransformFeedbackVaryings(particle_program, 6, varyings, GL_INTERLEAVED_ATTRIBS);
  
  glBindAttribLocation(particle_program, 0, "Pos");
  glBindAttribLocation(particle_program, 1, "Vel");
  glBindAttribLocation(particle_program, 2, "Lifetime");
  glBindAttribLocation(particle_program, 3, "Size");
  glBindAttribLocation(particle_program, 4, "Color");
  glBindAttribLocation(particle_program, 5, "Seed_off");
  oxygarum_link_program(particle_program);

  loc_rand_tex = glGetUniformLocation(particle_program, "rand_tex");
  loc_seed0 = glGetUniformLocation(particle_program, "seed0");
  loc_seed1 = glGetUniformLocation(particle_program, "seed1");
  loc_seed2 = glGetUniformLocation(particle_program, "seed2");

  loc_aspeed  = glGetUniformLocation(particle_program, "aspeed");
  loc_spawn_point = glGetUniformLocation(particle_program, "spawn_point");
  loc_gvector = glGetUniformLocation(particle_program, "gvector");
  loc_gvertex = glGetUniformLocation(particle_program, "gvertex");
  loc_gspeed  = glGetUniformLocation(particle_program, "gspeed");

  loc_pos_min = glGetUniformLocation(particle_program, "pos_min");
  loc_pos_max = glGetUniformLocation(particle_program, "pos_max");
  loc_vel_min = glGetUniformLocation(particle_program, "vel_min");
  loc_vel_max = glGetUniformLocation(particle_program, "vel_max");
  loc_col_min = glGetUniformLocation(particle_program, "col_min");
  loc_col_max = glGetUniformLocation(particle_program, "col_max");
  loc_life_min = glGetUniformLocation(particle_program, "life_min");
  loc_life_max = glGetUniformLocation(particle_program, "life_max");
}

void oxygarum_render_particle_system(particle_emitter_t *emitter) {
  glBindBuffer(GL_ARRAY_BUFFER, emitter->particle_buffer[0]);
  
  glVertexPointer(3, GL_FLOAT, sizeof(particle_t), 0x0);
  glColorPointer(4, GL_FLOAT, sizeof(particle_t), 0x20);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  
  glDrawArrays(GL_POINTS, NULL, emitter->particle_counter);
  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
}

void oxygarum_update_particle_system(particle_emitter_t *emitter, float frametime) {
  GLint swp = emitter->input;
  emitter->input = emitter->output;
  emitter->output = swp;
  
  glEnable(GL_RASTERIZER_DISCARD);
  glUseProgram(particle_program);
  
  glBindBuffer(GL_ARRAY_BUFFER, emitter->particle_buffer[emitter->input]);

  glEnable(GL_TEXTURE_1D);
  glBindTexture(GL_TEXTURE_1D, rand_tex_id);
  glUniform1i(loc_rand_tex, 0);
  glUniform1f(loc_seed0, rand_between(0.0f, 256.0f));
  glUniform1f(loc_seed1, rand_between(0.0f, 256.0f));
  glUniform1f(loc_seed2, rand_between(0.0f, 256.0f));

  glUniform1f(loc_aspeed, (GLfloat)frametime);
  glUniform3fv(loc_spawn_point, 1, &emitter->spawn_point);
  glUniform3fv(loc_gvector, 1, &emitter->gravity_vector);
  glUniform3fv(loc_gvertex, 1, &emitter->gravity_vertex);
  glUniform1f(loc_gspeed, (GLfloat)emitter->gravity_speed);

  glUniform3fv(loc_pos_min, 1, &emitter->borders[0].pos);
  glUniform3fv(loc_pos_max, 1, &emitter->borders[1].pos);
  glUniform3fv(loc_vel_min, 1, &emitter->borders[0].velocity);
  glUniform3fv(loc_vel_max, 1, &emitter->borders[1].velocity);
  glUniform4fv(loc_col_min, 1, &emitter->borders[0].color);
  glUniform4fv(loc_col_max, 1, &emitter->borders[1].color);
  glUniform1fv(loc_life_min, 1, &emitter->borders[0].lifetime);
  glUniform1fv(loc_life_max, 1, &emitter->borders[1].lifetime);

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
  glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(particle_t), 0x30); // seed_off
  
  glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, emitter->particle_buffer[emitter->output]);
  
  glBeginTransformFeedback(GL_POINTS);
  glDrawArrays(GL_POINTS, NULL, emitter->particle_counter);
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

