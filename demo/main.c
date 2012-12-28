#include <cliter.h>

int main(int argc, char **argv) {
  cliter_set_resolution(800, 400);
  cliter_set_title("Cliter test");
  cliter_set_flag(CLITER_FULLSCREEN, 0);
  init_cliter(argc, argv);
  
  return 0;
}
