/**
 *  src/core/object/object3d.cpp
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include "object.h"

namespace oxygarum {

Object3D::Object3D() {
	this->position = Vector3D();
	this->rotation = Vector3D();

	this->mesh = NULL;
	this->material = NULL;

	this->status = OBJECT_VISIBLE | OBJECT_DEPTH_BUFFERING;
}

Object3D::Object3D(Transformation3D transform) {
	this->position = transform.position;
	this->rotation = transform.rotation;

	this->mesh = NULL;
	this->material = NULL;

	this->status = OBJECT_VISIBLE | OBJECT_DEPTH_BUFFERING;
}

Object3D::Object3D(Vector3D position_) {
	this->position = position_;
	this->rotation = Vector3D();

	this->mesh = NULL;
	this->material = NULL;

	this->status = OBJECT_VISIBLE | OBJECT_DEPTH_BUFFERING;
}

Object3D::Object3D(Vector3D position_, Vector3D rotation_) {
	this->position = position_;
	this->rotation = rotation_;

	this->mesh = NULL;
	this->material = NULL;

	this->status = OBJECT_VISIBLE | OBJECT_DEPTH_BUFFERING;
}

Object3D::~Object3D() {
}

void Object3D::setFlag(int flag) {
	this->status |= flag;
}

void Object3D::removeFlag(int flag) {
	this->status &= ~flag;
}

int Object3D::getStatus(void) {
	return status;
}

void Object3D::render(void) {
	glFeedbackBuffer(3, GL_3D, (GLfloat*) &this->feedback);
	glRenderMode(GL_FEEDBACK);
	glBegin(GL_POINTS);
		glVertex3f(0.0f,0.0f,0.0f);
	glEnd();
	glRenderMode(GL_RENDER);

	if(! (this->status & OBJECT_DEPTH_BUFFERING)) {
		glDisable(GL_DEPTH_TEST);
	}

	if(this->status & OBJECT_TRANSPARENT) {    
		glDisable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	Material *mat = this->material;
	if(mat == NULL && this->mesh != NULL) {
		mat = this->mesh->default_material;
	}

	int num_textures = 0;
	if(mat != NULL){
		mat->use();
		num_textures = mat->textures->getSize();
	}

	if(this->mesh != NULL) {
		if(this->status & OBJECT_RENDER_VBO && this->mesh->instance != NULL) {
			this->mesh->renderInstance(num_textures);
		} else {
			this->mesh->renderImmediate(num_textures);
		}
	}
}

};

