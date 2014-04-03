/**
 *  src/core/screen.c
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
#include <SDL2/SDL.h>
#include "screen.h"

extern SDL_Window *sdl_window;
extern SDL_Renderer *sdl_renderer;

screen_t *oxygarum_create_screen(void) {
  screen_t *screen = malloc(sizeof(screen_t));
  
  screen->scene = NULL;
  screen->camera = malloc(sizeof(camera_t));
  screen->camera->pos.x = 0;
  screen->camera->pos.y = 0;
  screen->camera->pos.z = 0;
  screen->camera->rot.x = 0;
  screen->camera->rot.y = 0;
  screen->camera->rot.z = 0;
  screen->camera->fov = 45.0f;
  screen->viewport.x = 0;
  screen->viewport.y = 0;
  screen->viewport.width = 800;
  screen->viewport.height = 600;
  screen->width = 800;
  screen->height = 600;
  screen->background.rgb.r = 0.1f;
  screen->background.rgb.g = 0.1f;
  screen->background.rgb.b = 0.1f;
  screen->background.rgb.a = 1.0f;
  
  return screen;
}

void oxygarum_render_screen(screen_t *screen) {
  glViewport(screen->viewport.x, screen->viewport.y, screen->viewport.width, screen->viewport.height);
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(screen->background.rgb.r, screen->background.rgb.g, screen->background.rgb.b, screen->background.rgb.a);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluPerspective(screen->camera->fov, (GLfloat)screen->width/(GLfloat)screen->height, 1.0f, 1000.0f);
  
  glRotatef(screen->camera->rot.x, 1.0f,0.0f,0.0f);
  glRotatef(screen->camera->rot.y, 0.0f,1.0f,0.0f);
  glRotatef(screen->camera->rot.z, 0.0f,0.0f,1.0f);
  
  glTranslatef(screen->camera->pos.x, screen->camera->pos.y, screen->camera->pos.z);
  
  oxygarum_render_scene_3d(screen->scene);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glOrtho(0, screen->width, 0, screen->height, -1, 1);
  
  glUseProgram(0);
  glPushAttrib(GL_ENABLE_BIT);
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  oxygarum_render_scene_2d(screen->scene);
  
  glPopAttrib();
  
  glFlush();
  SDL_GL_SwapWindow(sdl_window);
}

