/**
 *  src/opengl.c
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
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "opengl.h"
#include "keyboard.h"

static int window;
static int width, height;
static int view_x, view_y;
static float fov = 45.0f;
static const char *title;

GLfloat light_ambient[]=  { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat light_diffuse[]=  { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light_specular[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat light_position[]= { 0.0f, 0.0f, 2.0f, 1.0f };

void oxygarum_init_glut(int argc, char **argv) {
  glutInit((void*)&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
  glutInitWindowSize(width, height);
  glutInitWindowPosition(0, 0);
  window = glutCreateWindow(title);
  glutDisplayFunc(&oxygarum_display);
  glutIdleFunc   (&oxygarum_idle);
  glutTimerFunc  (25, &oxygarum_timer, 0);
  glutReshapeFunc(&oxygarum_reshape);
  glutKeyboardFunc(&oxygarum_handle_keyboard_event);
}

void oxygarum_init_opengl(int argc, char **argv) {  
  oxygarum_init_glut(argc, argv);
  
  glClearColor(0.0, 0.0, 0.2, 0.0);
  glClearDepth(1.0);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  glViewport(view_x, view_y, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fov, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_TEXTURE_2D);
}

void oxygarum_set_light(GLenum light, GLfloat *ambient, GLfloat *diffuse, GLfloat *specular, GLfloat *position) {
  glEnable(GL_LIGHTING);
  glLightfv(light, GL_AMBIENT,  ambient);
  glLightfv(light, GL_DIFFUSE,  diffuse);
  glLightfv(light, GL_SPECULAR, specular);
  glLightfv(light, GL_POSITION, position);
  
  glEnable(light);
}

void oxygarum_reshape(int _width, int _height) {
  width= _width;
  height = _height;
  
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(view_x, view_y, width, height);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fov, (GLfloat)width/(GLfloat)height, 1.0f, 1000.0f);
  
  glutPostRedisplay();
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

