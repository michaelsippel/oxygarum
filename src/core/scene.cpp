/**
 *  src/core/scene.cpp
 *
 *  (C) Copyright 2013-2014 Michael Sippel
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

#include <stdlib.h>

#include "scene.h"
#include "object.h"
#include "particle.h"
#include "font.h"
#include "light.h"

Scene::Scene() {
	this->objects3D = new List<Object3D>();
	this->objects2D = new List<Object2D>();
	//this->texts = new List<Text>();
	//this->particle_emitters = new List<ParticleEmitter>();
	//this->lights = new List<Light>();
}

Scene::~Scene() {
	delete this->objects3D;
	delete this->objects2D;
	//delete this->texts;
	//delete this->particle_emitters;
	//delete this->lights;
}

void Scene::render3D(void) {
/*
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
  */

	// render 3D-Objects
	ListEntry<Object3D> *entry = this->objects3D->getHead();

	while(entry != NULL) {
		Object3D *obj = entry->element;
		if(obj == NULL) {
			continue;
		}

		if(obj->getStatus() & OBJECT_VISIBLE) {
			glPushMatrix();
			glPushAttrib(GL_ENABLE_BIT);

			obj->useTransformation();
			obj->render();

			glPopAttrib();
			glPopMatrix();
		}
    
		entry = entry->getNext();
	}
/*
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
  }*/
}

void Scene::render2D(void) {
/*  group_entry_t *entry;  
  
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
  }*/
}

