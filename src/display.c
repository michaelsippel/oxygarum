/**
 *  src/display.c
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
#include <unistd.h>
#include <stdio.h>
#include <GL/glut.h>
#include "opengl.h"
#include "vertex.h"
#include "object.h"

static vertex_t loc = {.x = 0, .y = 0, .z = 0};
static vertex_t rot = {.x = 0, .y = 0, .z = 0};
void (*oxygarum_animate)(void);

unsigned int display_object_counter = 0;
unsigned int display_text_counter = 0;
display_obj_t *display_objects;

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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.1, 0.1, 0.1, 1.0);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  glRotatef(rot.x, 1.0f,0.0f,0.0f);
  glRotatef(rot.y, 0.0f,1.0f,0.0f);
  glRotatef(rot.z, 0.0f,0.0f,1.0f);  
  
  glTranslatef(loc.x, loc.y, loc.z);
  
  int i;
  for(i = 0; i < display_object_counter; i++) {
    if(display_objects[i].status & OBJECT_VISIBLE) {
      glPushMatrix();
      
      if(display_objects[i].status & OBJECT_TRANSPARENT) {
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      }
      
      glTranslatef(display_objects[i].pos.x, display_objects[i].pos.y, display_objects[i].pos.z);
      
      glRotatef(display_objects[i].rot.x, 1.0f,0.0f,0.0f);
      glRotatef(display_objects[i].rot.y, 0.0f,1.0f,0.0f);
      glRotatef(display_objects[i].rot.z, 0.0f,0.0f,1.0f);   
      
      oxygarum_display_object(display_objects[i].object, display_objects[i].shade_mode);
      
      glPopMatrix();
    }
  }
  
  glFlush();
  glutSwapBuffers();
}

int oxygarum_add_object(object_t *object, float x, float y, float  z) {
  if(display_object_counter > 0) {
    display_objects = realloc(display_objects, (display_object_counter+1) * sizeof(display_obj_t));
  } else {
    display_objects = malloc(sizeof(display_obj_t));
  }
  
  display_objects[display_object_counter].object = object;
  display_objects[display_object_counter].pos.x = x;
  display_objects[display_object_counter].pos.y = y;
  display_objects[display_object_counter].pos.z = z;
  display_objects[display_object_counter].rot.x = 0;
  display_objects[display_object_counter].rot.y = 0;
  display_objects[display_object_counter].rot.z = 0;
  display_objects[display_object_counter].shade_mode = SHADE_FLAT;
  display_objects[display_object_counter].status = OBJECT_VISIBLE;
  
  return display_object_counter++;
}

void oxygarum_set_shade_mode(int id, int mode) {
  display_objects[id].shade_mode = mode;
}

void oxygarum_enable_object_status(int id, int status) {
  display_objects[id].status |= status;
}

void oxygarum_disable_object_status(int id, int status) {
  display_objects[id].status &= ~status;
}

void oxygarum_translate_object_to(int id, float new_x, float new_y, float new_z) {
  display_objects[id].pos.x = new_x;
  display_objects[id].pos.y = new_y;
  display_objects[id].pos.z = new_z;
}

void oxygarum_rotate_object_to(int id, float new_x, float new_y, float new_z) {
  display_objects[id].rot.x = new_x;
  display_objects[id].rot.y = new_y;
  display_objects[id].rot.z = new_z;
}

void oxygarum_translate_object(int id, float x_off, float y_off, float z_off) {
  display_objects[id].pos.x += x_off;
  display_objects[id].pos.y += y_off;
  display_objects[id].pos.z += z_off;
}

void oxygarum_rotate_object(int id, float x_off, float y_off, float z_off) {
  display_objects[id].rot.x += x_off;
  display_objects[id].rot.y += y_off;
  display_objects[id].rot.z += z_off;
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

