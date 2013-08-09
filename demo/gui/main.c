//
// this demo uses the gui functions
// from oxygarum
//
// Copyright (C) 2013 Michael Sippel
// <micha.linuxfreak@gmail.com>
//

#include <oxygarum.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  oxygarum_set_resolution(800, 600);
  oxygarum_set_title("Oxygarum test");
  
  init_oxygarum(argc, argv);
  
  texture_t *gui_tex = oxygarum_load_texture("gui.png");
  oxygarum_window_t *win = oxygarum_create_window(0.9, 0.9, gui_tex);  
  
  uv_t uv0[9] = {{.u = 0.0f, .v = 1.0f}, {.u = 0.5f, .v = 1.0f}, {.u = 0.5f, .v = 0.5f}, {.u = 0.0f, .v = 0.5f}};
  uv_t uv1[9] = {{.u = 1.0f, .v = 1.0f}, {.u = 0.5f, .v = 1.0f}, {.u = 0.5f, .v = 0.5f}, {.u = 1.0f, .v = 0.5f}};
  uv_t uv2[9] = {{.u = 0.0f, .v = 0.5f}, {.u = 0.0f, .v = 1.0f}, {.u = 0.5f, .v = 1.0f}, {.u = 0.5f, .v = 0.5f}};
  uv_t uv3[9] = {{.u = 0.5f, .v = 1.0f}, {.u = 0.5f, .v = 0.5f}, {.u = 1.0f, .v = 0.5f}, {.u = 1.0f, .v = 1.0f}};
  uv_t uv4[9] = {{.u = 0.0f, .v = 0.5f}, {.u = 1.0f, .v = 0.5f}, {.u = 1.0f, .v = 0.0f}, {.u = 0.0f, .v = 0.0f}};
  uv_t uv5[9] = {{.u = 1.0f, .v = 0.5f}, {.u = 1.0f, .v = 1.0f}, {.u = 0.5f, .v = 1.0f}, {.u = 0.5f, .v = 0.5f}};
  uv_t uv6[9] = {{.u = 0.5f, .v = 1.0f}, {.u = 0.5f, .v = 0.5f}, {.u = 0.0f, .v = 0.5f}, {.u = 0.0f, .v = 1.0f}};
  uv_t uv7[9] = {{.u = 0.5f, .v = 0.5f}, {.u = 1.0f, .v = 0.5f}, {.u = 1.0f, .v = 1.0f}, {.u = 0.5f, .v = 1.0f}};
  uv_t uv8[9] = {{.u = 0.5f, .v = 0.5f}, {.u = 0.0f, .v = 0.5f}, {.u = 0.0f, .v = 1.0f}, {.u = 0.5f, .v = 1.0f}};
  
  oxygarum_create_window_part(win, OXYGARUM_WINDOW_TOP_LEFT, uv0, 0.3f, 0.3f);
  oxygarum_create_window_part(win, OXYGARUM_WINDOW_TOP_CENTER, uv1, 0.3f, 0.3f);
  oxygarum_create_window_part(win, OXYGARUM_WINDOW_TOP_RIGHT, uv2, 0.3f, 0.3f);
  oxygarum_create_window_part(win, OXYGARUM_WINDOW_MIDDLE_LEFT, uv3, 0.3f, 0.3f);
  oxygarum_create_window_part(win, OXYGARUM_WINDOW_MIDDLE_CENTER, uv4, 0.3f, 0.3f);
  oxygarum_create_window_part(win, OXYGARUM_WINDOW_MIDDLE_RIGHT, uv5, 0.3f, 0.3f);
  oxygarum_create_window_part(win, OXYGARUM_WINDOW_BOTTOM_LEFT, uv6, 0.3f, 0.3f);
  oxygarum_create_window_part(win, OXYGARUM_WINDOW_BOTTOM_CENTER, uv7, 0.3f, 0.3f);
  oxygarum_create_window_part(win, OXYGARUM_WINDOW_BOTTOM_RIGHT, uv8, 0.3f, 0.3f);
  
  object2d_t *gui = oxygarum_create_window_obj(win);
  oxygarum_add_object2d(gui, 0, 0);
  
  glutMainLoop();
  
  return 0;
}
