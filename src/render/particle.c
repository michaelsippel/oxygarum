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
#include "particle.h"

static unsigned int num_particles = 0;
static particle_t *particles[100]; // FIXME!!

void oxygarum_render_particle(particle_t *particle) {
  glTranslatef(particle->pos.x,particle->pos.y, particle->pos.z);
  glColor4f(particle->color.color[0]*particle->saturation,
            particle->color.color[1]*particle->saturation,
            particle->color.color[2]*particle->saturation,
            particle->color.color[3]*particle->saturation);
  
  float n = particle->size / 2;
  glBegin(GL_QUADS);
    glVertex3f(-n, n, -1);
    glVertex3f( n, n, -1);
    glVertex3f( n,-n, -1);
    glVertex3f(-n,-n, -1);
  glEnd();
}

int oxygarum_add_particle(particle_t *particle) {
  int id = num_particles++;
  particles[id] = particle;
  return id;
}

void oxygarum_render_all_particles(void) {
  int i;
  for(i = 0; i < num_particles; i++) {
    oxygarum_render_particle(particles[i]);
  }
}

