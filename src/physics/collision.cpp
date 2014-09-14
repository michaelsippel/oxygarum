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
    if(!obj1->check_collision(obj2))
    {
        return false;
    }

    if(!obj2->check_collision(obj1))
    {
        return false;
    }

    printf("collision!\n");

    return true;
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
        obj1->body->velocity = Vector3D();
        return;
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

bool CollisionObject::check_collision(CollisionObject *obj)
{
    Vector3D axis = Vector3D(*this->position, *obj->position);
    axis.normalize();

    Vector2D d1 = this->get_distance(axis);
    Vector2D d2 = obj->get_distance(axis);

    return check_intersect(d1, d2);
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
    Vector2D dist = Vector2D(projection-0.05, projection+0.05);

    return dist;
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
    Vector2D dist = Vector2D(projection-radius, projection+radius);

    return dist;
}

Vector3D BoundingSphere::get_normal(Vector3D pos)
{
    Vector3D normal = Vector3D(*this->position, pos);
    normal.normalize();

    return normal;
}

// Polygon
CollisionPolygon::CollisionPolygon()
{
    CollisionObject();
}

CollisionPolygon::CollisionPolygon(int num_vertices_, Vector3D *vertices_, int num_normals_, Vector3D *normals_)
    : num_vertices(num_vertices_), vertices(vertices_), num_normals(num_normals_), normals(normals_)
{
    CollisionObject();
}

CollisionPolygon::CollisionPolygon(Face *face)
{
    CollisionObject();
}

CollisionPolygon::~CollisionPolygon()
{
}

Vector2D CollisionPolygon::get_distance(Vector3D axis)
{
    int i;
    Vector2D dist = Vector2D();

    for(i = 0; i < this->num_vertices; i++)
    {
        float projection = axis.dot(this->vertices[i]);
        if(projection < dist.x) dist.x = projection;
        if(projection > dist.y) dist.y = projection;
    }

    return dist;
}

Vector3D CollisionPolygon::get_normal(Vector3D pos)
{
    return Vector3D();
}

bool CollisionPolygon::check_collision(CollisionObject *obj)
{
    int i;

    for(i = 0; i < this->num_normals; i++)
    {
        Vector3D axis = this->normals[i];

        printf("projecting on axis (%f;%f;%f):\n", this->normals[i].x, this->normals[i].y, this->normals[i].z);

        Vector2D d1 = this->get_distance(this->normals[i]);
        Vector2D d2 = obj->get_distance(this->normals[i]);

        if(!check_intersect(d1, d2))
        {
            printf("\tno intersect. yay!\n");
            return false;
        }
        printf("\tintersects on this axis\n");
    }

    return true;
}

// Bounding Box
BoundingBox::BoundingBox()
{
    CollisionObject();
    Vector3D *v = (Vector3D*) calloc(sizeof(Vector3D), 8);
    Vector3D *n = (Vector3D*) calloc(sizeof(Vector3D), 3);

    this->num_vertices = 8;
    this->num_normals = 3;
    this->vertices = v;
    this->normals = n;
    //CollisionPolygon(8, v, 3, n); // FIXME: why this won't work?
}

BoundingBox::~BoundingBox()
{
}

void BoundingBox::update_poly(void)
{
    Vector3D m1 = this->box_size1;
    Vector3D m2 = this->box_size2;

    //if(this->num_vertices != 4 || this->num_normals != 3) return;


    this->vertices[0] = Vector3D(m1.x, m1.y, m1.z);
    this->vertices[0].rotate(*this->rotation);
    this->vertices[0].add(*this->position);

    this->vertices[1] = Vector3D(m2.x, m1.y, m1.z);
    this->vertices[1].rotate(*this->rotation);
    this->vertices[1].add(*this->position);

    this->vertices[2] = Vector3D(m1.x, m2.y, m1.z);
    this->vertices[2].rotate(*this->rotation);
    this->vertices[2].add(*this->position);

    this->vertices[3] = Vector3D(m2.x, m2.y, m1.z);
    this->vertices[3].rotate(*this->rotation);
    this->vertices[3].add(*this->position);

    this->vertices[4] = Vector3D(m1.x, m1.y, m2.z);
    this->vertices[4].rotate(*this->rotation);
    this->vertices[4].add(*this->position);

    this->vertices[5] = Vector3D(m2.x, m1.y, m2.z);
    this->vertices[5].rotate(*this->rotation);
    this->vertices[5].add(*this->position);

    this->vertices[6] = Vector3D(m1.x, m2.y, m2.z);
    this->vertices[6].rotate(*this->rotation);
    this->vertices[6].add(*this->position);

    this->vertices[7] = Vector3D(m2.x, m2.y, m2.z);
    this->vertices[7].rotate(*this->rotation);
    this->vertices[7].add(*this->position);

    this->normals[0] = Vector3D(1.0f, 0.0f, 0.0f);
    this->normals[1] = Vector3D(0.0f, 1.0f, 0.0f);
    this->normals[2] = Vector3D(0.0f, 0.0f, 1.0f);
}

};

