/**
 *  src/core/event/handler.c
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
#include <SDL2/SDL.h>

void oxygarum_handle_sdl_event(SDL_Event *event) {  
  switch(event->type) {
    case SDL_KEYDOWN:
      oxygarum_handle_keyboard_event(event->key.keysym.sym);
      break;
    case SDL_KEYUP:
      oxygarum_handle_keyboard_event_up(event->key.keysym.sym);
      break;
    case SDL_QUIT:
      exit(0);
  }
}

