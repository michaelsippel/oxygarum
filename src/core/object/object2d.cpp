/**
 *  src/core/object/object2d.cpp
 *
 *  (C) Copyright 2012-2014 Michael Sippel
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include "object.h"
#include "transformation.h"

Object2D::Object2D() {
	this->position = Vector2D();
	this->rotation = 0.0f;

	this->mesh = NULL;
	this->material = NULL;

	this->status = OBJECT_VISIBLE | OBJECT_DEPTH_BUFFERING;
}

Object2D::Object2D(Transformation2D transform) {
	this->position = transform.position;
	this->rotation = transform.rotation;

	this->mesh = NULL;
	this->material = NULL;

	this->status = OBJECT_VISIBLE | OBJECT_DEPTH_BUFFERING;
}

Object2D::Object2D(Vector2D position_) {
	this->position = position_;
	this->rotation = 0.0f;

	this->mesh = NULL;
	this->material = NULL;

	this->status = OBJECT_VISIBLE | OBJECT_DEPTH_BUFFERING;
}

Object2D::Object2D(Vector2D position_, float rotation_) {
	this->position = position_;
	this->rotation = rotation_;
	this->mesh = NULL;
	this->material = NULL;

	this->status = OBJECT_VISIBLE | OBJECT_DEPTH_BUFFERING;
}

Object2D::~Object2D() {
}

void Object2D::setFlag(int flag) {
	this->status |= flag;
}

void Object2D::removeFlag(int flag) {
	this->status &= ~flag;
}

int Object2D::getStatus(void) {
	return status;
}

void Object2D::render(void) {/*TODO
  int i;
  for(i = 0; i < obj->mesh->face_counter; i++) {
    oxygarum_render_face2d(obj->mesh, obj->mesh->faces[i]);
  }*/
}

