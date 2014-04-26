/**
 *  src/core/screen/screen.cpp
 *
 *  (C) Copyright 2013-2014 Michael Sippel
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
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include "screen.h"

extern SDL_Window *sdl_window;
extern SDL_Renderer *sdl_renderer;

/**
 * Default constructor.
 * Creates a Screen object with default values
 */
Screen::Screen() {
	this->scene = new Scene();
	this->camera = new Camera();
	this->viewport = Viewport(0, 0, 800, 600);
	this->background = Color(0.1f, 0.1f, 0.1f, 1.0f);
}

Screen::Screen(Scene *scene_)
: scene(scene_) {
	this->camera = new Camera();
	this->viewport = Viewport(0, 0, 800, 600);
	this->background = Color(0.1f, 0.1f, 0.1f, 1.0f);
}

Screen::Screen(Scene *scene_, Camera *camera_)
: scene(scene_), camera(camera_) {
	this->viewport = Viewport(0, 0, 800, 600);
	this->background = Color(0.1f, 0.1f, 0.1f, 1.0f);
}

Screen::Screen(Scene *scene_, Camera *camera_, Viewport viewport_)
: scene(scene_), camera(camera_), viewport(viewport_) {
	this->background = Color(0.1f, 0.1f, 0.1f, 1.0f);
}

/*
 * Destructor
 * Deletes a Screen object
 */
Screen::~Screen() {
}

/*
 * Renders the scene from camera view
 */
void Screen::render(void) {
	glViewport(this->viewport.x, this->viewport.y, this->viewport.width, this->viewport.height);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(this->background.r, this->background.g, this->background.b, this->background.a);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluPerspective(this->camera->fov, (GLfloat)this->viewport.width/(GLfloat)this->viewport.height, 1.0f, 1000.0f);

	glRotatef(this->camera->rotation.x, 1.0f,0.0f,0.0f);
	glRotatef(this->camera->rotation.y, 0.0f,1.0f,0.0f);
	glRotatef(this->camera->rotation.z, 0.0f,0.0f,1.0f);
	glTranslatef(this->camera->position.x, this->camera->position.y, this->camera->position.z);

	this->scene->render3D();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0, this->viewport.width, 0, this->viewport.height, -1, 1);

	glUseProgram(0);
	glPushAttrib(GL_ENABLE_BIT);
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		this->scene->render2D();
	glPopAttrib();

	glFlush();
	SDL_GL_SwapWindow(sdl_window);
}

