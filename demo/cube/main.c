//
// this simple demo will draw a rotating
// textured cube using the oxygarum 3D-Engine.
//
// Copyright (C) 2012-2013 Michael Sippel
// <micha.linuxfreak@gmail.com>
//

#include <oxygarum.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

GLfloat ambient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat specular[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat position[]= { 0.0f, 0.0f, 2.0f, 1.0f };

int main(int argc, char **argv) {
  oxygarum_set_resolution(800, 600);
  oxygarum_set_title("Oxygarum test");
  init_oxygarum(argc, argv);
  
  //oxygarum_set_light(GL_LIGHT1, ambient, diffuse, specular, position);
  
  object_t *object = oxygarum_load_oxy3d_file("cube.oxy3d");
  int id = oxygarum_add_object(object, 0, 0, 0);
  
  glutMainLoop();
  
  return 0;
}

