/**
 *  src/opengl.c
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
#include <GL/glut.h>
#include "opengl.h"

int window;
int width, height;
unsigned int flags;
const char *title;

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.1, 0.1, 0.1, 1.0);
  glLoadIdentity();
  glutSwapBuffers();
}

void cliter_init_glut(int argc, char **argv) {
  glutInit((void*)&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
  glutInitWindowSize(width, height);  
  glutInitWindowPosition(0, 0);
  window = glutCreateWindow(title);
//   glutSetCursor(GLUT_CURSOR_NONE);
  glutDisplayFunc(&display);
  if(flags & CLITER_FULLSCREEN) glutFullScreen();
  glutIdleFunc(&display);
  glClearColor(0, 0, 0, 0);
  glMatrixMode(GL_PROJECTION);
  gluPerspective(45.0, 1.0, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

void cliter_init_opengl(int argc, char **argv) {  
  cliter_init_glut(argc, argv);
  
  glClearColor(0.0, 0.0, 0.2, 0.0);
  glClearDepth(1.0);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  glViewport(0, 0, width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
  
  glutMainLoop();
}

void cliter_set_resolution(int _width, int _height) {
  width = _width;
  height = _height;
}

void cliter_set_title(const char *_title) {
  title = _title;
}

void cliter_set_flag(int mask, int value) {
  if(value) {
    flags |= mask;
  } else {
    flags &= ~mask;
  }
}
