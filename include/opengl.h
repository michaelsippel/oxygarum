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

#define SHADE_FLAT 0
#define SHADE_SMOOTH 1

void oxygarum_animation_func(void (*handler)(void));
void oxygarum_ilde(void);
void oxygarum_display(void);

void oxygarum_init_glut(int argc, char **argv);
void oxygarum_init_opengl(int argc, char **argv);
void oxygarum_reshape(int _width, int _height);

void oxygarum_set_light(GLenum light, GLfloat *ambient, GLfloat *diffuse, GLfloat *specular, GLfloat *position);
void oxygarum_set_resolution(int _width, int _height);
void oxygarum_set_title(const char *_title);
void oxygarum_set_flag(int mask, int value);

#endif
