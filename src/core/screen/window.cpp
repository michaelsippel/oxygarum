/**
 *  src/core/screen/window.cpp
 *
 *  (C) Copyright 2014 Michael Sippel
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

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "logger.h"
#include "window.h"

namespace oxygarum
{

SDLWindow::SDLWindow()
{
    this->width = 800;
    this->height = 600;
    this->init();
}

SDLWindow::SDLWindow(int width_, int height_)
    : width(width_), height(height_)
{
    this->init();
}

SDLWindow::SDLWindow(char *title_, int width_, int height_)
    : title(title_), width(width_), height(height_)
{
    this->init();
}

SDLWindow::~SDLWindow()
{
}

void SDLWindow::init(void)
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        this->logger->log(ERROR, "SDL init failed!");
        return;
    }

    this->sdl_window = SDL_CreateWindow(title, 0, 0, width, height, SDL_WINDOW_OPENGL);
    if(this->sdl_window == NULL)
    {
        this->logger->log(ERROR, "SDL create window failed!");
        return;
    }

    this->sdl_context = (SDL_GLContext*) SDL_GL_CreateContext(this->sdl_window);
    if(this->sdl_context == NULL)
    {
        this->logger->log(ERROR, "OpenGL context creation failed!");
        return;
    }

    if(glewInit() != GLEW_OK)
    {
        this->logger->log(ERROR, "glewInit failed!");
    }

    this->eventmgr = new EventManager();
    this->logger->log(INFO, "window created");
}

float SDLWindow::update(void)
{
    // calc frametime
    static float time_prev = 0;
    float time_cur = (float) SDL_GetTicks();

    float frametime = time_cur - time_prev;
    time_prev = time_cur;

    this->swap();

    return frametime;
}

void SDLWindow::poll_events(void)
{
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        int success = this->eventmgr->handle_event(e.type, 1, (void**) &e);
        if( !(success == 0) && e.type == SDL_QUIT)
        {
            exit(0);
        }
    }
}

void SDLWindow::swap(void)
{
    SDL_GL_SwapWindow(this->sdl_window);
}

int SDLWindow::getWidth(void)
{
    return this->width;
}

int SDLWindow::getHeight(void)
{
    return this->height;
}

};

