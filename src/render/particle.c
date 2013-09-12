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
#include <GL/gl.h>
#include <stdlib.h>
#include "particle.h"

unsigned int particle_system_counter = 0;
particle_emitter_t **particle_emitters;

void oxygarum_render_particle(particle_t *particle, int tex_id) {
  glTranslatef(particle->pos.x,particle->pos.y, particle->pos.z);
  glColor4f(particle->color.color[0]*particle->saturation,
            particle->color.color[1]*particle->saturation,
            particle->color.color[2]*particle->saturation,
            particle->color.color[3]*particle->saturation);
  glBindTexture(GL_TEXTURE_2D, tex_id);
  
  float n = particle->size / 2;
  glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex3f(-n, n, 0);
    glTexCoord2f(1, 1);
    glVertex3f( n, n, 0);
    glTexCoord2f(1, 0);
    glVertex3f( n,-n, 0);
    glTexCoord2f(0, -0);
    glVertex3f(-n,-n, 0);
  glEnd();
}

void oxygarum_render_particle_system(particle_emitter_t *emitter) {
  int i;

  for(i = 0; i < emitter->num_particles; i++) {
    if(emitter->particles[i] == NULL) continue;

    glPushMatrix();
    oxygarum_render_particle(emitter->particles[i], emitter->texture->id);
    glPopMatrix();
  }
}

void oxygarum_render_all_particles(void) {
  int i;
  for(i = 0; i < particle_system_counter; i++) {
    if(particle_emitters[i] == NULL) continue;
    oxygarum_render_particle_system(particle_emitters[i]);
  }
}

void oxygarum_update_all_particles(float frametime) {
  int i;
  for(i = 0; i < particle_system_counter; i++) {
    if(particle_emitters[i] == NULL) continue;
    oxygarum_update_particle_system(particle_emitters[i], frametime);
  }
}

int oxygarum_add_particle_system(particle_emitter_t *emitter) {
  int id = particle_system_counter++;
  
  particle_emitters = realloc(particle_emitters, particle_system_counter * sizeof(particle_emitter_t*));
  
  particle_emitters[id] = emitter;
  
  return id;
}

void oxygarum_remove_particle_system(int id) {
  particle_emitters[id] = NULL;
}

