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
#include "volumebox.h"

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
    POLYGON,
    MESH
};

class CollisionObject : public Transformation3D
{
    public:
        CollisionObject();
        CollisionObject(PhysicsObject *body_);
        ~CollisionObject();

        static const enum collision_type type = NONE;

        PhysicsObject *body;
        List<CollisionObject> *collisions;

        virtual Vector2D get_distance(Vector3D axis);
        virtual Vector3D get_normal(Vector3D pos);
        virtual bool check_collision(CollisionObject *obj);
};

class CollisionPoint : public CollisionObject
{
    public:
        CollisionPoint();
        ~CollisionPoint();

        static const enum collision_type type = POINT;

        Vector2D get_distance(Vector3D axis);
        Vector3D get_normal(Vector3D pos);
};

class BoundingSphere : public CollisionObject
{
    public:
        BoundingSphere();
        BoundingSphere(float radius_);
        BoundingSphere(float radius_, PhysicsObject *body_);
        ~BoundingSphere();

        static const enum collision_type type = BOUNDING_SPHERE;

        float radius;

        Vector2D get_distance(Vector3D axis);
        Vector3D get_normal(Vector3D pos);
};

class CollisionPolygon : public CollisionObject
{
    public:
        CollisionPolygon();
        CollisionPolygon(int num_vertices_, Vector3D *vertices_, int num_normals_, Vector3D *normals_);
        CollisionPolygon(Face *face);
        ~CollisionPolygon();

        static const enum collision_type type = POLYGON;

        Vector2D get_distance(Vector3D axis);
        Vector3D get_normal(Vector3D pos);

        bool check_collision(CollisionObject *obj);

    protected:
        int num_normals;
        Vector3D *normals;

        int num_vertices;
        Vector3D *vertices;
};

class BoundingBox : public CollisionPolygon, public VolumeBox
{
    public:
        BoundingBox();
        ~BoundingBox();

        static const enum collision_type type = BOUNDING_BOX;

        void update_poly(void);
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
        void pull(Vector3D v);

    private:
        Vector3D unpaid_force;
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

