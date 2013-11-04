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
  
  // create emitter
  particle_t *min = malloc(sizeof(particle_t));
  particle_t *max = malloc(sizeof(particle_t));
  
  min->velocity.x = -0.001;
  min->velocity.y =  0;
  min->velocity.z = -0.001;
  min->color.rgb.r = 1;
  min->color.rgb.g = 0;
  min->color.rgb.b = 0;
  min->color.rgb.a = 1;
  min->saturation_min = 0;
  min->saturation_max = 0.3;
  min->fade_in = 200;
  min->fade_out = 400;
  min->lifetime = 300;
  min->size = 0.1;
  
  max->velocity.x = 0.001;
  max->velocity.y = 0.001;
  max->velocity.z = 0.001;
  max->color.rgb.r = 1;
  max->color.rgb.g = 1;
  max->color.rgb.b = 0;
  max->color.rgb.a = 1;
  max->saturation_min = 0;
  max->saturation_max = 0.3;
  min->fade_in = 250;
  min->fade_out = 400;
  max->lifetime = 500;
  max->size = 0.5;
  
  particle_emitter_t *emitter = malloc(sizeof(particle_emitter_t));
  emitter->mask_min = min;
  emitter->mask_max = max;
  
  emitter->pos.x = 0;
  emitter->pos.y = -1;
  emitter->pos.z = 0;
  emitter->gravity.x = 0;
  emitter->gravity.y = 1;
  emitter->gravity.z = 0;
  emitter->gravity_type = OXYGARUM_GRAVITY_TYPE_VERTEX;
  emitter->gravity_speed = 0.00001;
  emitter->num_particles_per_emission = 300;
  emitter->emision_rate = 10;
  emitter->texture = oxygarum_load_texture("texture.png", LINEAR, LINEAR, LINEAR);  
  
  oxygarum_add_emitter(scene, emitter);
  
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

