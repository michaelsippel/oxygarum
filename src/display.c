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
display_obj_t display_objects[10];

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
  rot.x += 0.1;
  rot.y += 0.5;
  
  oxygarum_calc_fps();
  glutPostRedisplay();
}

void oxygarum_display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.1, 0.1, 0.1, 1.0);
  
  printf("%f fps\n", fps);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  glTranslatef(loc.x, loc.y, loc.z);
  
  glRotatef(rot.x, 1.0f,0.0f,0.0f);
  glRotatef(rot.y, 0.0f,1.0f,0.0f);
  glRotatef(rot.z, 0.0f,0.0f,1.0f);
  
  int i;
  for(i = 0; i < display_object_counter; i++) {
    object_offset = display_objects[i].pos;
    oxygarum_display_object(display_objects[i].object);
  }
  
  glFlush();
  glutSwapBuffers();
}

int oxygarum_add_object(object_t *object, double x, double y, double  z) {
  display_objects[display_object_counter].object = object;
  display_objects[display_object_counter].pos.x = x;
  display_objects[display_object_counter].pos.y = y;
  display_objects[display_object_counter].pos.z = z;
  
  return display_object_counter++;
}

