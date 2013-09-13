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

int player1_id, player2_id, playground_id, ball_id;
int shade_mode = 1;
object3d_t *player = NULL;
object3d_t *ball = NULL;
object2d_t *load_screen = NULL;
int load_screen_id;

float player1_loc = 0.5;
float player1_x = 0;
float player2_loc = 0.5;

#define DIRECTION_LEFT 0
#define DIRECTION_RIGHT 1
#define DIRECTION_FORWARD 0
#define DIRECTION_BACK 1

float ball_x = 0, ball_y = -1;
int direction_x = DIRECTION_LEFT;
int direction_y = DIRECTION_BACK;

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

void anim(void) {
  static game_over = 0;
  if(game_over) {
    return;
  }
  float anim_sens = oxygarum_get_frametime()*0.005;

  player1_loc += dir * anim_sens * 0.5;

  player1_x = (player1_loc-0.5)*3;
  oxygarum_translate_object3d_to(player1_id, player1_x, 0, 0);
  
  switch(direction_y) {
    case DIRECTION_FORWARD:
      ball_y -= anim_sens;
      break;
    case DIRECTION_BACK:
      ball_y += anim_sens;
      break;
  }
  switch(direction_x) {
    case DIRECTION_LEFT:
      ball_x -= anim_sens;
      break;
    case DIRECTION_RIGHT:
      ball_x += anim_sens;
      break;
  }
  
  if(ball_x >= 3) {
    direction_x = DIRECTION_LEFT;
  } else if(ball_x <= -3) {
    direction_x = DIRECTION_RIGHT;
  }
  
  if(ball_y <= -3.5) {
    direction_y = DIRECTION_BACK;
  } else if(ball_y >= -0.5) {
    if(ball_x <= player1_x+0.8 && ball_x >= player1_x-0.8) {
      direction_y = DIRECTION_FORWARD;
    } else {
      load_screen->material->textures[0] = oxygarum_load_texture("game_over.png",1);
      oxygarum_enable_object2d_status(load_screen_id, OBJECT_VISIBLE);
      game_over = 1;
    }
  }
  
  oxygarum_translate_object3d_to(ball_id, ball_x, 0, ball_y);

  sprintf(text, "FPS:%f", oxygarum_get_fps());
  sprintf(text2, "FRAMETIME:%f", oxygarum_get_frametime());
}

void wait_for_begin(void) {
  if(oxygarum_get_fps() > 0 && player != NULL && ball != NULL) {
    oxygarum_disable_object2d_status(load_screen_id, OBJECT_VISIBLE);
    oxygarum_animation_func(&anim);
  } else if(player == NULL) {
    player = oxygarum_load_oxy3d_file("player.oxy3d");
    player1_id = oxygarum_add_object3d(player, 0, 0, 0);
    oxygarum_set_shade_mode(player1_id, GL_SMOOTH);
  } else if(ball == NULL) {
    ball = oxygarum_load_oxy3d_file("ball.oxy3d");
    ball_id = oxygarum_add_object3d(ball, 0, 0, -4);
    oxygarum_set_shade_mode(ball_id, GL_SMOOTH);
  }
}

int main(int argc, char **argv) {
  oxygarum_set_resolution(800, 600);
  oxygarum_set_title("Oxygarum test");
  oxygarum_animation_func(&wait_for_begin);
  
  oxygarum_set_keyboard_event('a', &player1_up);
  oxygarum_set_keyboard_event('d', &player1_down);
  oxygarum_set_keyboard_event_up('a', &up);
  oxygarum_set_keyboard_event_up('d', &up);  
  
  init_oxygarum();
  
  light_t light;
  light.ambient[0] = 0.8f; light.ambient[1] = 0.7f; light.ambient[2] = 0.9f; light.ambient[3] = 1.0f;
  light.diffuse[0] = 1.0f; light.diffuse[1] = 1.0f; light.diffuse[2] = 1.0f; light.diffuse[3] = 1.0f;
  light.specular[0] = 0.0f; light.specular[1] = 0.0f; light.specular[2] = 0.0f; light.specular[3] = 0.0f;
  light.pos[0] = 5.0f; light.pos[1] = 0.0f; light.pos[2] = 3.0f; light.pos[3] = 1.0f;
  light.gl_light = GL_LIGHT0;
  oxygarum_add_light(&light, LIGHT_POSITION_ABSOLUTE);
  
  glEnable(GL_CULL_FACE);  // Enable backface culling  
  
  oxygarum_rotate_camera_to(20, 0, 0);
  oxygarum_translate_camera_to(0, -2, -3);  
  
  load_screen = oxygarum_load_oxy2d_file("../load_screen.oxy2d");
  load_screen_id = oxygarum_add_object2d(load_screen, 0, 0);
  oxygarum_set_max_fps(60);
  
  texture_t *font_tex = oxygarum_load_texture("../font.png",1);
  font_t *font = oxygaurm_create_font(font_tex, 8, 8, '!', 14); 
  oxygarum_add_text(text, font, 0, 30);
  oxygarum_add_text(text2, font, 0, 0);   

  oxygarum_start_render();
  
  return 0;
}

