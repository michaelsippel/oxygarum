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
    this->fields = new List<ForceField>();
}

PhysicsContext::~PhysicsContext()
{
    delete this->objects;
    delete this->fields;
}

void PhysicsContext::update(float speed)
{
    ListEntry<PhysicsObject> *entry = this->objects->getHead();
    while(entry != NULL)
    {
        PhysicsObject *obj = entry->element;
        if(obj != NULL)
        {
            bool collide = 0;
            ListEntry<PhysicsObject> *centry = this->objects->getHead();
            while(centry != NULL)
            {
                if(centry != entry)
                {
                    PhysicsObject *cobj = centry->element;
                    if(cobj != NULL)
                    {
                        if(cobj->collision != NULL && obj->collision != NULL)
                        {
                            // check collision
                            if(check_collision(cobj->collision, obj->collision))
                            {
                                collide = 1;
                                break;
                            }
                        }
                    }
                }
                centry = centry->getNext();
            }

            ListEntry<ForceField> *f_entry = this->fields->getHead();
            while(f_entry != NULL)
            {
                ForceField *field = f_entry->element;
                Vector3D v = field->velocity;
                v.mul(speed);

                if(!collide)
                {
                    obj->push(v);
                }

                f_entry = f_entry->getNext();
            }

            if(!collide)
            {
                obj->update(speed);
            }
        }

        entry = entry->getNext();
    }
}

};

