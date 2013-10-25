/**
 *  include/scene.h
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
#ifndef _SCENE_H
#define _SCENE_H

#include "object.h"
#include "particle.h"
#include "physics.h"
#include "light.h"
#include "font.h"

typedef struct scene {
  unsigned int object3d_counter;
  object3d_t **objects3d;
  
  unsigned int object2d_counter;
  object2d_t **objects2d;
  
  unsigned int text_counter;
  text_t **texts;
  
  unsigned int particle_system_counter;
  particle_emitter_t **particle_emitters;
  
  unsigned int light_counter;
  light_t **lights;
  
  struct physics *physics;
} scene_t;

scene_t *oxygarum_create_scene(void);
void oxygarum_render_scene_3d(scene_t *scene);
void oxygarum_render_scene_2d(scene_t *scene);

int oxygarum_add_object3d(scene_t *scene, object3d_t *object);
int oxygarum_add_object2d(scene_t *scene, object2d_t *object);
int oxygarum_add_text(scene_t *scene, text_t *text);
int oxygarum_add_emitter(scene_t *scene, particle_emitter_t *emitter);
int oxygarum_add_light(scene_t *scene, light_t *light);

void oxygarum_remove_object3d(scene_t *scene, int id);
void oxygarum_remove_object2d(scene_t *scene, int id);
void oxygarum_remove_text(scene_t *scene, int id);
void oxygarum_remove_emitter(scene_t *scene, int id);
void oxygarum_remove_light(scene_t *scene, int id);

#endif

