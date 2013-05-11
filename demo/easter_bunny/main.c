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

GLfloat ambient[]= { 0.8f, 0.7f, 0.9f, 1.0f };
GLfloat diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat specular[]= { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat position[]= { 1.0f, 0.5f, -0.1f, 1.0f };

int id;
int shade_mode = 1;

void change_shade(void) {
  shade_mode++;
  shade_mode %= 2;
  oxygarum_set_shade_mode(id, shade_mode);
}

void anim(void) {
  float anim_sens = 100 / 25;
  oxygarum_rotate_object(id, 0, anim_sens, 0);
}

int main(int argc, char **argv) {
  oxygarum_set_resolution(800, 600);
  oxygarum_set_title("Oxygarum test");
  oxygarum_set_flag(OXYGARUM_FULLSCREEN, 0);
  oxygarum_animation_func(&anim);
  
  oxygarum_set_keyboard_event('s', &change_shade);  
  
  init_oxygarum(argc, argv);
  oxygarum_set_light(GL_LIGHT1, ambient, diffuse, specular, position);  
  
  object_t *bunny = oxygarum_load_oxy3d_file("bunny.oxy3d");
  id = oxygarum_add_object(bunny, 0, -1.5, -5);
  oxygarum_set_shade_mode(id, shade_mode);  
  oxygarum_set_max_fps(30);  
  
  glutMainLoop();
  
  return 0;
}

