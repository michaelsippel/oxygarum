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
    this->collisions = new List<CollisionObject>();
    this->fields = new List<ForceField>();
}

PhysicsContext::~PhysicsContext()
{
    delete this->objects;
    delete this->collisions;
    delete this->fields;
}

void PhysicsContext::update(float speed)
{
    // check all combinations of collisions
    ListEntry<CollisionObject> *c1_entry = collisions->getHead();
    while(c1_entry != NULL)
    {
        ListEntry<CollisionObject> *c2_entry = c1_entry->getNext();
        while(c2_entry != NULL)
        {
            if(c2_entry != c1_entry && c1_entry->element != NULL && c2_entry->element != NULL)
            {
                CollisionObject *obj1 = c1_entry->element;
                CollisionObject *obj2 = c2_entry->element;

                if(check_collision(obj1, obj2))
                {
                    if(obj1->collisions->isContained(obj2) == NULL)
                    {
                        handle_collision(obj1, obj2);
                    }

                    if(obj2->collisions->isContained(obj1) == NULL)
                    {
                        handle_collision(obj2, obj1);
                    }

                    obj1->collisions->add(obj2);
                    obj2->collisions->add(obj1);
                }
                else
                {
                    ListEntry<CollisionObject> *e1 = obj1->collisions->isContained(obj2);
                    ListEntry<CollisionObject> *e2 = obj2->collisions->isContained(obj1);
                    if(e1 != NULL) obj1->collisions->remove(e1);
                    if(e2 != NULL) obj2->collisions->remove(e2);
                }
            }
            c2_entry = c2_entry->getNext();
        }
        c1_entry = c1_entry->getNext();
    }

    // move objects
    ListEntry<PhysicsObject> *entry = this->objects->getHead();
    while(entry != NULL)
    {
        PhysicsObject *obj = entry->element;
        if(obj != NULL)
        {
            ListEntry<ForceField> *f_entry = this->fields->getHead();
            while(f_entry != NULL)
            {
                ForceField *field = f_entry->element;
                Vector3D v = field->velocity;
                v.mul(speed);

                obj->push(v);

                f_entry = f_entry->getNext();
            }

            obj->update(speed);
        }

        entry = entry->getNext();
    }
}

};

