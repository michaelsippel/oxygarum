/**
 *  src/core/material/color.cpp
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

#include <stdlib.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include "material.h"

namespace oxygarum {

Color::Color() {
	this->r = 1.0f;
	this->g = 1.0f;
	this->b = 1.0f;
	this->a = 1.0f;
}

Color::Color(float r_, float g_, float b_)
: r(r_), g(g_), b(b_) {
	this->a = 1.0f;
}

Color::Color(float r_, float g_, float b_, float a_)
: r(r_), g(g_), b(b_), a(a_) {
}

Color::~Color() {
}

void Color::use(void) {
	glColor4f(this->r, this->g, this->b, this->a);
}

};

