/**
 *  src/core/vector/transformation3d.cpp
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

Transformation3D::Transformation3D() {
	this->position = Vector3D();
	this->rotation = Vector3D();
	this->scaling = Vector3D(1.0f, 1.0f, 1.0f);
}

Transformation3D::Transformation3D(Vector3D position_, Vector3D rotation_)
: position(position_), rotation(rotation_) {
	this->scaling = Vector3D(1.0f, 1.0f, 1.0f);
}

Transformation3D::Transformation3D(Vector3D position_, Vector3D rotation_, float scaling_)
: position(position_), rotation(rotation_), scaling(scaling_) {
}

Transformation3D::~Transformation3D() {
}

void Transformation3D::setPosition(Vertex3D position_) {
	this->position = position_;
}

void Transformation3D::setPosition(float x, float y, float z) {
	this->position = Vector3D(x, y, z);
}

void Transformation3D::setRotation(Vector3D rotation_) {
	this->rotation = rotation_;
}

void Transformation3D::setRotation(float x, float y, float z) {
	this->rotation = Vector3D(x, y, z);
}

void Transformation3D::setScaling(Vector3D scaling_) {
	this->scaling = scaling_;
}

void Transformation3D::setScaling(float x, float y, float z) {
	this->scaling = Vector3D(x, y, z);
}

void Transformation3D::move(Vector3D position_) {
	this->position.add(position_);
}

void Transformation3D::move(float x, float y, float z) {
	this->position.add(Vector3D(x, y, z));
}

void Transformation3D::rotate(Vector3D rotation_) {
	this->rotation.add(rotation_);
}

void Transformation3D::rotate(float x, float y, float z) {
	this->rotation.add(Vector3D(x, y, z));
}

void Transformation3D::scale(Vector3D scaling_) {
	this->scaling.add(scaling_);
}

void Transformation3D::scale(float x, float y, float z) {
	this->scaling.add(Vector3D(x, y, z));
}

void Transformation3D::useTransformation(void) {
	glRotatef(this->rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(this->rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(this->rotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(this->scaling.x, this->scaling.y, this->scaling.z);
	glTranslatef(this->position.x, this->position.y, this->position.z);
}

