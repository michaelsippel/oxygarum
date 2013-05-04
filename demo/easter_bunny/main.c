//
// this simple demo will draw a  with
// blender modeled easter bunny
//
// Copyright (C) 2013 Michael Sippel
// <micha.linuxfreak@gmail.com>
//

#include <oxygarum.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int id;

void anim(void) {
  oxygarum_rotate_object(id, 0, 1, 0);
}

int main(int argc, char **argv) {
  oxygarum_set_resolution(800, 600);
  oxygarum_set_title("Oxygarum test");
  oxygarum_set_flag(OXYGARUM_FULLSCREEN, 0);
  oxygarum_animation_func(&anim);
  
  init_oxygarum(argc, argv);
  
  object_t *bunny = oxygarum_load_oxy3d_file("bunny.oxy3d");
  id = oxygarum_add_object(bunny, 0, -1.5, -5);
  
  glutMainLoop();
  
  return 0;
}

