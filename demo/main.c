//
// this simple demo will draw a rotating
// textured cube using the oxygarum 3D-Engine.
//
// Copyright (C) 2012-2013 Michael Sippel
// <micha.linuxfreak@gmail.com>
//

#include <oxygarum.h>
#include <stdio.h>

int main(int argc, char **argv) {
  oxygarum_set_resolution(800, 600);
  oxygarum_set_title("Oxygarum test");
  oxygarum_set_flag(OXYGARUM_FULLSCREEN, 0);
  init_oxygarum(argc, argv);  

  vertex_id v0 = oxygarum_add_vertex((vertex_t){-1, 1,-1});
  vertex_id v1 = oxygarum_add_vertex((vertex_t){-1,-1,-1});
  vertex_id v2 = oxygarum_add_vertex((vertex_t){ 1,-1,-1});
  vertex_id v3 = oxygarum_add_vertex((vertex_t){ 1, 1,-1});
  
  vertex_id v4 = oxygarum_add_vertex((vertex_t){-1, 1, 1});
  vertex_id v5 = oxygarum_add_vertex((vertex_t){-1,-1, 1});
  vertex_id v6 = oxygarum_add_vertex((vertex_t){ 1,-1, 1});
  vertex_id v7 = oxygarum_add_vertex((vertex_t){ 1, 1, 1});
  
  material_t *material = oxygarum_create_material("material");
  material->texture = oxygarum_load_texture("texture.png");
  material->color.rgb = (color_st_t) {.r = 1, .g = 1, .b = 1};
  if(! material->texture) {
    printf("Fehler beim Laden der Textur!\n");
    exit(0);
  }
  
  uv_t *uvmap = calloc(4, sizeof(uv_t));
  uvmap[0] = (uv_t){0,1};
  uvmap[1] = (uv_t){0,0};
  uvmap[2] = (uv_t){1,0};
  uvmap[3] = (uv_t){1,1};
  
  vertex_id va0[] = {v0, v1, v2, v3};
  vertex_id va1[] = {v4, v5, v6, v7};
  vertex_id va2[] = {v0, v1, v5, v4};
  vertex_id va3[] = {v2, v3, v7, v6};
  vertex_id va4[] = {v0, v3, v7, v4};
  vertex_id va5[] = {v1, v2, v6, v5};
  
  face_t **faces = calloc(6, sizeof(face_t));
  faces[0] = oxygarum_create_face(4, (vertex_id*) &va0, material, uvmap); // Front
  faces[1] = oxygarum_create_face(4, (vertex_id*) &va1, material, uvmap); // Back
  faces[2] = oxygarum_create_face(4, (vertex_id*) &va2, material, uvmap); // Left
  faces[3] = oxygarum_create_face(4, (vertex_id*) &va3, material, uvmap); // Right
  faces[4] = oxygarum_create_face(4, (vertex_id*) &va4, material, uvmap); // Top
  faces[5] = oxygarum_create_face(4, (vertex_id*) &va5, material, uvmap); // Bottom
  
  object_t *cube = oxygarum_create_object(6, faces);
  oxygarum_add_object(cube);
  
  glutMainLoop();  
  
  return 0;
}

