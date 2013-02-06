#include <cliter.h>

int main(int argc, char **argv) {
  cliter_set_resolution(800, 400);
  cliter_set_title("Cliter test");
  cliter_set_flag(CLITER_FULLSCREEN, 0);
  
  vertex_id v0 = cliter_add_vertex((vertex_t){-1, 1,-1});
  vertex_id v1 = cliter_add_vertex((vertex_t){-1,-1,-1});
  vertex_id v2 = cliter_add_vertex((vertex_t){ 1,-1,-1});
  vertex_id v3 = cliter_add_vertex((vertex_t){ 1, 1,-1});
  
  vertex_id v4 = cliter_add_vertex((vertex_t){-1, 1, 1});
  vertex_id v5 = cliter_add_vertex((vertex_t){-1,-1, 1});
  vertex_id v6 = cliter_add_vertex((vertex_t){ 1,-1, 1});
  vertex_id v7 = cliter_add_vertex((vertex_t){ 1, 1, 1});
  
  object_t *cube = cliter_create_object(1,
    (face_t*) {
      cliter_create_face(4, (vertex_id*) {v0, v1, v2, v3}), // Front
      cliter_create_face(4, (vertex_id*) {v4, v5, v6, v7}), // Back
      cliter_create_face(4, (vertex_id*) {v0, v1, v5, v4}), // Left
      cliter_create_face(4, (vertex_id*) {v2, v3, v6, v7}), // Right
      cliter_create_face(4, (vertex_id*) {v0, v3, v7, v4}), // Top
      cliter_create_face(4, (vertex_id*) {v1, v2, v6, v5})  // Bottom
    }
  );
  
  cliter_add_object(cube, (vertex_t){0,0,0});
  
  init_cliter(argc, argv);
  
  return 0;
}
