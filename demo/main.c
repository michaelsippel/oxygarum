#include <oxygarum.h>

int main(int argc, char **argv) {
  oxygarum_set_resolution(800, 400);
  oxygarum_set_title("Oxygarum test");
  oxygarum_set_flag(OXYGARUM_FULLSCREEN, 1);
  
  vertex_id v0 = oxygarum_add_vertex((vertex_t){-1, 1,-1});
  vertex_id v1 = oxygarum_add_vertex((vertex_t){-1,-1,-1});
  vertex_id v2 = oxygarum_add_vertex((vertex_t){ 1,-1,-1});
  vertex_id v3 = oxygarum_add_vertex((vertex_t){ 1, 1,-1});
  
  vertex_id v4 = oxygarum_add_vertex((vertex_t){-1, 1, 1});
  vertex_id v5 = oxygarum_add_vertex((vertex_t){-1,-1, 1});
  vertex_id v6 = oxygarum_add_vertex((vertex_t){ 1,-1, 1});
  vertex_id v7 = oxygarum_add_vertex((vertex_t){ 1, 1, 1});
  
  color_t color;
  color.rgb = (color_st_t){.r = 0.1, .g = 1, .b = 0.5};
  material_id material1 = oxygarum_create_material("grün", color);
  color_t color2;
  color2.rgb = (color_st_t){.r = 0, .g = 0, .b = 1};
  material_id material2 = oxygarum_create_material("blau", color2);
  
  face_t **faces = calloc(6, sizeof(face_t));
  
  vertex_id va0[] = {v0, v1, v2, v3};
  vertex_id va1[] = {v4, v5, v6, v7};
  vertex_id va2[] = {v0, v1, v5, v4};
  vertex_id va3[] = {v2, v3, v7, v6};
  vertex_id va4[] = {v0, v3, v7, v4};
  vertex_id va5[] = {v1, v2, v6, v5};
  
  faces[0] = (face_t*)oxygarum_create_face(4, (vertex_id*) &va0, material1); // Front
  faces[1] = (face_t*)oxygarum_create_face(4, (vertex_id*) &va1, material1); // Back
  faces[2] = (face_t*)oxygarum_create_face(4, (vertex_id*) &va2, material2); // Left
  faces[3] = (face_t*)oxygarum_create_face(4, (vertex_id*) &va3, material2); // Right
  faces[4] = (face_t*)oxygarum_create_face(4, (vertex_id*) &va4, material1); // Top
  faces[5] = (face_t*)oxygarum_create_face(4, (vertex_id*) &va5, material2); // Bottom
  
  object_t *cube = oxygarum_create_object(6, faces);
  oxygarum_add_object(cube);
  
  init_oxygarum(argc, argv);
  
  return 0;
}
