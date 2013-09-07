//
// Particle System Test
//
// Copyright (C) 2013 Michael Sippel
// <micha.linuxfreak@gmail.com>
//

#include <oxygarum.h>

int main(int argc, char **argv) {
  oxygarum_set_resolution(800, 600);
  oxygarum_set_title("Oxygarum test");
  
  init_oxygarum(argc, argv);
  
  particle_t *particle = malloc(sizeof(particle_t));
  particle->pos.x = 0;
  particle->pos.y = 0;
  particle->pos.z = 0;
  particle->size = 1;
  particle->saturation = 1;
  particle->color.rgb.r = 1;
  particle->color.rgb.g = 0;
  particle->color.rgb.b = 0;
  particle->color.rgb.a = 1;
  
  oxygarum_add_particle(particle); 
  
  oxygarum_translate_camera_to(0, 0, -10);
  oxygarum_rotate_camera_to(0, 0, 0);  
  
  glutMainLoop();
  
  return 0;
}

