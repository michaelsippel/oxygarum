//
// this simple demo will draw a
// human exported from MakeHuman
//
// Copyright (C) 2013 Michael Sippel
// <michamimosa@gmail.com>
//

#include <oxygarum.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char text[100];
char text2[100];

int main(int argc, char **argv) {
  oxygarum_set_resolution(800, 600);
  oxygarum_set_title("Oxygarum test");
  
  init_oxygarum();
  glEnable(GL_LIGHTING);
  
  // create screen (with viewport, FOV, etc.)
  screen_t *screen = oxygarum_create_screen();
  
  // loading
  object3d_t *human = oxygarum_create_object3d();
  human->mesh = oxygarum_load_oxy3d_file("human.oxy3d");
  oxygarum_create_render_instance(human->mesh);
  human->shade_program = 0;
  human->pos.x = 0;
  human->pos.y = 0;
  human->pos.z = -20;
  human->status |= OBJECT_RENDER_VBO;
  
  texture_t *font_tex = oxygarum_load_texture("../font.png", 1);
  font_t *font = oxygarum_create_font(font_tex, 8, 8, '!', 14); 
  text_t *t1 = oxygarum_create_text(text, font, 0, 30);
  text_t *t2 = oxygarum_create_text(text2, font, 0, 0);
  
  // setup scene
  scene_t *scene = oxygarum_create_scene();
  oxygarum_add_object3d(scene, human);
  oxygarum_add_text(scene, t1);
  oxygarum_add_text(scene, t2);
  
  light_t light;
  light.ambient[0] = 1.0f; light.ambient[1] = 1.0f; light.ambient[2] = 1.0f; light.ambient[3] = 1.0f;
  light.diffuse[0] = 1.0f; light.diffuse[1] = 1.0f; light.diffuse[2] = 1.0f; light.diffuse[3] = 1.0f;
  light.specular[0] = 1.0f; light.specular[1] = 1.0f; light.specular[2] = 1.0f; light.specular[3] = 1.0f;
  light.r_pos[0] = 50.0f; light.r_pos[1] = 0.0f; light.r_pos[2] = 0.0f; light.r_pos[3] = 0.0f;
  light.gl_light = GL_LIGHT0;
  oxygarum_add_light(scene, &light);
  
  screen->scene = scene;
  
  // main loop
  while(1) {
    // update (calculate frametime, handle events, etc.)
    float frametime = oxygarum_update();
    
    // render
    oxygarum_render_screen(screen);
    
    // update
    sprintf(text, "FPS:%f", 1000/frametime);
    sprintf(text2, "FRAMETIME:%f", frametime);
    
    human->rot.y += frametime * 0.1;
  }
  
  return 0;
}

