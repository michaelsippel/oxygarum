/**
 *  src/physics/object.cpp
 *
 *  (C) Copyright 2013-2014 Michael Sippel
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
#include "physics.h"
#include "vector.h"

namespace oxygarum
{

PhysicsObject::PhysicsObject()
{
    this->velocity = Vector3D();
    this->collision = NULL;
}

PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::update(float speed)
{
    Vector3D v = this->velocity;

    v.mul(speed);
    this->move(v);
}

void PhysicsObject::push(Vector3D v)
{
    this->velocity.add(v);
}

void PhysicsObject::pull(Vector3D v)
{
    this->velocity.sub(v);
}

};

