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
	this->position = Vector3D();
	this->position = Vector3D();
}

Camera::Camera(Transformation3D transform) {
	this->position = transform.position;
	this->rotation = transform.rotation;
}

Camera::Camera(Vector3D position_)
: position(position_) {
	this->rotation = Vector3D();
}

Camera::Camera(Vector3D position_, Vector3D rotation_)
: position(position_), rotation(_rotation) {
}

/**
 * Destructor.
 * Deletes a Camera object
 */
Camera::~Camera() {
}

