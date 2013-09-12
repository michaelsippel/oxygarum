/**
 *  src/oxygarum.c
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
#include <GL/gl.h>
#include <SDL/SDL.h>

#include "oxygarum.h"

int sdl_surface;
int width, height;
int view_x, view_y;
float fov = 45.0f;
const char *title = NULL;

void oxygarum_init_sdl(void) {
  int state = SDL_Init(SDL_INIT_VIDEO);
  if(state < 0) {
    printf("Error initalizing SDL.\n");
    exit(EXIT_FAILURE);
  }
  
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE,     5);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,   5);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,    5);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,  16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  
  int flags = SDL_OPENGL | SDL_HWPALETTE | SDL_SWSURFACE;
  sdl_surface = SDL_SetVideoMode(width, height, 0, flags);
}

void oxygarum_init_opengl(void) {
  glClearColor(0.0, 0.0, 0.2, 0.0);
  glClearDepth(1.0);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
}

void init_oxygarum(void) {
  oxygarum_init_sdl();
  oxygarum_init_opengl();
}

void oxygarum_set_resolution(int _width, int _height) {
  width = _width;
  height = _height;
}

void oxygarum_set_viewport(int _x, int _y) {
  view_x = _x;
  view_y = _y;
}

void oxygarum_set_title(const char *_title) {
  title = _title;
}

void oxygarum_set_fov(float _fov) {
  fov = _fov;
}

