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

void oxygarum_particle_vitalize(particle_emiter_t *emiter) {
  particle_t *particle = malloc(sizeof(particle_t));
  particle->pos.x = emiter->pos.x;
  particle->pos.y = emiter->pos.x;
  particle->pos.z = emiter->pos.x;
  particle->size = 1;
  particle->saturation = 1;
  particle->color.rgb.r = 1;
  particle->color.rgb.g = 0;
  particle->color.rgb.b = 0;
  particle->color.rgb.a = 1;
  
  int id;
  id = emiter->num_particles++;
  emiter->particles = realloc(emiter->particles, emiter->num_particles * sizeof(particle_t*));
  emiter->particles[id] = particle;
}

void oxygarum_update_particle_system(particle_emiter_t *emiter) {
  int i;
  for(i = 0; i < emiter->num_particles; i++) {
    particle_t *particle = emiter->particles[i];    
    
    particle->pos.x += particle->velocity.x;
    particle->pos.y += particle->velocity.y;
    particle->pos.z += particle->velocity.z;
    
    particle->velocity.x += emiter->gravity.x;
    particle->velocity.y += emiter->gravity.y;
    particle->velocity.z += emiter->gravity.z;
  }
}

