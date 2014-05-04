/**
 *  include/window.h
 *
 *  Copyright (C) 2014 Michael Sippel
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

#ifndef _WINDOW_H
#define _WINDOW_H

#include <SDL2/SDL.h>
#include "logger.h"

namespace oxygarum {

class SDLWindow {
	public:
		SDLWindow();
		SDLWindow(int width, int height);
		SDLWindow(char *title_, int width, int height);
		~SDLWindow();

		float update(void);

		int getWidth(void);
		int getHeight(void);

		static Logger *logger;

	private:
		void init(void);
		int width;
		int height;
		char *title;

		SDL_Window *sdl_window;
		SDL_GLContext *sdl_context;
};

};

#endif

