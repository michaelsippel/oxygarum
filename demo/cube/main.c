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
  
  // load mesh and create object
  struct load_return *ret = oxygarum_load_oxy3d_file("cube.oxy3d", NULL);
  object3d_t *object = oxygarum_create_object3d();
  object->mesh = (mesh3d_t*) oxygarum_get_group_entry(ret->meshes, "cube")->element;
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
  screen_t *screen = oxygarum_create_screen();
  scene_t *scene = oxygarum_create_scene();
  screen->scene = scene;
  oxygarum_group_add(scene->objects3d, object, NULL);
  
  // physics
  physics_t *physics = oxygarum_create_physics();
  scene->physics = physics;
  
  force_field_t *gravity = oxygarum_create_force_field();
  gravity->force.y = 0;//-9.80665;
  gravity->velocity = 0.000001;
  oxygarum_group_add(physics->force_fields, gravity, NULL);
  
  object->physics_properties = oxygarum_create_physics_properties();
  object->physics_properties->rot_velocity.y = 0.5;
  
  // main loop
  while(1) {
    // update (calculate frametime, handle events, etc.)
    float frametime = oxygarum_update();
    
    // render
    oxygarum_render_screen(screen);
    
    // update
    oxygarum_update_physics(scene, frametime);
  }
  
  return 0;
}

