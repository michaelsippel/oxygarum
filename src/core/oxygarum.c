/**
 *  src/core/oxygarum.c
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
#include <SDL2/SDL.h>

#include "oxygarum.h"

int width, height;
int view_x, view_y;
float fov = 45.0f;
const char *title = NULL;

SDL_Window *sdl_window;
SDL_GLContext *sdl_context;

void oxygarum_init_sdl(void) {
  char str[100];
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
    fprintf(stderr, "Error: initalize SDL: %s\n", SDL_GetError());
    return;
  }
  
  sdl_window = SDL_CreateWindow(title, 0, 0, width, height, SDL_WINDOW_OPENGL);
  if(sdl_window == NULL) {
    sprintf(str, "Error: create renderer: %s\n", SDL_GetError());
    fprintf(stderr, "%s", str);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", str, NULL);
  }

  sdl_context = SDL_GL_CreateContext(sdl_window);
}

void oxygarum_init_opengl(void) {
  glClearColor(0.0, 0.0, 0.2, 0.0);
  glClearDepth(1.0);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
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

float oxygarum_update(void) {
  // handle SDL events
  SDL_Event event;
  while(SDL_PollEvent( &event )) {
    oxygarum_handle_sdl_event(&event);
  }
  oxygarum_handle_sdl_event(&event);
  
  // calc frametime
  static float time_prev = 0;
  float time_cur = (float) SDL_GetTicks();
  
  float frametime = time_cur - time_prev;
  time_prev = time_cur;
  
  return frametime;
}


