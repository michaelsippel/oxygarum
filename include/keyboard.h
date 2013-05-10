/**
 *  include/keyboard.h
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

#define MOUSE_ACTIVE_MOTION  0x0
#define MOUSE_PASSIVE_MOTION 0x1
#define MOUSE_CLICK          0x2

void oxygarum_handle_keyboard_event(unsigned char key, int x, int y);
void oxygarum_set_keyborad_event(unsigned char key, void (*handler)(void));
void oxygarum_set_mouse_func(int type, void *handler);

#endif

