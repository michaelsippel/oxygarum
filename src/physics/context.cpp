/**
 *  src/physics/context.cpp
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

PhysicsContext::PhysicsContext()
{
	this->objects = new List<PhysicsObject>();
}

PhysicsContext::~PhysicsContext()
{
	delete this->objects;
}

void PhysicsContext::update(float speed)
{
	ListEntry<PhysicsObject> *entry = this->objects->getHead();

	Vector3D gravity = Vector3D(0.0f, -9.80665f, 0.0f);
	gravity.mul(speed);

	while(entry != NULL)
	{
		PhysicsObject *obj = entry->element;
		if(obj != NULL)
		{
			obj->velocity.add(gravity);
			obj->update(speed);
		}

		entry = entry->getNext();
	}
}

};

