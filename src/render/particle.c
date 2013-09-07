/**
 *  src/render/particle.c
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
#include "opengl.h"

static int particle_system_counter = 0;
static particle_emiter_t **particle_emiters = NULL;

void oxygarum_render_particle(particle_t *particle) {
  glTranslatef(particle->pos.x,particle->pos.y, particle->pos.z);
  glColor4f(particle->color.color[0]*particle->saturation,
            particle->color.color[1]*particle->saturation,
            particle->color.color[2]*particle->saturation,
            particle->color.color[3]*particle->saturation);
  
  float n = particle->size / 2;
  glBegin(GL_QUADS);
    glVertex3f(-n, n, 0);
    glVertex3f( n, n, 0);
    glVertex3f( n,-n, 0);
    glVertex3f(-n,-n, 0);
  glEnd();
}

void oxygarum_render_particle_system(particle_emiter_t *emiter) {
  int i;
  for(i = 0; i < emiter->num_particles; i++) {
    if(emiter->particles[i] == NULL) continue;
    oxygarum_render_particle(emiter->particles[i]);
  }
}

void oxygarum_render_all_particles(void) {
  int i;
  for(i = 0; i < particle_system_counter; i++) {
    oxygarum_render_particle_system(particle_emiters[i]);
  }
}

void oxygarum_update_all_particles(float frametime) {
  int i;
  for(i = 0; i < particle_system_counter; i++) {
    oxygarum_update_particle_system(particle_emiters[i], frametime);
  }
}

int oxygarum_add_particle_system(particle_emiter_t *emiter) {
  int id;
  id = particle_system_counter++;
  particle_emiters = realloc(particle_emiters, particle_system_counter * sizeof(particle_emiter_t*));
  
  particle_emiters[id] = emiter;
  
  return id;
}

void oxygarum_remove_particle_system(int id) {
  particle_emiters[id] = NULL;
}

