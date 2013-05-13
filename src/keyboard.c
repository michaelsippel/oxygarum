/**
 *  src/keyboard.c
 *
 *  (C) Copyright 2013 Michael Sippel
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdint.h>
#include <stddef.h>
#include "keyboard.h"

static void (*kbd_events[256]) (void);

void oxygarum_handle_keyboard_event(unsigned char key, int x, int y) {
  usleep(100);
  
  if(kbd_events[key] != NULL) {
    kbd_events[key]();
  }
}

void oxygarum_set_keyboard_event(unsigned char key, void (*handler)(void)) {
  kbd_events[key] = handler;
}

void oxygarum_set_mouse_func(int type, void *handler) {
/*
  switch(type) {
    case MOUSE_PASSIVE_MOTION:
      glutPassiveMotionFunc(handler);
      break;
    case MOUSE_ACTIVE_MOTION:
      glutMotionFunc(handler);
      break;
    case MOUSE_CLICK:
      glutMouseFunc(handler);
      break;
  }
  */
}

