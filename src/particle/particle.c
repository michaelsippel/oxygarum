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
#include "particle.h"

int oxygarum_particle_emit(particle_emitter_t *emitter, vector3d_t *velocity) {
  particle_t *particle = malloc(sizeof(particle_t));
  
  particle->pos.x = emitter->pos.x;
  particle->pos.y = emitter->pos.y;
  particle->pos.z = emitter->pos.z;
  
  particle->velocity.x = velocity->x;
  particle->velocity.y = velocity->y;
  particle->velocity.z = velocity->z;
  
  particle->age = 0;
  particle->lifetime = 5000; 
  
  particle->size = 0.5;
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
    
    particle->velocity.x += emitter->gravity.x * frametime;
    particle->velocity.y += emitter->gravity.y * frametime;
    particle->velocity.z += emitter->gravity.z * frametime;
  }
  
  time += frametime;
  if(time >= emitter->emision_rate) {
    time = 0;
    vector3d_t velocity;
    velocity.x = 0.001;
    velocity.y = 0;
    velocity.z = 0;
    oxygarum_particle_emit(emitter, &velocity);
  }
}

