/**
 *  src/core/screen/camera.cpp
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

#include "camera.h"

/**
 * Default constructor.
 * Creates a Camera class with default values
 */
Camera::Camera() {
	this->window = new SDLWindow();
	this->scene = new Scene();
	this->viewport = Viewport(0, 0, 800, 600);
	this->background = Color(0.1f, 0.1f, 0.1f, 1.0f);
	this->position = Vector3D();
	this->rotation = Vector3D();
	this->fov = 45.0f;
}

Camera::Camera(SDLWindow *window_)
: window(window_) {
	this->scene = new Scene();
	this->viewport = Viewport(0, 0, window->getWidth(), window->getHeight());
	this->background = Color(0.1f, 0.1f, 0.1f, 1.0f);
	this->position = Vector3D();
	this->rotation = Vector3D();
	this->fov = 45.0f;
}

Camera::Camera(SDLWindow *window_, Scene *scene_)
: window(window_), scene(scene_) {
	this->viewport = Viewport(0, 0, window->getWidth(), window->getHeight());
	this->background = Color(0.1f, 0.1f, 0.1f, 1.0f);
	this->position = Vector3D();
	this->rotation = Vector3D();
	this->fov = 45.0f;
}

Camera::Camera(SDLWindow *window_, Scene *scene_, Viewport viewport_)
: window(window_), scene(scene_), viewport(viewport_) {
	this->background = Color(0.1f, 0.1f, 0.1f, 1.0f);
	this->position = Vector3D();
	this->rotation = Vector3D();
	this->fov = 45.0f;
}

Camera::Camera(SDLWindow *window_, Transformation3D transform)
: window(window_) {
	this->position = transform.position;
	this->rotation = transform.rotation;
	this->background = Color(0.1f, 0.1f, 0.1f, 1.0f);
	this->fov = 45.0f;
}

Camera::Camera(SDLWindow *window_, Vector3D position_)
: window(window_) {
	this->position = position_;
	this->background = Color(0.1f, 0.1f, 0.1f, 1.0f);
	this->rotation = Vector3D();
	this->fov = 45.0f;
}

Camera::Camera(SDLWindow *window_, Vector3D position_, Vector3D rotation_)
: window(window_) {
	this->position = position_;
	this->rotation = rotation_;
	this->background = Color(0.1f, 0.1f, 0.1f, 1.0f);
	this->fov = 45.0f;
}

Camera::Camera(SDLWindow *window_, Vector3D position_, Vector3D rotation_, float fov_)
: window(window_), fov(fov_) {
	this->background = Color(0.1f, 0.1f, 0.1f, 1.0f);
	this->position = position_;
	this->rotation = rotation_;
}

/**
 * Destructor.
 * Deletes a Camera object
 */
Camera::~Camera() {
}

/*
 * Renders the scene from camera view
 */
void Camera::render(void) {
	this->viewport.use();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(this->background.r, this->background.g, this->background.b, this->background.a);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluPerspective(this->fov, (GLfloat)this->viewport.width/(GLfloat)this->viewport.height, 1.0f, 1000.0f);

	this->useTransformation();

	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
		glVertex3f( 0.0f,  1.0f, 0.0f);
		glVertex3f( 1.0f, -1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
	glEnd();

/*
	//this->scene->render3D();

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

		//this->scene->render2D();
	glPopAttrib();
*/
	glFlush();
}

