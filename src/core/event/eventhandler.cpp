/**
 *  src/core/event/eventhandler.cpp
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
#include <stdint.h>
#include <stddef.h>
#include <SDL2/SDL.h>

#include "event.h"
#include "list.h"

namespace oxygarum
{

EventHandler::EventHandler()
{
	this->type = 0;
	this->function = NULL;
}

EventHandler::EventHandler(uint32_t type_, void (*function_)(SDL_Event*))
: type(type_), function(function_)
{
}

EventHandler::~EventHandler()
{
}


EventManager::EventManager()
{
	this->handlers = new List<EventHandler>();
}

EventManager::~EventManager()
{
}

void EventManager::poll_events(void)
{
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		ListEntry<EventHandler> *entry = this->handlers->getHead();
		int handled = 0;
		while(entry != NULL)
		{
			EventHandler *handler = entry->element;
			if(handler->type == e.type)
			{
				if(handler->function != NULL)
				{
					handler->function(&e);
					handled = 1;
				}
			}
			
			entry = entry->getNext();
		}
		
		if( (!handled) && e.type == SDL_QUIT)
		{
			exit(0);
		}
	}
}

ListEntry<EventHandler> *EventManager::register_handler(EventHandler *handler)
{
	return this->handlers->add(handler);
}

ListEntry<EventHandler> *EventManager::register_handler(uint32_t type, void (*function)(SDL_Event*))
{
	EventHandler *handler = new EventHandler(type, function);
	return this->handlers->add(handler);
}

};

