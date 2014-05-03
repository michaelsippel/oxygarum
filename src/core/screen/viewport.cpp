/**
 *  src/core/screen/viewport.cpp
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
#include <GL/glew.h>
#include <GL/gl.h>
#include "camera.h"

namespace oxygarum {

/**
 * Default constructor.
 * Creates a Viewport with default values
 */
Viewport::Viewport() {
	this->x = 0;
	this->y = 0;
	this->width = 800;
	this->height = 600;
	this->background = Color(0.0f, 0.0f, 0.0f, 1.0f);
}

/**
 * Adapted constructor.
 * Initalizes the object with special values
 */
Viewport::Viewport(int x_, int y_, int width_, int height_)
: x(x_), y(y_), width(width_), height(height_) {
	this->background = Color(0.0f, 0.0f, 0.0f, 1.0f);
}

Viewport::Viewport(int x_, int y_, int width_, int height_, Color background_)
: x(x_), y(y_), width(width_), height(height_), background(background_) {
}

/**
 * Destructor.
 * Deletes a Viewport object
 */
Viewport::~Viewport() {
}

void Viewport::use(void) {
	glViewport(this->x, this->y, this->width, this->height);

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(this->background.r, this->background.g, this->background.b, this->background.a);
}

};

