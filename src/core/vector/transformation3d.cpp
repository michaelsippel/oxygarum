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
#include <GL/glew.h>
#include <GL/gl.h>

#include "transformation.h"

namespace oxygarum
{

Transformation3D::Transformation3D()
{
    this->position = new Vector3D();
    this->rotation = new Vector3D();
    this->scaling = new Vector3D(1.0f, 1.0f, 1.0f);
}

Transformation3D::Transformation3D(Vector3D *position_, Vector3D *rotation_)
    : position(position_), rotation(rotation_)
{
    this->scaling = new Vector3D(1.0f, 1.0f, 1.0f);
}

Transformation3D::Transformation3D(Vector3D *position_, Vector3D *rotation_, Vector3D *scaling_)
    : position(position_), rotation(rotation_), scaling(scaling_)
{
}

Transformation3D::Transformation3D(Vector3D position_, Vector3D rotation_)
{
    this->position = new Vector3D();
    this->rotation = new Vector3D();

    *this->position = position_;
    *this->rotation = rotation_;
    this->scaling = new Vector3D(1.0f, 1.0f, 1.0f);
}

Transformation3D::Transformation3D(Vector3D position_, Vector3D rotation_, Vector3D scaling_)
{
    this->position = new Vector3D();
    this->rotation = new Vector3D();
    this->scaling = new Vector3D();

    *this->position = position_;
    *this->rotation = rotation_;
    *this->scaling = scaling_;
}


Transformation3D::~Transformation3D()
{
}

void Transformation3D::setPosition(Vector3D position_)
{
    *this->position = position_;
}

void Transformation3D::setRotation(Vector3D rotation_)
{
    *this->rotation = rotation_;
}

void Transformation3D::setScaling(Vector3D scaling_)
{
    *this->scaling = scaling_;
}

void Transformation3D::setScaling(float x_)
{
    this->setScaling(Vector3D(x_, x_, x_));
}

void Transformation3D::move(Vector3D position_)
{
    this->position->add(position_);
}

void Transformation3D::rotate(Vector3D rotation_)
{
    this->rotation->add(rotation_);
}

void Transformation3D::scale(Vector3D scaling_)
{
    this->scaling->add(scaling_);
}

void Transformation3D::scale(float x_)
{
    this->scale(Vector3D(x_, x_, x_));
}

void Transformation3D::useTransformation(void)
{
    glRotatef(this->rotation->x, 1.0f, 0.0f, 0.0f);
    glRotatef(this->rotation->y, 0.0f, 1.0f, 0.0f);
    glRotatef(this->rotation->z, 0.0f, 0.0f, 1.0f);
    glTranslatef(this->position->x, this->position->y, this->position->z);
    glScalef(this->scaling->x, this->scaling->y, this->scaling->z);
}

void Transformation3D::parent(Transformation3D *parent_)
{
    this->parent_position(parent_);
    this->parent_rotation(parent_);
    this->parent_scaling(parent_);
}

void Transformation3D::parent_position(Transformation3D *parent_)
{
    this->position = parent_->position;
}

void Transformation3D::parent_rotation(Transformation3D *parent_)
{
    this->rotation = parent_->rotation;
}

void Transformation3D::parent_scaling(Transformation3D *parent_)
{
    this->scaling = parent_->scaling;
}

};

