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
#include <GL/glut.h>
#include "opengl.h"
#include "vertex.h"
#include "object.h"

vertex_t loc = {.x = 0, .y = 0, .z = -3};
vertex_t rot = {.x = 0, .y = 0, .z = 0};

unsigned int display_object_counter = 0;
object_t *display_objects[2];

void cliter_ilde(void) {
  
  glutPostRedisplay();
}

void cliter_display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.1, 0.1, 0.1, 1.0);
  
  glRotatef(rot.x, 1.0f,0.0f,0.0f);
  glRotatef(rot.y, 0.0f,1.0f,0.0f);
  glRotatef(rot.z, 0.0f,0.0f,1.0f);
  
  rot.x += 0.05;
  rot.y += 0.05;
  rot.z += 0.05;
  
  glTranslatef(loc.x, loc.y, loc.z);
  
  int i;
  for(i = 0; i < display_object_counter; i++) {
    cliter_display_object(display_objects[i]);
  }
  
  glLoadIdentity();
  glutSwapBuffers();
}

void cliter_add_object(object_t *object) {
  display_objects[display_object_counter++] = object;
}
