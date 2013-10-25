//
// A pong-game using the
// oxygarum-engine
//
// Copyright (C) 2013 Michael Sippel
// <micha.linuxfreak@gmail.com>
//

#include <oxygarum.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

object3d_t *player = NULL;
object3d_t *ball = NULL;

#define DIRECTION_LEFT 0
#define DIRECTION_RIGHT 1
#define DIRECTION_FORWARD 0
#define DIRECTION_BACK 1

int direction_x = DIRECTION_LEFT;
int direction_y = DIRECTION_BACK;
float player1_loc = 0.4;

int dir = 0;

char text[100];
char text2[100];

void player1_up(void) {
  dir = -1;
}

void player1_down(void) {
  dir = 1;
}

void up(void) {
  dir = 0;
}

void anim(float frametime) {
  static game_over = 0;
  if(game_over) {
    return;
  }
  float anim_sens = frametime*0.005;
  
  player1_loc += dir * anim_sens * 0.5;
  
  player->pos.x = (player1_loc-0.5)*3;
  
  switch(direction_y) {
    case DIRECTION_FORWARD:
      ball->pos.z -= anim_sens;
      break;
    case DIRECTION_BACK:
      ball->pos.z += anim_sens;
      break;
  }
  switch(direction_x) {
    case DIRECTION_LEFT:
      ball->pos.x -= anim_sens;
      break;
    case DIRECTION_RIGHT:
      ball->pos.x += anim_sens;
      break;
  }
  
  if(ball->pos.x >= 3) {
    direction_x = DIRECTION_LEFT;
  } else if(ball->pos.x <= -3) {
    direction_x = DIRECTION_RIGHT;
  }
  
  if(ball->pos.z <= -3.5) {
    direction_y = DIRECTION_BACK;
  } else if(ball->pos.z >= -0.5) {
    if(ball->pos.x <= player->pos.x+0.8 && ball->pos.x >= player->pos.x-0.8) {
      direction_y = DIRECTION_FORWARD;
    } else {
      game_over = 1;
    }
  }
  
  sprintf(text, "FPS:%f", 1000/frametime);
  sprintf(text2, "FRAMETIME:%f", frametime);
}

int main(int argc, char **argv) {
  oxygarum_set_resolution(800, 600);
  oxygarum_set_title("Oxygarum test");
  
  oxygarum_set_keyboard_event('a', &player1_up);
  oxygarum_set_keyboard_event('d', &player1_down);
  oxygarum_set_keyboard_event_up('a', &up);
  oxygarum_set_keyboard_event_up('d', &up);  
  
  init_oxygarum();
  glEnable(GL_LIGHTING);
  
  // create screen
  screen_t *screen = oxygarum_create_screen();
  screen->camera->rot.x = 20;
  screen->camera->pos.y = -2;
  screen->camera->pos.z = -3;
  
  // loading
  player = oxygarum_create_object3d();
  player->mesh = oxygarum_load_oxy3d_file("player.oxy3d");
  
  ball = oxygarum_create_object3d();
  ball->mesh = oxygarum_load_oxy3d_file("ball.oxy3d");
  ball->pos.z = -1;
  
  texture_t *font_tex = oxygarum_load_texture("../font.png", NEAREST, NEAREST, NO_MIPMAP);
  font_t *font = oxygarum_create_font(font_tex, 8, 8, '!', 14); 
  text_t *t1 = oxygarum_create_text(text, font, 0, 30);
  text_t *t2 = oxygarum_create_text(text2, font, 0, 0);  
  
  // setup scene
  scene_t *scene = oxygarum_create_scene();
  oxygarum_add_object3d(scene, player);
  oxygarum_add_object3d(scene, ball);
  oxygarum_add_text(scene, t1);
  oxygarum_add_text(scene, t2);
  
  light_t light;
  light.ambient[0] = 0.8f; light.ambient[1] = 0.7f; light.ambient[2] = 0.9f; light.ambient[3] = 1.0f;
  light.diffuse[0] = 1.0f; light.diffuse[1] = 1.0f; light.diffuse[2] = 1.0f; light.diffuse[3] = 1.0f;
  light.specular[0] = 0.0f; light.specular[1] = 0.0f; light.specular[2] = 0.0f; light.specular[3] = 0.0f;
  light.r_pos[0] = 5.0f; light.r_pos[1] = 0.0f; light.r_pos[2] = 3.0f; light.r_pos[3] = 1.0f;
  light.gl_light = GL_LIGHT0;
  oxygarum_add_light(scene, &light);
  
  screen->scene = scene;
  
  while(1) {
    // update (calculate frametime, handle events, etc.)
    float frametime = oxygarum_update();
    
    // render
    oxygarum_render_screen(screen);
    
    // animate
    anim(frametime);
  }
  
  return 0;
}

