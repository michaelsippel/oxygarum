/**
 *  include/oxygarum.h
 *
 *  (C) Copyright 2012-2013 Michael Sippel
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
#ifndef _OXYGARUM_H
#define _OXYGARUM_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "camera.h"
#include "event.h"
#include "face.h"
#include "font.h"
#include "vertex.h"
#include "object.h"
#include "material.h"
#include "mesh.h"
#include "particle.h"
#include "physics.h"
#include "shader.h"
#include "scene.h"
#include "screen.h"
#include "texture.h"
#include "gui.h"
#include "light.h"
#include "group.h"

void init_oxygarum(void);
void oxygarum_start_render(float _min_frame_time);
void oxygarum_stop_render(void);
void oxygarum_animation_func(void (*handler)(void));
void oxygarum_render(void);
void oxygarum_display(void);
void oxygarum_init_opengl(void);
void oxygarum_set_resolution(int _width, int _height);
void oxygarum_set_viewport(int _x, int _y);
void oxygarum_set_title(const char *_title);
void oxygarum_set_fov(float _fov);
float oxygarum_update(void);

typedef struct load_return {
  group_t *textures;
  group_t *shaders;
  group_t *materials;
  group_t *meshes;
  group_t *objects;
};

struct load_return *oxygarum_load_oxy3d_file(const char *f_path, struct load_return *ret);
mesh2d_t *oxygarum_load_oxy2d_file(const char *path);

#if defined(__cplusplus)
}
#endif

#endif

