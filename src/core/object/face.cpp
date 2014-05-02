/**
 *  src/core/object/face.c
 *
 *  (C) Copyright 2012-2013 Michael Sippel
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
#include <string.h>

#include "vector.h"
#include "face.h"

namespace oxygarum {

Face::Face() {
	this->num_vertices = 0;
	this->vertices = NULL;
	this->texcoords = NULL;
	this->normal = Vector3D();
}

Face::Face(int num_vertices_, int *vertices_)
: num_vertices(num_vertices_), vertices(vertices_) {
	this->texcoords = NULL;
	this->normal = Vector3D();
}

Face::Face(int num_vertices_, int *vertices_, int *texcoords_)
: num_vertices(num_vertices_), vertices(vertices_), texcoords(texcoords_)  {
	this->normal = Vector3D();
}

Face::~Face() {
}

};

