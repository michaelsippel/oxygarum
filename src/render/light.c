/**
 *  src/render/light.c
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
#include <unistd.h>
#include <stdio.h>
#include <GL/gl.h>
#include <SDL/SDL.h>
#include "vertex.h"
#include "object.h"
#include "font.h"
#include "light.h"
#include "oxygarum.h"

unsigned int light_counter = 0;
light_t **lights;

void oxygarum_update_lights(void) {
  int i,j;
  
  for(i = 0; i < light_counter; i++) {
    light_t *l = lights[i];
    
    glPushMatrix();
    if(l->rot != NULL) {
      glRotatef(l->rot->x, 1.0f,0.0f,0.0f);
      glRotatef(l->rot->y, 0.0f,1.0f,0.0f);
      glRotatef(l->rot->z, 0.0f,0.0f,1.0f);
    }
    if(l->pos != NULL) {
      glTranslatef(l->pos->x, l->pos->y, l->pos->z);
    }
    
    glLightfv(l->gl_light, GL_POSITION, l->r_pos);
    glPopMatrix();
  }
}

int oxygarum_add_light(light_t *light) {
  glLightfv(light->gl_light, GL_AMBIENT,  light->ambient);
  glLightfv(light->gl_light, GL_DIFFUSE,  light->diffuse);
  glLightfv(light->gl_light, GL_SPECULAR, light->specular);
  glLightfv(light->gl_light, GL_POSITION, light->r_pos);
  
  glEnable(light->gl_light);
  
  int id;
  id = light_counter++;
  lights = realloc(lights, light_counter * sizeof(light_t));
  
  lights[id] = light;
  
  return -1;
}

void oxygarum_remove_light(int id) {
  free(lights[id]);
  lights[id] = NULL;
}

