//
// Particle System Test
//
// Copyright (C) 2013 Michael Sippel
// <micha.linuxfreak@gmail.com>
//

#include <oxygarum.h>

particle_emitter_t *emitter;

void anim(void) {
  oxygarum_update_all_particles(oxygarum_get_frametime());
}

int main(int argc, char **argv) {
  oxygarum_set_resolution(800, 600);
  oxygarum_set_title("Oxygarum test");
  oxygarum_animation_func(&anim);  
  
  init_oxygarum(argc, argv);
  glutFullScreen();
  
  particle_t *min = malloc(sizeof(particle_t));
  particle_t *max = malloc(sizeof(particle_t));
  
  min->velocity.x = -0.005;
  min->velocity.y =  0;
  min->velocity.z = -0.005;
  min->color.rgb.r = 1;
  min->color.rgb.g = 0;
  min->color.rgb.b = 0;
  min->color.rgb.a = 1;
  min->saturation_min = 0;
  min->saturation_max = 0.3;
  min->fade_in = 200;
  min->fade_out = 400;
  min->lifetime = 600;
  min->size = 0.1;
  
  max->velocity.x = 0.005;
  max->velocity.y = 0.005;
  max->velocity.z = 0.005;
  max->color.rgb.r = 1;
  max->color.rgb.g = 1;
  max->color.rgb.b = 0;
  max->color.rgb.a = 1;
  max->saturation_min = 0;
  max->saturation_max = 0.3;
  min->fade_in = 250;
  min->fade_out = 400;
  max->lifetime = 650;
  max->size = 0.5;
  
  emitter = malloc(sizeof(particle_emitter_t));
  emitter->mask_min = min;
  emitter->mask_max = max;
  
  emitter->pos.x = 0;
  emitter->pos.y = -3;
  emitter->pos.z = 0;
  emitter->gravity.x = 0;
  emitter->gravity.y = 3;
  emitter->gravity.z = 0;
  emitter->gravity_type = OXYGARUM_GRAVITY_TYPE_VERTEX;
  emitter->gravity_speed = 0.000003;
  emitter->num_particles_per_emission = 300;
  emitter->emision_rate = 10;
  emitter->texture = oxygarum_load_texture("texture.png", 1);  
  
  oxygarum_add_particle_system(emitter);  
  
  oxygarum_translate_camera_to(0, 0, -10);
  oxygarum_rotate_camera_to(0, 0, 0);
  
  glutMainLoop();
  
  return 0;
}

