//
// this simple demo will draw a rotating
// textured cube using the oxygarum 3D-Engine.
//
// Copyright (C) 2012-2013 Michael Sippel
// <michamimosa@gmail.com>
//

#include <oxygarum.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char text1[100];
char text2[100];

int main(int argc, char **argv) {
  oxygarum_set_resolution(800, 600);
  oxygarum_set_title("Oxygarum test");
  
  init_oxygarum();
  
  // create screen (with viewport, FOV, etc.)
  screen_t *screen = oxygarum_create_screen();  
  
  // load mesh and create object
  object3d_t *object = oxygarum_create_object3d();
  object->mesh = oxygarum_load_oxy3d_file("cube.oxy3d");
  object->pos.x = 0;
  object->pos.y = 0;
  object->pos.z = -4;
  object->rot.x = 10;
  object->rot.y = 30;
  object->rot.z = 10;
  object->shade_program = 0;
  object->shade_model = GL_FLAT;
  object->status = OBJECT_VISIBLE | OBJECT_TRANSPARENT;
  
  // setup scene
  scene_t *scene = oxygarum_create_scene();
  oxygarum_add_object3d(scene, object);
  screen->scene = scene;

  // physics
  physics_t *physics = oxygarum_create_physics();
  force_field_t *gravity = oxygarum_create_force_field();
  gravity->force.y = -0.0000981;

  oxygarum_add_force_field(physics, gravity);

  scene->physics = physics;

  // main loop
  while(1) {
    // update (calculate frametime, handle events, etc.)
    float frametime = oxygarum_update();
    
    // render
    oxygarum_render_screen(screen);
    
    // update
    object->rot.y += frametime * 0.05;
    oxygarum_update_physics(scene, frametime);
  }
  
  return 0;
}

