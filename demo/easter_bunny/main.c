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
#include <math.h>

int id;
int shade_mode = 1;
object3d_t *bunny = NULL;
object2d_t *load_screen = NULL;
int load_screen_id;

char text[100] = "FPS---";
char text2[100] = "FRAMETIME---";

void change_shade(void) {
  shade_mode++;
  shade_mode %= 2;
  oxygarum_set_shade_mode(id, shade_mode==0?GL_FLAT:GL_SMOOTH);
}

void anim(void) {
  sprintf(text, "FPS:%f", oxygarum_get_fps());
  sprintf(text2, "FRAMETIME:%f", oxygarum_get_frametime());
  
  float anim_sens = oxygarum_get_frametime()*0.1;
  oxygarum_rotate_object3d(id, 0, anim_sens, 0);
}

void wait_for_begin(void) {
  if(oxygarum_get_frametime() < 0) return;
  if(oxygarum_get_fps() > 0 && bunny != NULL) {
    oxygarum_remove_object2d(load_screen_id);
    oxygarum_animation_func(&anim);
  } else if(bunny == NULL) {
    GLuint shader = oxygarum_create_shader_from_file("data/shader.vert", "data/shader.frag");
    bunny = oxygarum_load_oxy3d_file("data/bunny.oxy3d");
    id = oxygarum_add_object3d(bunny, 0, -1.5, -5);
    oxygarum_object3d_use_glsl(id, shader);
    oxygarum_set_shade_mode(id, (shade_mode==0)?GL_FLAT:GL_SMOOTH);
  }
}

int main(int argc, char **argv) {
  oxygarum_set_resolution(800, 600);
  oxygarum_set_title("Oxygarum test");
  oxygarum_animation_func(&wait_for_begin);
  
  oxygarum_set_keyboard_event('s', &change_shade);  
  
  init_oxygarum(argc, argv);
  
  light_t light;
  light.ambient[0] = 0.8f; light.ambient[1] = 0.7f; light.ambient[2] = 0.9f; light.ambient[3] = 1.0f;
  light.diffuse[0] = 1.0f; light.diffuse[1] = 1.0f; light.diffuse[2] = 1.0f; light.diffuse[3] = 1.0f;
  light.specular[0] = 0.0f; light.specular[1] = 0.0f; light.specular[2] = 0.0f; light.specular[3] = 0.0f;
  light.pos[0] = 1.0f; light.pos[1] = 0.5f; light.pos[2] = -0.1f; light.pos[3] = 1.0f;
  light.gl_light = GL_LIGHT0;
  oxygarum_add_light(&light, LIGHT_POSITION_RELATIVE);
  
  glEnable(GL_CULL_FACE);  // Enable backface culling
  
  load_screen = oxygarum_load_oxy2d_file("../load_screen.oxy2d");
  load_screen_id = oxygarum_add_object2d(load_screen, 0, 0);
  oxygarum_set_max_fps(60);
  
  texture_t *font_tex = oxygarum_load_texture("../font.png", 1);
  font_t *font = oxygaurm_create_font(font_tex, 8, 8, '!', 14); 
  oxygarum_add_text(text, font, 0, 30);
  oxygarum_add_text(text2, font, 0, 0);    
  
  glutMainLoop();
  
  return 0;
}

