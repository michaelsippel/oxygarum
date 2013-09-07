//
// Particle System Test
//
// Copyright (C) 2013 Michael Sippel
// <micha.linuxfreak@gmail.com>
//

#include <oxygarum.h>

particle_emiter_t *emiter;

void anim(void) {
  oxygarum_update_all_particles(oxygarum_get_frametime());
}

int main(int argc, char **argv) {
  oxygarum_set_resolution(800, 600);
  oxygarum_set_title("Oxygarum test");  
  oxygarum_animation_func(&anim);  
  
  init_oxygarum(argc, argv);
  
  emiter = malloc(sizeof(particle_emiter_t));
  emiter->pos.x = 0;
  emiter->pos.y = 0;
  emiter->pos.z = 0;
  emiter->gravity.x = 0;
  emiter->gravity.y = -0.00001;
  emiter->gravity.z = 0;
  
  vector3d_t velocity;
  velocity.x = 0.001;
  oxygarum_particle_vitalize(emiter, &velocity);
  oxygarum_add_particle_system(emiter);  
  
  oxygarum_translate_camera_to(0, 0, -10);
  oxygarum_rotate_camera_to(0, 0, 0);
  
  glutMainLoop();
  
  return 0;
}

