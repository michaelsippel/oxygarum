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

int main(int argc, char **argv) {
  oxygarum_set_resolution(800, 600);
  oxygarum_set_title("Oxygarum test");
  oxygarum_set_flag(OXYGARUM_FULLSCREEN, 0);
  init_oxygarum(argc, argv);  
  
  object_t *object = oxygarum_load_oxy3d_file("cube.oxy3d");
  oxygarum_add_object(object, 0, 0, 0);

  glutMainLoop();
  
  return 0;
}

