/**
 *  include/opengl.h
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
#ifndef _OPENGL_H
#define _OPENGL_H

#include <GL/glut.h>

#define OXYGARUM_FULLSCREEN 0

#ifndef _LIGHT
#define _LIGHT
extern GLfloat light_ambient[4];
extern GLfloat light_diffuse[4];
extern GLfloat light_specular[4];
extern GLfloat light_position[4];
#endif

void oxygarum_ilde(void);
void oxygarum_display(void);

void oxygarum_init_glut(int argc, char **argv);
void oxygarum_init_opengl(int argc, char **argv);
void oxygarum_reshape(int _width, int _height);

void oxygarum_set_resolution(int _width, int _height);
void oxygarum_set_title(const char *_title);
void oxygarum_set_flag(int mask, int value);

#endif
