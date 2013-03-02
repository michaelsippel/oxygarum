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
  color.rgb = (color_st_t){.r = 0xff, .g = 0x00, .b = 0xff};
  material_id material = oxygarum_create_material("material", color);
  
  face_t faces[] = {
      oxygarum_create_face(4, (vertex_id*) {v0, v1, v2, v3}, material), // Front
      oxygarum_create_face(4, (vertex_id*) {v4, v5, v6, v7}, material), // Back
      oxygarum_create_face(4, (vertex_id*) {v0, v1, v5, v4}, material), // Left
      oxygarum_create_face(4, (vertex_id*) {v2, v3, v6, v7}, material), // Right
      oxygarum_create_face(4, (vertex_id*) {v0, v3, v7, v4}, material), // Top
      oxygarum_create_face(4, (vertex_id*) {v1, v2, v6, v5}, material)  // Bottom
  };
  
  object_t cube = oxygarum_create_object(6, &faces);
  oxygarum_add_object(&cube);
  
  init_oxygarum(argc, argv);
  
  return 0;
}
