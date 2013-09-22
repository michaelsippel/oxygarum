/**
 *  include/event.h
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
#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <SDL/SDL.h>

void oxygarum_handle_sdl_event(SDL_Event *event);
void oxygarum_handle_keyboard_event(unsigned char key);
void oxygarum_handle_keyboard_event_up(unsigned char key);
void oxygarum_set_keyboard_event(unsigned char key, void (*handler)(void));
void oxygarum_set_keyboard_event_up(unsigned char key, void (*handler)(void));

#endif

