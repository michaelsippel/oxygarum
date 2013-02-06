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

#define CLITER_FULLSCREEN 0

void cliter_ilde(void);
void cliter_display(void);

void cliter_init_glut(int argc, char **argv);
void cliter_init_opengl(int argc, char **argv);

void cliter_set_resolution(int _width, int _height);
void cliter_set_title(const char *_title);
void cliter_set_flag(int mask, int value);

#endif
