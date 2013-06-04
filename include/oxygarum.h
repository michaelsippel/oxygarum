/**
 *  include/oxygarum.h
 *
 *  (C) Copyright 2012 Michael Sippel
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

#include <GL/gl.h>

#if defined(__cplusplus)
extern "C" {
#endif

#include "vertex.h"
#include "face.h"
#include "font.h"
#include "object.h"
#include "opengl.h"
#include "material.h"
#include "texture.h"
#include "keyboard.h"

#ifdef __WIN32__
void usleep(unsigned int usec);
#endif

void init_oxygarum(int argc, char **argv);
object3d_t *oxygarum_load_oxy3d_file(const char *path);
float oxygarum_get_fps(void);
void oxygarum_set_max_fps(float max_fps);
float oxygarum_get_frametime(void);

#if defined(__cplusplus)
}
#endif

#endif

