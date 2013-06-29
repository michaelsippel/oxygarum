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
vertex3d_t rot = {0,0,0};
vertex3d_t loc = {0,0,-2};

font_t *font;
char fps[100];
char frametime[100];
char name[100];
int name_id;

int dir = 0;
float speed = 0;

void left(void) {
  dir = -1;
}

void right(void) {
  dir = 1;
}

void forwards(void) {
  speed = SPEED;
}

void back(void) {
  speed = - SPEED;
}

void speed_up(void) {
  speed = 0;
}

void dir_up(void) {
  dir = 0;
}

void anim(void) {
  sprintf(fps, "%f FPS", oxygarum_get_fps());
  sprintf(frametime, "Frametime: %f", oxygarum_get_frametime());
  
  vertex2d_t feedback = oxygarum_get_object3d_feedback(suzanne_id);
  if(feedback.x == -1 && feedback.y == -1) {
    sprintf(name, "object not in view");
  } else {
    sprintf(name, "Suzanne");
  }
  oxygarum_update_text(name_id, NULL, NULL, feedback.x, feedback.y+100);
  
  float anim_sens = oxygarum_get_frametime()*0.1;
  
  rot.y += anim_sens * dir;
  
  loc.z += cos(rot.y*piover180) * speed * anim_sens;
  loc.x -= sin(rot.y*piover180) * speed * anim_sens;
  
  oxygarum_rotate_object3d(suzanne_id, 0, anim_sens, 0);
  
  oxygarum_rotate_camera_to(rot.x, rot.y, rot.z);
  oxygarum_translate_camera_to(loc.x, loc.y, loc.z);
}

int main(int argc, char **argv) {
  oxygarum_set_resolution(800, 600);
  oxygarum_set_fov(45);
  oxygarum_set_title("Oxygarum test");
  
  oxygarum_animation_func(&anim);
  oxygarum_set_keyboard_event('w', &forwards);
  oxygarum_set_keyboard_event('a', &left);
  oxygarum_set_keyboard_event('s', &back);
  oxygarum_set_keyboard_event('d', &right);
  oxygarum_set_keyboard_event_up('w', &speed_up);
  oxygarum_set_keyboard_event_up('a', &dir_up);
  oxygarum_set_keyboard_event_up('s', &speed_up);
  oxygarum_set_keyboard_event_up('d', &dir_up);  
  
  oxygarum_translate_camera_to(loc.x, loc.y, loc.z);
  oxygarum_rotate_camera_to(rot.x, rot.y, rot.z);
  
  init_oxygarum(argc, argv);
  
  oxygarum_set_light(GL_LIGHT1, ambient, diffuse, specular, position);
  //glEnable(GL_CULL_FACE);  // Enable backface culling
  
  object3d_t *world = oxygarum_load_oxy3d_file("world.oxy3d");
  object3d_t *suzanne = oxygarum_load_oxy3d_file("suzanne.oxy3d");
  world_id = oxygarum_add_object3d(world, 0, 0, 0);
  suzanne_id = oxygarum_add_object3d(suzanne, 0, 0, 0);
  oxygarum_set_shade_mode(suzanne_id, SHADE_SMOOTH);
  oxygarum_set_shade_mode(world_id, SHADE_SMOOTH);  

  texture_t *font_tex = oxygarum_load_texture("../font2.png");
  font = oxygaurm_create_font(font_tex, 16, 16, 0, 16);
  oxygarum_add_text(fps, font, 0, 30);
  oxygarum_add_text(frametime, font, 0, 0);
  name_id = oxygarum_add_text(name, font, 0, 0);
  color_t color;
  color.rgb = (color_st_t) {.r = 1, .g = 0, .b = 0, .a = 1};
  oxygarum_set_text_color(name_id, color);
  
  oxygarum_set_max_fps(60);
  
  glutMainLoop();
  
  return 0;
}

