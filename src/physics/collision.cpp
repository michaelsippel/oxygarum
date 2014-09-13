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
#include <math.h>

#include "physics.h"
#include "vector.h"

using namespace std;

namespace oxygarum
{

bool check_intersect(Vector2D d1, Vector2D d2)
{
    if(d1.y >= d2.x && d1.x <= d2.y)
    {
        return true;
    }

    return false;
}

bool check_collision(CollisionObject *obj1, CollisionObject *obj2)
{
    Vector3D axis = Vector3D(*obj1->position, *obj2->position);
    axis.normalize();

    Vector2D d1 = obj1->get_distance(axis);
    Vector2D d2 = obj2->get_distance(axis);

    return check_intersect(d1, d2);
}

void handle_collision(CollisionObject *obj1, CollisionObject *obj2)
{
    /**
     * obj1 is the actor:
     *     - gives his impulse to obj2
     *     - reflects on obj2
     * obj2 is passive:
     *     - it will be pushed by obj1
     */

    if(obj1->body != NULL)
    {
        Vector3D normal = obj2->get_normal(*obj1->position);
        Vector3D dir = obj1->body->velocity;
        dir.normalize();

        float impulse = -obj1->body->velocity.length();

        Vector3D diff = Vector3D(normal, dir);
        float split_a = diff.length() * 0.5f;
        float split_b = split_a - 1.0;

        // give impulse to obj2
        if(obj2->body != NULL)
        {
            Vector3D ivec = normal;
            ivec.mul(impulse * split_a);
            obj2->body->push(ivec);
        }

        // reflection
        normal.mul(-1.0f);
        obj1->body->velocity = Vector3D(normal, dir);
        obj1->body->velocity.normalize();
        obj1->body->velocity.mul(impulse * split_b);
    }
}

CollisionObject::CollisionObject()
{
    this->body = NULL;
    this->collisions = new List<CollisionObject>();
}

CollisionObject::CollisionObject(PhysicsObject *body_)
    : body(body_)
{
    this->collisions = new List<CollisionObject>();
}

CollisionObject::~CollisionObject()
{
}

Vector2D CollisionObject::get_distance(Vector3D axis)
{
    return Vector2D();
}

Vector3D CollisionObject::get_normal(Vector3D pos)
{
    return Vector3D();
}

void CollisionObject::point_projection(Vector3D axis, Vector3D point)
{
    float p = axis.dot(point);

    if(p < this->dist.x) this->dist.x = p;
    if(p > this->dist.y) this->dist.y = p;
}

//Point
CollisionPoint::CollisionPoint()
{
    CollisionObject();
}

CollisionPoint::~CollisionPoint()
{
}

Vector2D CollisionPoint::get_distance(Vector3D axis)
{
    float projection = axis.dot(*this->position);
    this->dist = Vector2D(projection-0.05, projection+0.05);

    return this->dist;
}

Vector3D CollisionPoint::get_normal(Vector3D pos)
{
    Vector3D normal = Vector3D(*this->position, pos);
    normal.normalize();

    return normal;
}

//Sphere
BoundingSphere::BoundingSphere()
{
    CollisionObject();
}

BoundingSphere::BoundingSphere(float radius_)
    : radius(radius_)
{
    CollisionObject();
}

BoundingSphere::BoundingSphere(float radius_, PhysicsObject *body_)
    : CollisionObject(body_), radius(radius_)
{
}

BoundingSphere::~BoundingSphere()
{
}

Vector2D BoundingSphere::get_distance(Vector3D axis)
{
    float projection = axis.dot(*this->position);
    this->dist = Vector2D(projection-radius, projection+radius);

    return this->dist;
}

Vector3D BoundingSphere::get_normal(Vector3D pos)
{
    Vector3D normal = Vector3D(*this->position, pos);
    normal.normalize();

    return normal;
}

// Bounding Box
BoundingBox::BoundingBox()
{
    CollisionObject();
}

BoundingBox::~BoundingBox()
{
}

Vector2D BoundingBox::get_distance(Vector3D axis)
{
    Vector3D m1 = this->box_size1;
    Vector3D m2 = this->box_size2;

    this->dist = Vector2D();

    Vector3D a = Vector3D(m1.x, m1.y, m1.z);
    a.rotate(*this->rotation);
    a.add(*this->position);
    this->point_projection(axis, a);

    Vector3D b = Vector3D(m2.x, m1.y, m1.z);
    b.rotate(*this->rotation);
    b.add(*this->position);
    this->point_projection(axis, b);

    Vector3D c = Vector3D(m1.x, m2.y, m1.z);
    c.rotate(*this->rotation);
    c.add(*this->position);
    this->point_projection(axis, c);

    Vector3D d = Vector3D(m2.x, m2.y, m1.z);
    d.rotate(*this->rotation);
    d.add(*this->position);
    this->point_projection(axis, d);

    Vector3D e = Vector3D(m1.x, m1.y, m2.z);
    e.rotate(*this->rotation);
    e.add(*this->position);
    this->point_projection(axis, e);

    Vector3D f = Vector3D(m2.x, m1.y, m2.z);
    f.rotate(*this->rotation);
    f.add(*this->position);
    this->point_projection(axis, f);

    Vector3D g = Vector3D(m1.x, m2.y, m2.z);
    g.rotate(*this->rotation);
    g.add(*this->position);
    this->point_projection(axis, g);

    Vector3D h = Vector3D(m2.x, m2.y, m2.z);
    h.rotate(*this->rotation);
    h.add(*this->position);
    this->point_projection(axis, h);

    return this->dist;
}

Vector3D BoundingBox::get_normal(Vector3D pos)
{
    Vector3D normal = Vector3D(*this->position, pos);
    normal.normalize();

    return normal;
}

};

