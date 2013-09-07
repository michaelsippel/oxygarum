/**
 *  src/render/display.c
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
#include <unistd.h>
#include <stdio.h>
#include <GL/glut.h>
#include "opengl.h"
#include "vertex.h"
#include "object.h"
#include "font.h"
#include "light.h"

static vertex3d_t loc = {.x = 0, .y = 0, .z = 0};
static vertex3d_t rot = {.x = 0, .y = 0, .z = 0};
void (*oxygarum_animate)(void);

unsigned int absolute_light_counter = 0;
light_t **absolute_lights;

static int frame_counter = 0;
static int time_cur = 0, time_prev = 0, time_diff = 0;
static float fps = 0;
static float frame_time = 0;
static float max_fps = 0;

void oxygarum_calc_fps(void) {
  frame_counter++;
  time_cur = glutGet(GLUT_ELAPSED_TIME);
  
  time_diff = time_cur - time_prev;
  frame_time = time_diff / frame_counter;
  if(time_diff > 1000) {
    fps = frame_counter / (time_diff / 1000.0f);
    time_prev = time_cur;
    frame_counter = 0;
  }
}

void oxygarum_animation_func(void (*handler)(void)) {
  oxygarum_animate = handler;
}

float oxygarum_get_fps(void) {
  return fps;
}

float oxygarum_get_frametime(void) {
  return frame_time;
}

void oxygarum_set_max_fps(float _max_fps) {
  max_fps = _max_fps;
}

void oxygarum_update(void) {
  oxygarum_calc_fps();
  
  // Animate
  if(oxygarum_animate)
    oxygarum_animate();
  
  glutPostRedisplay();
}

void oxygarum_timer(int value) {
  oxygarum_update();
  if(max_fps > 0) {
    float min_time = 1000000/max_fps;
    float wait_time = min_time - frame_time;
    glutTimerFunc(wait_time/1000, &oxygarum_timer, 0);
  }
}

void oxygarum_idle(void) {
  if(! (max_fps > 0)) {
    oxygarum_update();
  }
}

void oxygarum_display(void) {
  int i,j;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.1, 0.1, 0.1, 1.0);  
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  glRotatef(rot.x, 1.0f,0.0f,0.0f);
  glRotatef(rot.y, 0.0f,1.0f,0.0f);
  glRotatef(rot.z, 0.0f,0.0f,1.0f);  
  
  glTranslatef(loc.x, loc.y, loc.z);
  
  for(i = 0; i < absolute_light_counter; i++) {
    light_t *l = absolute_lights[i];
    glLightfv(l->gl_light, GL_POSITION, l->pos);
  }
  
  oxygarum_render_all_objects3d();
  
  glPushAttrib(GL_ENABLE_BIT);
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);  
  
  // particles
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  oxygarum_render_all_particles();  
  
  // display fonts and 2d-objects
  glOrtho(0, oxygarum_get_width(), 0, oxygarum_get_height(), -1, 1);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  oxygarum_render_all_objects2d();
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, oxygarum_get_width(), 0, oxygarum_get_height(), -1, 1); 
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  oxygarum_render_all_texts();  
  
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  
  glPopAttrib();
  glFlush();
  glutSwapBuffers();
}

int oxygarum_add_light(light_t *light, int light_pos) {
  glLightfv(light->gl_light, GL_AMBIENT,  light->ambient);
  glLightfv(light->gl_light, GL_DIFFUSE,  light->diffuse);
  glLightfv(light->gl_light, GL_SPECULAR, light->specular);
  glLightfv(light->gl_light, GL_POSITION, light->pos);
  
  glEnable(light->gl_light);
  
  if(light_pos == LIGHT_POSITION_ABSOLUTE) {
    int id;
    id = absolute_light_counter++;
    if(absolute_light_counter > 0) {
      absolute_lights = realloc(absolute_lights, absolute_light_counter * sizeof(light_t));
    } else {
      absolute_lights = malloc(sizeof(light_t));
    }
    
    absolute_lights[id] = light;
    return id;
  }
  
  return -1;
}
void oxygarum_remove_absolute_light(int id) {
  free(absolute_lights[id]);
  absolute_lights[id] = NULL;
}

void oxygarum_translate_camera_to(float new_x, float new_y, float new_z) {
  loc.x = new_x;
  loc.y = new_y;
  loc.z = new_z;
}
void oxygarum_rotate_camera_to(float new_x, float new_y, float new_z) {
  rot.x = new_x;
  rot.y = new_y;
  rot.z = new_z;
}
void oxygarum_translate_camera(float x_off, float y_off, float z_off) {
  loc.x += x_off;
  loc.y += y_off;
  loc.z += z_off;
}
void oxygarum_rotate_camera(float x_off, float y_off, float z_off) {
  rot.x += x_off;
  rot.y += y_off;
  rot.z += z_off;
}

