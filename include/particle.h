/**
 *  include/particle.h
 *
 *  Copyright (C) 2013 Michael Sippel
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

/**
 * @author Michael Sippel <michamimosa@gmail.com>
 */

#ifndef _PARTICLE_H
#define _PARTICLE_H
/*
#include "vector.h"
#include "material.h"

typedef struct particle {
  vertex3d_t pos;
  vector3d_t velocity;
  float lifetime;
  float size;
  color_t color;
  float seed_off;
} particle_t;

typedef struct particle_emitter {
  GLuint particle_buffer[2];
  int input;
  int output;

  vertex3d_t pos;
  vertex3d_t spawn_point;
  vector3d_t gravity_vector;
  vertex3d_t gravity_vertex;
  float gravity_speed;
  particle_t *borders;

  texture_t *texture;

  unsigned int particle_counter;
  unsigned int max_particles;
  unsigned int emission_rate;
  unsigned int emission_intensity;
} particle_emitter_t;

particle_emitter_t *oxygarum_create_emitter(particle_t *borders, int max_particles);
void oxygarum_init_particle_shader(void);

void oxygarum_render_particle_system(particle_emitter_t *emitter);
void oxygarum_update_particle_system(particle_emitter_t *emitter, float frametime);
*/
#endif

