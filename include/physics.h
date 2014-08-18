/**
 *  include/physics.h
 *
 *  Copyright (C) 2013-2014 Michael Sippel
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

#ifndef _PHYSICS_H
#define _PHYSICS_H

#include <list.h>
#include "object.h"
#include "vector.h"

namespace oxygarum
{

class ForceField
{
	public:
		ForceField();
		~ForceField();

		//int type;
		Vector3D velocity;
};

class PhysicsObject
{
	public:
		PhysicsObject();
		~PhysicsObject();

		void update(float speed);

		Object3D *object;
		Vector3D velocity;
};

class PhysicsContext
{
	public:
		PhysicsContext();
		~PhysicsContext();

		void update(float speed);

		List<PhysicsObject> *objects;
		List<ForceField> *fields;
};

};

#endif

