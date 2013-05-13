//
// In this demo you can walk through a
// little world using the oxygarum 3D-Engine.
//
// Copyright (C) 2013 Michael Sippel
// <micha.linuxfreak@gmail.com>
//

#include <oxygarum.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

GLfloat ambient[]= { 0.8f, 0.7f, 0.9f, 1.0f };
GLfloat diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat specular[]= { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat position[]= { 1.0f, 0.5f, -0.1f, 1.0f };

#define piover180 0.0174532925f
#define SPEED 0.2

int world_id, suzanne_id;
vertex_t rot = {0,0,0};
vertex_t loc = {0,0,-2};

void left(void) {
  rot.y -= 1;
  oxygarum_rotate_camera_to(rot.x, rot.y, rot.z);
}

void right(void) {
  rot.y += 1;
  oxygarum_rotate_camera_to(rot.x, rot.y, rot.z);
}

void forwards(void) {
  loc.z += cos(rot.y*piover180) * SPEED;
  loc.x -= sin(rot.y*piover180) * SPEED;
  oxygarum_translate_camera_to(loc.x, loc.y, loc.z);
}

void back(void) {
  loc.z -= cos(rot.y*piover180) * SPEED;
  loc.x += sin(rot.y*piover180) * SPEED;
  oxygarum_translate_camera_to(loc.x, loc.y, loc.z);
}

void anim(void) {
  oxygarum_rotate_object(suzanne_id, 0,1, 0);
}

int main(int argc, char **argv) {
  oxygarum_set_resolution(800, 600);
  oxygarum_set_title("Oxygarum test");
  oxygarum_set_flag(OXYGARUM_FULLSCREEN, 0);
  
  oxygarum_animation_func(&anim);
  oxygarum_set_keyboard_event('w', &forwards);
  oxygarum_set_keyboard_event('a', &left);
  oxygarum_set_keyboard_event('s', &back);
  oxygarum_set_keyboard_event('d', &right);
  
  oxygarum_translate_camera_to(loc.x, loc.y, loc.z);
  oxygarum_rotate_camera_to(rot.x, rot.y, rot.z);
  
  init_oxygarum(argc, argv);
  
  oxygarum_set_light(GL_LIGHT1, ambient, diffuse, specular, position);
  
  object_t *world = oxygarum_load_oxy3d_file("world.oxy3d");
  object_t *suzanne = oxygarum_load_oxy3d_file("suzanne.oxy3d");
  world_id = oxygarum_add_object(world, 0, 0, 0);
  suzanne_id = oxygarum_add_object(suzanne, 0, 0, 0);
  oxygarum_set_shade_mode(suzanne_id, SHADE_SMOOTH);
  oxygarum_set_max_fps(60);  

  glutMainLoop();
  
  return 0;
}

