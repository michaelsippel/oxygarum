/**
 *  src/core/vector/transformation2d.cpp
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

#include "transformation.h"

Transformation2D::Transformation2D() {
	this->position = Vector2D();
	this->rotation = 0.0f;
	this->scaling = 1.0f;
}

Transformation2D::Transformation2D(Vector2D position_, Vector2D rotation_)
: position(position_), rotation(rotation_) {
	this->scaling = 1.0f;
}

Transformation2D::Transformation2D(Vector2D position_, Vector2D rotation_, float scaling_)
: position(position_), rotation(rotation_), scaling(scaling_) {
}

Transformation2D::~Transformation2D() {
}

void Transformation2D::setPosition(Vertex2D position_) {
	this->position = position_;
}

void Transformation2D::setPosition(float x, float y) {
	this->position = Vector2D(x, y);
}

void Transformation2D::setRotation(float rotation_) {
	this->rotation = rotation_;
}

void Transformation2D::setScaling(Vector2D scaling_) {
	this->scaling = scaling_;
}

void Transformation2D::setScaling(float x_) {
	this->scaling = Vector2D(x_, x_);
}

void Transformation2D::move(Vector2D position_) {
	this->position.add(position_);
}

void Transformation2D::rotate(float rotation_) {
	this->rotation += rotation_;
}

void Transformation2D::scale(Vector2D scaling_) {
	this->scaling.add(scaling_);
}

void Transformation2D::scale(float x_) {
	this->scaling.add(Vector2D(x, x_));
}

void Transformation3D::useTransformation(void) {
	glRotatef(this->rotation, 0.0f, 0.0f, 1.0f);
	glScalef(this->scaling.x, this->scaling.y, 1.0f);
	glTranslatef(this->position.x, this->position.y, 0.0f);
}

