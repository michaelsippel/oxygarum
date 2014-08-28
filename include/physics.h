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

class PhysicsObject;

class ForceField
{
    public:
        ForceField();
        ~ForceField();

        //int type;
        Vector3D velocity;
};

enum collision_type
{
    NONE = 0,
    POINT,
    BOUNDING_SPHERE,
    BOUNDING_BOX,
    MESH
};

class CollisionObject : public Transformation3D
{
    public:
        CollisionObject();
        CollisionObject(PhysicsObject *body_);
        ~CollisionObject();

		PhysicsObject *body;
		List<CollisionObject> *collisions;

        virtual Vector2D get_distance(Vector3D axis);
};

class CollisionPoint : public CollisionObject
{
    public:
        CollisionPoint();
        ~CollisionPoint();

        Vector2D get_distance(Vector3D axis);
};

class BoundingSphere : public CollisionObject
{
    public:
        BoundingSphere();
        BoundingSphere(float radius_);
        BoundingSphere(float radius_, PhysicsObject *body_);
        ~BoundingSphere();

        float radius;

        Vector2D get_distance(Vector3D axis);
};

class PhysicsObject : public Transformation3D
{
    public:
        PhysicsObject();
        ~PhysicsObject();

        CollisionObject *collision;
        Vector3D velocity;

        void update(float speed);
        void push(Vector3D v);
};

class PhysicsContext
{
    public:
        PhysicsContext();
        ~PhysicsContext();

        List<PhysicsObject> *objects;
		List<CollisionObject> *collisions;
        List<ForceField> *fields;

        void update(float speed);
};

bool check_collision(CollisionObject *obj1, CollisionObject *obj2);
void handle_collision(CollisionObject *obj1, CollisionObject *obj2);

};

#endif

