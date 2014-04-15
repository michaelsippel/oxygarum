//
// this simple demo will draw a rotating
// textured cube using the oxygarum 3D-Engine.
//
// Copyright (C) 2012-2013 Michael Sippel
// <michamimosa@gmail.com>
//

#include <oxygarum.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  oxygarum_set_resolution(960, 540);
  oxygarum_set_title("Oxygarum test");
  
  init_oxygarum();
  
  // load mesh and create object
  struct load_return *ret = oxygarum_load_oxy3d_file("data/scene.oxy3d", NULL);
  object3d_t *cube = oxygarum_create_object3d();
  cube->mesh = (mesh3d_t*) oxygarum_get_group_entry(ret->meshes, "cube")->element;
  
  object3d_t *wall = oxygarum_create_object3d();
  wall->mesh = (mesh3d_t*) oxygarum_get_group_entry(ret->meshes, "wall")->element;

  object3d_t *suzanne = oxygarum_create_object3d();
  suzanne->mesh = (mesh3d_t*) oxygarum_get_group_entry(ret->meshes, "suzanne")->element;

  // load shaders
  GLint vshader = oxygarum_create_shader_from_file(GL_VERTEX_SHADER, "../shader.vert");
  GLint fshader = oxygarum_create_shader_from_file(GL_FRAGMENT_SHADER, "../shader.frag");
  GLint program = glCreateProgram();
  glAttachShader(program, vshader);
  glAttachShader(program, fshader);
  glLinkProgram(program); 

  shader_t *shader = malloc(sizeof(shader_t));
  shader->program = program;  

  shader->inputs = oxygarum_create_group();

  cube->mesh->default_material->shader = shader;
  wall->mesh->default_material->shader = shader;
  suzanne->mesh->default_material->shader = shader;
  
  // setup scene
  screen_t *screen = oxygarum_create_screen();
  scene_t *scene = oxygarum_create_scene();
  screen->scene = scene;
  screen->camera->pos.x = -5.0f;
  screen->camera->pos.y = -2.0f;
  screen->camera->pos.z = -5.0f;
  screen->camera->rot.x = 0.0f;
  screen->camera->rot.y = -45.0f;
  screen->camera->rot.z = 0.0f;
  screen->width = screen->viewport.width = 960;
  screen->height = screen->viewport.height = 540;
  oxygarum_group_add(scene->objects3d, cube, NULL);
  oxygarum_group_add(scene->objects3d, wall, NULL);
  oxygarum_group_add(scene->objects3d, suzanne, NULL);

  light_t *light = oxygarum_create_light();
  light->ambient[0] = 0.1f; light->ambient[1] = 0.1f; light->ambient[2] = 0.1f; light->ambient[3] = 1.0f;
  light->diffuse[0] = 1.0f; light->diffuse[1] = 1.0f; light->diffuse[2] = 1.0f; light->diffuse[3] = 1.0f;
  light->specular[0] = 1.0f; light->specular[1] = 1.0f; light->specular[2] = 1.0f; light->specular[3] = 1.0f;
  light->r_pos[0] = 0.0f; light->r_pos[1] = 0.0f; light->r_pos[2] = 0.0f; light->r_pos[3] = 1.0f;
  light->pos.x = 0.0f; light->pos.y = 0.0f; light->pos.z = 0.0f;
  light->gl_light = GL_LIGHT0;
  glEnable(GL_LIGHT0);

  oxygarum_group_add(scene->lights, light, NULL);

  // main loop
  while(1) {
    // update (calculate frametime, handle events, etc.)
    float frametime = oxygarum_update();
    
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    light->pos.x = ((float)mx/screen->width)  * 20.0f;
    light->pos.y = 5.0f - ((float)my/screen->height) * 10.0f;
    
    // render
    oxygarum_render_screen(screen);
  }
  
  return 0;
}

