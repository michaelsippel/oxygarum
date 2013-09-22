/**
 *  include/screen.h
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
#ifndef _SCREEN_H
#define _SCREEN_H

#include "vertex.h"
#include "scene.h"
#include "camera.h"
#include "material.h"

typedef struct viewport {
  float x;
  float y;
  float width;
  float height;
} viewport_t;

typedef struct screen {
  scene_t *scene;
  camera_t *camera;
  viewport_t viewport;
  float width;
  float height;
  color_t background;
} screen_t;

screen_t *oxygarum_create_screen(void);
void oxygarum_render_screen(screen_t *screen);

#endif

