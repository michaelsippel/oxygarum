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
#include "group.h"

typedef struct scene {
  group_t *objects3d;
  group_t *objects2d;
  group_t *texts;
  group_t *particle_emitters;
  group_t *lights;
  
  struct physics *physics;
} scene_t;

scene_t *oxygarum_create_scene(void);
void oxygarum_render_scene_3d(scene_t *scene);
void oxygarum_render_scene_2d(scene_t *scene);

#endif

