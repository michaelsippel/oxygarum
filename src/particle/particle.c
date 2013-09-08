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
#include <GL/glut.h>
#include <stdlib.h>
#include "particle.h"

float rand_between(float min, float max) {
  float ret;
  float diff = max - min;
  ret = min + (( rand() / (RAND_MAX +1.0)) * diff);
  return ret;
}

int oxygarum_particle_emit(particle_emitter_t *emitter) {
  particle_t *particle = malloc(sizeof(particle_t));
  
  particle->pos.x = emitter->pos.x;
  particle->pos.y = emitter->pos.y;
  particle->pos.z = emitter->pos.z;
  
  particle->velocity.x = rand_between(emitter->mask_min->velocity.x, emitter->mask_max->velocity.x);
  particle->velocity.y = rand_between(emitter->mask_min->velocity.y, emitter->mask_max->velocity.y);
  particle->velocity.z = rand_between(emitter->mask_min->velocity.z, emitter->mask_max->velocity.z);
  
  particle->age = 0;
  particle->lifetime = rand_between(emitter->mask_min->lifetime, emitter->mask_max->lifetime);
  
  particle->size = rand_between(emitter->mask_min->size, emitter->mask_max->size);
  particle->saturation = 0.5;
  particle->color.rgb.r = 1;
  particle->color.rgb.g = 0;
  particle->color.rgb.b = 0;
  particle->color.rgb.a = 1;
  
  int id;
  int i;
  for(i = 0; i < emitter->num_particles; i++) {
    if(emitter->particles[i] == NULL) {
      id = i;
      break;
    }
  }
  
  if(i >= emitter->num_particles) {
    id = emitter->num_particles++;
    emitter->particles = realloc(emitter->particles, emitter->num_particles * sizeof(particle_t*));
  }
  
  emitter->particles[id] = particle;
  
  return id;
}

void oxygarum_particle_die(particle_emitter_t *emitter, int id) {
  free(emitter->particles[id]);
  emitter->particles[id] = NULL;
}

void oxygarum_update_particle_system(particle_emitter_t *emitter, float frametime) {
  static float time = 0;
  int i;
  
  for(i = 0; i < emitter->num_particles; i++) {
    if(emitter->particles[i] == NULL) {
      continue;
    }
    
    particle_t *particle = emitter->particles[i];    
    
    if(particle->lifetime <= particle->age) {
      oxygarum_particle_die(emitter, i);
      continue;
    }
    
    particle->age += frametime;    
    
    particle->pos.x += particle->velocity.x * frametime;
    particle->pos.y += particle->velocity.y * frametime;
    particle->pos.z += particle->velocity.z * frametime;

    vector3d_t gravity_vector;
    
    switch(emitter->gravity_type) {
      case OXYGARUM_GRAVITY_TYPE_VERTEX:
        gravity_vector.x = emitter->gravity.x - particle->pos.x;
        gravity_vector.y = emitter->gravity.y - particle->pos.y;
        gravity_vector.z = emitter->gravity.z - particle->pos.z;
        break;
      case OXYGARUM_GRAVITY_TYPE_VECTOR:
        gravity_vector.x = emitter->gravity.x;
        gravity_vector.y = emitter->gravity.y;
        gravity_vector.z = emitter->gravity.z;
        break;
      case OXYGARUM_GRAVITY_TYPE_NONE:
        gravity_vector.x = 0;
        gravity_vector.y = 0;
        gravity_vector.z = 0;
        break;
    }
    
    particle->velocity.x += gravity_vector.x * emitter->gravity_speed * frametime;
    particle->velocity.y += gravity_vector.y * emitter->gravity_speed * frametime;
    particle->velocity.z += gravity_vector.z * emitter->gravity_speed * frametime;
  }
  
  time += frametime;
  if(time >= emitter->emision_rate) {
    time = 0;
    for(i = 0; i < emitter->num_particles_per_emission; i++)
      oxygarum_particle_emit(emitter);
  }
}

