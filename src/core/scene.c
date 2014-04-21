/**
 *  src/core/scene.c
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
#include <stdlib.h>

#include "scene.h"
#include "object.h"
#include "particle.h"
#include "font.h"
#include "light.h"

scene_t *oxygarum_create_scene(void) {
  scene_t *scene = malloc(sizeof(scene_t));
  
  scene->objects3d = oxygarum_create_group();
  scene->objects2d = oxygarum_create_group();
  scene->texts = oxygarum_create_group();
  scene->particle_emitters = oxygarum_create_group();
  scene->lights = oxygarum_create_group();
  
  scene->physics = NULL;  
  
  return scene;
}

void oxygarum_render_scene_3d(scene_t *scene) {
  group_entry_t *entry;  

  // update lights
  entry = scene->lights->head;
  while(entry != NULL) {
    light_t *light = (light_t*) entry->element;
    if(light == NULL) {
      continue;
    }
    
    glPushMatrix();
      glTranslatef(light->pos.x, light->pos.y, light->pos.z);
      glRotatef(light->rot.x, 1.0f,0.0f,0.0f);
      glRotatef(light->rot.y, 0.0f,1.0f,0.0f);
      glRotatef(light->rot.z, 0.0f,0.0f,1.0f);
      
      glLightfv(light->gl_light, GL_AMBIENT, light->ambient);
      glLightfv(light->gl_light, GL_DIFFUSE, light->diffuse);
      glLightfv(light->gl_light, GL_SPECULAR, light->specular);
      glLightfv(light->gl_light, GL_POSITION, light->r_pos);
    glPopMatrix();
    
    entry = entry->next;
  }
  
  // render 3D-Objects
  entry = scene->objects3d->head;
  while(entry != NULL) {
    object3d_t *obj = (object3d_t*) entry->element;
    
    if(obj == NULL) {
      continue;
    }
    
    if(obj->status & OBJECT_VISIBLE) {
      glPushMatrix();
      glPushAttrib(GL_ENABLE_BIT);
      
      oxygarum_render_object3d(obj);
      
      glPopAttrib();
      glPopMatrix();
    }
    
    entry = entry->next;
  }
  
  // render particles
  entry = scene->particle_emitters->head;
  while(entry != NULL) {
    particle_emitter_t *emitter = (particle_emitter_t*) entry->element;
    if(emitter == NULL) {
      continue;
    }
    
    glPushMatrix();
      glTranslatef(emitter->pos.x, emitter->pos.y, emitter->pos.z);
      oxygarum_render_particle_system(emitter);
    glPopMatrix();
    
    entry = entry->next;
  }
}

void oxygarum_render_scene_2d(scene_t *scene) {
  group_entry_t *entry;  
  
  // render 2D-Objects
  entry = scene->objects2d->head;
  while(entry != NULL) {
    object2d_t *obj = (object2d_t*) entry->element;
    if(obj == NULL) {
      continue;
    }
    
    if(obj->status & OBJECT_VISIBLE) {
      glPushMatrix();
        oxygarum_render_object2d(obj);
      glPopMatrix();
    }
    
    entry = entry->next;
  }
  
  // render texts
  entry = scene->texts->head;
  while(entry != NULL) {
    text_t *text = (text_t*) entry->element;
    if(text == NULL) {
      continue;
    }
    
    glPushMatrix();
      oxygarum_render_text(text);
    glPopMatrix();
    
    entry = entry->next;
  }
}

light_t *oxygarum_create_light(void) {
  light_t *light = malloc(sizeof(light_t));
  return light;
}

