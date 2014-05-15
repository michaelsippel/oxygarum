/**
 *  include/event.h
 *
 *  Copyright (C) 2013-2014 Michael Sippel
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

/**
 * @author Michael Sippel <michamimosa@gmail.com>
 */

#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <SDL2/SDL.h>
#include "list.h"

namespace oxygarum
{

class EventHandler
{
	public:
		EventHandler();
		EventHandler(uint32_t type_, void (*handler_)(SDL_Event*));
		~EventHandler();

		uint32_t type;
		void (*function)(SDL_Event*);
};

class EventManager
{
	public:
		EventManager();
		~EventManager();

		List<EventHandler> *handlers;

		void poll_events(void);

		ListEntry<EventHandler> *register_handler(EventHandler *event);
		ListEntry<EventHandler> *register_handler(uint32_t type, void (*function)(SDL_Event*));
};

};

#endif

