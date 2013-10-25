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
#include "scene.h"

#include "object.h"
#include "particle.h"
#include "font.h"
#include "light.h"

scene_t *oxygarum_create_scene(void) {
  scene_t *scene = malloc(sizeof(scene_t));
  
  scene->object3d_counter = 0;
  scene->objects3d = NULL;
  
  scene->object2d_counter = 0;
  scene->objects2d = NULL;
  
  scene->text_counter = 0;
  scene->texts = NULL;  
  
  scene->particle_system_counter = 0;
  scene->particle_emitters = NULL;
  
  scene->light_counter = 0;
  scene->lights = NULL;
  
  scene->physics = NULL;  
  
  return scene;
}

void oxygarum_render_scene_3d(scene_t *scene) {
  int i;
  
  // update lights
  for(i = 0; i < scene->light_counter; i++) {
    if(scene->lights[i] == NULL) {
      continue;
    }
    
    glPushMatrix();
    glTranslatef(scene->lights[i]->pos.x, scene->lights[i]->pos.y, scene->lights[i]->pos.z);
    glRotatef(scene->lights[i]->rot.x, 1.0f,0.0f,0.0f);
    glRotatef(scene->lights[i]->rot.y, 0.0f,1.0f,0.0f);
    glRotatef(scene->lights[i]->rot.z, 0.0f,0.0f,1.0f);
    
    glLightfv(scene->lights[i]->gl_light, GL_AMBIENT, scene->lights[i]->ambient);
    glLightfv(scene->lights[i]->gl_light, GL_DIFFUSE, scene->lights[i]->diffuse);
    glLightfv(scene->lights[i]->gl_light, GL_SPECULAR, scene->lights[i]->specular);
    glLightfv(scene->lights[i]->gl_light, GL_POSITION, scene->lights[i]->r_pos);
    glPopMatrix();
  }
  
  // render 3D-Objects
  for(i = 0; i < scene->object3d_counter; i++) {
    if(scene->objects3d[i] == NULL) {
      continue;
    }
    
    if(scene->objects3d[i]->status & OBJECT_VISIBLE) {
      glPushMatrix();
      glPushAttrib(GL_ENABLE_BIT);
      
      oxygarum_render_object3d(scene->objects3d[i]);
      
      glPopAttrib();
      glPopMatrix();
    }
  }
  
  // render particles
  for(i = 0; i < scene->particle_system_counter; i++) {
    if(scene->particle_emitters[i] == NULL) {
      continue;
    }
    
   // oxygarum_render_particle_system(scene->particle_emitters[i]);
  }
}

void oxygarum_render_scene_2d(scene_t *scene) {
  int i;
  
  // render 2D-Objects
  for(i = 0; i < scene->object2d_counter; i++) {
    if(scene->objects2d[i] == NULL) {
      continue;
    }
    
    if(scene->objects2d[i]->status & OBJECT_VISIBLE) {
      glPushMatrix();
      oxygarum_render_object2d(scene->objects2d[i]);
      glPopMatrix();
    }
  }
  
  // render texts
  for(i = 0; i < scene->text_counter; i++) {
    if(scene->texts[i] == NULL) {
      continue;
    }
    
    glPushMatrix();
    oxygarum_render_text(scene->texts[i]);
    glPopMatrix();
  }
}

int oxygarum_add_object3d(scene_t *scene, object3d_t *obj) {
  int id = scene->object3d_counter++;
  scene->objects3d = realloc(scene->objects3d, scene->object3d_counter * sizeof(object3d_t*));
  
  scene->objects3d[id] = obj;
  
  return id;
}

int oxygarum_add_object2d(scene_t *scene, object2d_t *obj) {
  int id = scene->object2d_counter++;
  scene->objects2d = realloc(scene->objects2d, scene->object2d_counter * sizeof(object2d_t*));
  
  scene->objects2d[id] = obj;
  
  return id;
}

int oxygarum_add_text(scene_t *scene, text_t *text) {
  int id = scene->text_counter++;
  scene->texts = realloc(scene->texts, scene->text_counter * sizeof(text_t*));
  
  scene->texts[id] = text;
  
  return id;
}

int oxygarum_add_emitter(scene_t *scene, particle_emitter_t *emitter) {
  int id = scene->particle_system_counter++;
  scene->particle_emitters = realloc(scene->particle_emitters, scene->particle_system_counter * sizeof(particle_emitter_t*));
  
  scene->particle_emitters[id] = emitter;
  
  return id;
}

int oxygarum_add_light(scene_t *scene, light_t *light) {
  glLightfv(light->gl_light, GL_AMBIENT, light->ambient);
  glLightfv(light->gl_light, GL_DIFFUSE, light->diffuse);
  glLightfv(light->gl_light, GL_SPECULAR, light->specular);
  glLightfv(light->gl_light, GL_POSITION, light->r_pos);
  
  glEnable(light->gl_light);  
  
  int id = scene->light_counter++;
  scene->lights = realloc(scene->lights, scene->light_counter * sizeof(light_t*));
  
  scene->lights[id] = light;
  
  return id;
}

void oxygarum_remove_object3d(scene_t *scene, int id) {
  scene->objects3d[id] = NULL;
}

void oxygarum_remove_object2d(scene_t *scene, int id) {
  scene->objects2d[id] = NULL;
}

void oxygarum_remove_text(scene_t *scene, int id) {
  scene->texts[id] = NULL;
}

void oxygarum_remove_emitter(scene_t *scene, int id) {
  scene->particle_emitters[id] = NULL;
}

void oxygarum_remove_light(scene_t *scene, int id) {
  scene->lights[id] = NULL;
}

