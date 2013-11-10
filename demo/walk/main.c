//
// In this demo you can walk through a
// little world using the oxygarum 3D-Engine.
//
// Copyright (C) 2013 Michael Sippel
// <michamimosa@gmail.com>
//

#include <oxygarum.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define piover180 0.0174532925f
#define SPEED 0.2

char text_fps[100];
char text_frametime[100];
char text_name[100];

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

int main(int argc, char **argv) {
  oxygarum_set_resolution(800, 600);
  oxygarum_set_title("Oxygarum test");
  
  oxygarum_set_keyboard_event('w', &forwards);
  oxygarum_set_keyboard_event('a', &left);
  oxygarum_set_keyboard_event('s', &back);
  oxygarum_set_keyboard_event('d', &right);
  oxygarum_set_keyboard_event_up('w', &speed_up);
  oxygarum_set_keyboard_event_up('a', &dir_up);
  oxygarum_set_keyboard_event_up('s', &speed_up);
  oxygarum_set_keyboard_event_up('d', &dir_up);  
  
  init_oxygarum();
  glEnable(GL_LIGHTING);
  
  // create screen
  screen_t *screen = oxygarum_create_screen();
  
  // loading
  GLuint vert = oxygarum_create_shader_from_file(GL_VERTEX_SHADER, "../shader.vert");
  GLuint frag = oxygarum_create_shader_from_file(GL_FRAGMENT_SHADER, "../shader.frag");
  GLuint program = glCreateProgram();
  glAttachShader(program, vert);
  glAttachShader(program, frag);
  glLinkProgram(program);
  
  object3d_t *world = oxygarum_create_object3d();
  object3d_t *suzanne = oxygarum_create_object3d();
  world->mesh = oxygarum_load_oxy3d_file("data/world.oxy3d");
  suzanne->mesh = oxygarum_load_oxy3d_file("data/suzanne.oxy3d");
  oxygarum_create_render_instance(world->mesh);
  oxygarum_create_render_instance(suzanne->mesh);
  world->shade_program = program;
  suzanne->shade_program = program;
  world->status |= OBJECT_RENDER_VBO;
  suzanne->status |= OBJECT_RENDER_VBO;
  world->pos.y = -1.5;
  
  texture_t *font_tex = oxygarum_load_texture("../font2.png", NEAREST, NEAREST, NO_MIPMAP);
  font_t *font = oxygarum_create_font(font_tex, 16, 16, 0, 16);
  text_t *t1 = oxygarum_create_text(text_fps, font, 0, 30);
  text_t *t2 = oxygarum_create_text(text_frametime, font, 0, 0);
  text_t *t3 = oxygarum_create_text(text_name, font, 0, 0);
  t3->color.rgb = (color_st_t) {.r = 1, .g = 0, .b = 0, .a = 1};
  
  // setup scene
  scene_t *scene = oxygarum_create_scene();
  oxygarum_add_object3d(scene, world);
  oxygarum_add_object3d(scene, suzanne);
  oxygarum_add_text(scene, t1);
  oxygarum_add_text(scene, t2);
  oxygarum_add_text(scene, t3);
  
  screen->camera->pos.x = 0;
  screen->camera->pos.y = 0;
  screen->camera->pos.z = -3;  
  
  light_t light;
  light.ambient[0] = 1.0f; light.ambient[1] = 1.0f; light.ambient[2] = 1.0f; light.ambient[3] = 1.0f;
  light.diffuse[0] = 1.0f; light.diffuse[1] = 1.0f; light.diffuse[2] = 1.0f; light.diffuse[3] = 1.0f;
  light.specular[0] = 1.0f; light.specular[1] = 1.0f; light.specular[2] = 1.0f; light.specular[3] = 1.0f;
  light.r_pos[0] = 0.0f; light.r_pos[1] = 0.0f; light.r_pos[2] = 10.0f; light.r_pos[3] = 0.0f;
  light.gl_light = GL_LIGHT0;
  oxygarum_add_light(scene, &light);
  
  screen->scene = scene;

  // main loop
  while(1) {
    // update (calculate frametime, handle events, etc.)
    float frametime = oxygarum_update();
    
    // render
    oxygarum_render_screen(screen);
    
    // animate
    sprintf(text_fps, "%f FPS", 1000/frametime);
    sprintf(text_frametime, "Frametime: %f", frametime);
    
    if(suzanne->feedback.x == -1 && suzanne->feedback.y == -1) {
      sprintf(text_name, "object not in view");
    } else {
      sprintf(text_name, "Suzanne");
    }
    t3->pos.x = suzanne->feedback.x;
    t3->pos.y = suzanne->feedback.y+100;
    
    float anim_sens = frametime*0.1;
    
    screen->camera->rot.y += anim_sens * dir;
    
    screen->camera->pos.z += cos(screen->camera->rot.y*piover180) * speed * anim_sens;
    screen->camera->pos.x -= sin(screen->camera->rot.y*piover180) * speed * anim_sens;
    
    suzanne->rot.y += anim_sens;
  }
  
  return 0;
}

