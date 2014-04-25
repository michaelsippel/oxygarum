//
// Particle System Test
//
// Copyright (C) 2013-2014 Michael Sippel
// <michamimosa@gmail.com>
//

#include <oxygarum.h>
#include <stdlib.h>

particle_emitter_t *emitter;

void increase_particles(void) {
  emitter->particle_counter *= 2;

  if(emitter->particle_counter > emitter->max_particles)
    emitter->particle_counter = emitter->max_particles;
}

void decrease_particles(void) {
  emitter->particle_counter /= 2;

  if(emitter->particle_counter < 1)
    emitter->particle_counter = 1;
}

int main(int argc, char **argv) {
  oxygarum_set_resolution(1300, 680);
  oxygarum_set_title("Oxygarum Particle-System Test");
  
  init_oxygarum();

  oxygarum_set_keyboard_event('1', &increase_particles);
  oxygarum_set_keyboard_event('2', &decrease_particles);

  screen_t *screen = oxygarum_create_screen();
  scene_t *scene = oxygarum_create_scene();
  screen->scene = scene;  
  screen->camera->pos.x = 0;
  screen->camera->pos.y = 0;
  screen->camera->pos.z = -5.0f;

  screen->width = screen->viewport.width = 1300;
  screen->height = screen->viewport.height = 680;

  glPointSize(20);  

  // create emitter
  particle_t borders[2];
  borders[0].pos.x = 0;
  borders[0].pos.y = 0;
  borders[0].pos.z = 0;
  borders[0].velocity.x = -0.01;
  borders[0].velocity.y = 0;
  borders[0].velocity.z = -0.01;
  borders[0].color.rgb.r = 1;
  borders[0].color.rgb.g = 0.0;
  borders[0].color.rgb.b = 0;
  borders[0].color.rgb.a = 1.0f;
  borders[0].lifetime = 2;
  borders[0].size = 0;
  borders[1].pos.x = 0.1;
  borders[1].pos.y = 0.1;
  borders[1].pos.z = 0.1;
  borders[1].velocity.x = 0.01;
  borders[1].velocity.y = 0;
  borders[1].velocity.z = 0.01;
  borders[1].color.rgb.r = 1;
  borders[1].color.rgb.g = 0.5;
  borders[1].color.rgb.b = 0;
  borders[1].color.rgb.a = 1.0f;
  borders[1].lifetime = 40;
  borders[1].size = 4;
  
  emitter = oxygarum_create_emitter(&borders, 10000);
  emitter->particle_counter = 100;
  emitter->pos.x = 0;
  emitter->pos.y = 0;
  emitter->pos.z = 0;
  emitter->gravity_vector.x = 0;
  emitter->gravity_vector.y = 1;
  emitter->gravity_vector.z = 0;
  emitter->gravity_speed = 0.002;
  emitter->emission_intensity = 300;
  emitter->emission_rate = 10;
  emitter->texture = oxygarum_load_texture_from_file("texture.png", NULL);
  
  oxygarum_group_add(scene->particle_emitters, emitter, NULL);
  oxygarum_init_particle_shader();  

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // main loop
  while(1) {
    // update (calculate frametime, handle events, etc.)
    float frametime = oxygarum_update();

    int mx, my;
    SDL_GetMouseState(&mx, &my);
    emitter->spawn_point.x = ((float)mx / screen->width) * 7.0f - 3.5f;
    emitter->spawn_point.y = ((screen->height-(float)my) / screen->height) * 4.0f - 2.0f;

    oxygarum_update_particle_system(emitter, frametime*0.1);

    // render
    oxygarum_render_screen(screen);
  }
  
  return 0;
}

