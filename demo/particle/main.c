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
  
  emitter = malloc(sizeof(particle_emitter_t));
  emitter->pos.x = -2;
  emitter->pos.y = 2;
  emitter->pos.z = 0;
  emitter->gravity.x = 0;
  emitter->gravity.y = -0.000001;
  emitter->gravity.z = 0;
  emitter->num_particles_per_emision = 1;
  emitter->emision_rate = 100;
  
  oxygarum_add_particle_system(emitter);  
  
  oxygarum_translate_camera_to(0, 0, -10);
  oxygarum_rotate_camera_to(0, 0, 0);
  
  glutMainLoop();
  
  return 0;
}

