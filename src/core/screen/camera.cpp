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

namespace oxygarum
{

/**
 * Default constructor.
 * Creates a Camera class with default values
 */
Camera::Camera()
{
    Transformation3D();
    this->window = new SDLWindow();
    this->scene = new Scene();
    this->viewport = Viewport(0, 0, window->getWidth(), window->getHeight());
    this->fov = 45.0f;
}

Camera::Camera(SDLWindow *window_)
    : window(window_)
{
    Transformation3D();
    this->scene = new Scene();
    this->viewport = Viewport(0, 0, window->getWidth(), window->getHeight());
    this->fov = 45.0f;
}

Camera::Camera(SDLWindow *window_, Scene *scene_)
    : window(window_), scene(scene_)
{
    Transformation3D();
    this->viewport = Viewport(0, 0, window->getWidth(), window->getHeight());
    this->fov = 45.0f;
}

Camera::Camera(SDLWindow *window_, Scene *scene_, Viewport viewport_)
    : window(window_), scene(scene_), viewport(viewport_)
{
    Transformation3D();
    this->fov = 45.0f;
}

Camera::Camera(SDLWindow *window_, Transformation3D transform)
    : window(window_)
{
    Transformation3D(transform.position, transform.rotation, transform.scaling);
    this->scene = new Scene();
    this->viewport = Viewport(0, 0, window->getWidth(), window->getHeight());
    this->fov = 45.0f;
}

Camera::Camera(SDLWindow *window_, Vector3D position_)
    : window(window_)
{
    Transformation3D(position_, Vector3D());
    this->scene = new Scene();
    this->viewport = Viewport(0, 0, window->getWidth(), window->getHeight());
    this->fov = 45.0f;
}

Camera::Camera(SDLWindow *window_, Vector3D position_, Vector3D rotation_)
    : window(window_)
{
    Transformation3D(position_, rotation_);
    this->scene = new Scene();
    this->viewport = Viewport(0, 0, window->getWidth(), window->getHeight());
    this->fov = 45.0f;
}

Camera::Camera(SDLWindow *window_, Vector3D position_, Vector3D rotation_, float fov_)
    : window(window_), fov(fov_)
{
    Transformation3D(position_, rotation_);
    this->scene = new Scene();
    this->viewport = Viewport(0, 0, window->getWidth(), window->getHeight());
}

/**
 * Destructor.
 * Deletes a Camera object
 */
Camera::~Camera()
{
}

/*
 * Set all matrices
 */
void Camera::use(void)
{
    this->viewport.use();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluPerspective(this->fov, (GLfloat)this->viewport.width/(GLfloat)this->viewport.height, 1.0f, 1000.0f);

    this->useTransformation();
}

/*
 * Renders the scene from camera view
 */
void Camera::render(void)
{
    this->use();

    if(this->scene != NULL) this->scene->render3D();
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

};

