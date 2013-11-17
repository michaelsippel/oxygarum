//
// Particle System Test
//
// Copyright (C) 2013 Michael Sippel
// <micha.linuxfreak@gmail.com>
//

#include <oxygarum.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  oxygarum_set_resolution(800, 600);
  oxygarum_set_title("Oxygarum test");
  
  init_oxygarum();
  
  screen_t *screen = oxygarum_create_screen();
  scene_t *scene = oxygarum_create_scene();
  screen->scene = scene;  
    screen->camera->pos.x = 0;
  screen->camera->pos.y = 0;
  screen->camera->pos.z = -3;
  glPointSize(8);
  
  // create emitter
  particle_t borders[2];
  borders[0].pos.x = 0.1;
  borders[0].pos.y = 0;
  borders[0].pos.z = 0;
  borders[0].velocity.x = -0.001;
  borders[0].velocity.y =  0;
  borders[0].velocity.z = -0.001;
  borders[0].color.rgb.r = 1;
  borders[0].color.rgb.g = 0;
  borders[0].color.rgb.b = 0;
  borders[0].color.rgb.a = 1;
  borders[0].lifetime = 300;
  borders[0].size = 0.1;
  borders[1].pos.x = 0;
  borders[1].pos.y = 0;
  borders[1].pos.z = 0;
  borders[1].velocity.x = 0.001;
  borders[1].velocity.y = 0.001;
  borders[1].velocity.z = 0.001;
  borders[1].color.rgb.r = 1;
  borders[1].color.rgb.g = 1;
  borders[1].color.rgb.b = 0;
  borders[1].color.rgb.a = 1;
  borders[1].lifetime = 500;
  borders[1].size = 0.5;
  
  particle_emitter_t *emitter = oxygarum_create_emitter((void*)&borders);
  emitter->pos.x = 0;
  emitter->pos.y = 0;
  emitter->pos.z = 0;
  emitter->gravity_vector.x = 0;
  emitter->gravity_vector.y = 1;
  emitter->gravity_vector.z = 0;
  emitter->gravity_speed = 0.001;
  emitter->particles_per_emission = 300;
  emitter->emision_rate = 10;
  emitter->particle_counter = 2;
  emitter->texture = oxygarum_load_texture("texture.png", LINEAR, LINEAR, LINEAR);  
  
  oxygarum_add_emitter(scene, emitter);
  oxygarum_init_particle_shader();  

  // main loop
  while(1) {
    // update (calculate frametime, handle events, etc.)
    float frametime = oxygarum_update();
    
    // render
    oxygarum_render_screen(screen);

    // update
    oxygarum_update_particle_system(emitter, frametime);
  }
  
  return 0;
}

