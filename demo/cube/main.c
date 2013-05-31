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

int id;

void anim(void) {
  oxygarum_rotate_object3d(id, 0,1,0);
}

int main(int argc, char **argv) {
  oxygarum_set_resolution(800, 600);
  oxygarum_set_title("Oxygarum test");
  oxygarum_animation_func(anim);
  
  init_oxygarum(argc, argv);
  
  object3d_t *object = oxygarum_load_oxy3d_file("cube.oxy3d");
  id = oxygarum_add_object3d(object, 0, 0, -4);
  oxygarum_rotate_object3d(id, 10, 30, 10);  
  oxygarum_enable_object3d_status(id, OBJECT_TRANSPARENT);
  
  glutMainLoop();
  
  return 0;
}

