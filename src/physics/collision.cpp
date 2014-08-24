/**
 *  src/physics/collision.cpp
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

bool check_collision(CollisionObject *obj1, CollisionObject *obj2)
{
    if(obj1->trans == NULL || obj2->trans == NULL)
    {
        return false;
    }

    Vector3D axis = Vector3D(obj1->trans->position, obj2->trans->position);
    axis.normalize();

    Vector2D d1 = obj1->get_distance(axis);
    Vector2D d2 = obj2->get_distance(axis);

    if(d1.y >= d2.x && d1.x <= d2.y)
    {
        return true;
    }

    return false;
}

CollisionObject::CollisionObject()
{
}

CollisionObject::~CollisionObject()
{
}

Vector2D CollisionObject::get_distance(Vector3D axis)
{
    return Vector2D();
}

//Point
CollisionPoint::CollisionPoint()
{
}

CollisionPoint::~CollisionPoint()
{
}

Vector2D CollisionPoint::get_distance(Vector3D axis)
{
    float projection = axis.scalar(this->trans->position);
    Vector2D dist = Vector2D(projection-0.05, projection+0.05);

    return dist;
}

//sphere
BoundingSphere::BoundingSphere()
{
}

BoundingSphere::BoundingSphere(float radius_)
    : radius(radius_)
{
}

BoundingSphere::~BoundingSphere()
{
}

Vector2D BoundingSphere::get_distance(Vector3D axis)
{
    float projection = axis.scalar(this->trans->position);
    Vector2D dist = Vector2D(projection-radius, projection+radius);

    return dist;
}

};

