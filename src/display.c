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
#define _OBJECT_OFFSET
#include <unistd.h>
#include <stdio.h>
#include <GL/glut.h>
#include "opengl.h"
#include "vertex.h"
#include "object.h"

vertex_t loc = {.x = 0, .y = 0, .z = -5};
vertex_t rot = {.x = 0, .y = 0, .z = 0};
vertex_t object_offset;

unsigned int display_object_counter = 0;
display_obj_t *display_objects;

int frame_counter = 0;
int time_cur = 0, time_prev = 0;
float fps = 0;

void oxygarum_calc_fps() {
  frame_counter++;
  time_cur = glutGet(GLUT_ELAPSED_TIME);
  
  int diff = time_cur - time_prev;
  
  if(diff > 1000) {
    fps = frame_counter / (diff / 1000.0f);
    time_prev = time_cur;
    frame_counter = 0;
  }
}

void oxygarum_ilde(void) {
  oxygarum_calc_fps();
  glutPostRedisplay();
}

void oxygarum_display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.1, 0.1, 0.1, 1.0);
  
  printf("%f fps\n", fps);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glRotatef(rot.x, 1.0f,0.0f,0.0f);
  glRotatef(rot.y, 0.0f,1.0f,0.0f);
  glRotatef(rot.z, 0.0f,0.0f,1.0f);  
  
  glTranslatef(loc.x, loc.y, loc.z);
  
  int i;
  for(i = 0; i < display_object_counter; i++) {
    glRotatef(display_objects[i].rot.x, 1.0f,0.0f,0.0f);
    glRotatef(display_objects[i].rot.y, 0.0f,1.0f,0.0f);
    glRotatef(display_objects[i].rot.z, 0.0f,0.0f,1.0f);
    
    object_offset = display_objects[i].pos;
    oxygarum_display_object(display_objects[i].object);
  }
  
  glFlush();
  glutSwapBuffers();
}

int oxygarum_add_object(object_t *object, double x, double y, double  z) {
  if(display_object_counter > 0) {
    display_objects = realloc(display_objects, (display_object_counter+1) * sizeof(display_obj_t));
  } else {
    display_objects = malloc(sizeof(display_obj_t));
  }
  
  display_objects[display_object_counter].object = object;
  display_objects[display_object_counter].pos.x = x;
  display_objects[display_object_counter].pos.y = y;
  display_objects[display_object_counter].pos.z = z;
  
  return display_object_counter++;
}

void oxygarum_translate_object_to(int id, double new_x, double new_y, double new_z) {
  display_objects[id].pos.x = new_x;
  display_objects[id].pos.y = new_y;
  display_objects[id].pos.z = new_z;
}

void oxygarum_rotate_object_to(int id, double new_x, double new_y, double new_z) {
  display_objects[id].rot.x = new_x;
  display_objects[id].rot.y = new_y;
  display_objects[id].rot.z = new_z;
}

void oxygarum_translate_camera_to(double new_x, double new_y, double new_z) {
  loc.x = new_x;
  loc.y = new_y;
  loc.z = new_z;
}

void oxygarum_rotate_camera_to(double new_x, double new_y, double new_z) {
  rot.x = new_x;
  rot.y = new_y;
  rot.z = new_z;
}

