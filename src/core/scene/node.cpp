/**
 *  src/core/node.cpp
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

/**
 * @author Michael Sippel <michamimosa@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>

#include "scene.h"
#include "object.h"
#include "particle.h"
#include "font.h"
#include "light.h"
#include "math.h"

namespace oxygarum
{

SceneNode::SceneNode()
{
    this->position = Vector3D();
    this->rotation = Vector3D();

    this->objects3D = new List<Object3D>();
    //this->objects2D = new List<Object2D>();
    //this->texts = new List<Text>();
    //this->particle_emitters = new List<ParticleEmitter>();
    this->lights = new List<Light>();

    this->subnodes = new List<SceneNode>();

    this->updateSize();
}

SceneNode::~SceneNode()
{
    delete this->objects3D;
    //delete this->objects2D;
    //delete this->texts;
    //delete this->particle_emitters;
    delete this->lights;
    delete this->subnodes;
}

void SceneNode::render3D(void)
{
    this->drawDebugBox();
    // update lights
    ListEntry<Light> *l_entry = this->lights->getHead();

    while(l_entry != NULL)
    {
        //this->logger->log(INFO, "rendering light \"%s\"", l_entry->name);
        Light *light = l_entry->element;
        if(light == NULL)
        {
            continue;
        }

        glPushMatrix();

        light->useTransformation();
        light->update();

        glPopMatrix();

        l_entry = l_entry->getNext();
    }

    // render 3D-Objects
    ListEntry<Object3D> *o_entry = this->objects3D->getHead();

    while(o_entry != NULL)
    {
        //this->logger->log(INFO, "rendering object \"%s\"", o_entry->name);
        Object3D *obj = o_entry->element;
        if(obj == NULL)
        {
            continue;
        }

        if(obj->getStatus() & OBJECT_VISIBLE)
        {
            glPushMatrix();
            glPushAttrib(GL_ENABLE_BIT);

            obj->useTransformation();
            obj->render();

            glPopAttrib();
            glPopMatrix();
        }

        o_entry = o_entry->getNext();
    }
    /*
      // render particles
      entry = scene->particle_emitters->head;
      while(entry != NULL) {
        particle_emitter_t *emitter = (particle_emitter_t*) entry->element;
        if(emitter == NULL) {
          continue;
        }

        glPushMatrix();
          glTranslatef(emitter->pos.x, emitter->pos.y, emitter->pos.z);
          oxygarum_render_particle_system(emitter);
        glPopMatrix();

        entry = entry->next;
      }*/


    // render subnodes
    ListEntry<SceneNode> *s_entry = this->subnodes->getHead();
    while(s_entry != NULL)
    {
        SceneNode *subnode = s_entry->element;
        if(subnode != NULL)
        {
            subnode->useTransformation();
            subnode->render3D();
        }
        s_entry = s_entry->getNext();
    }
}

void SceneNode::render2D(void)
{
    /*  group_entry_t *entry;

      // render 2D-Objects
      entry = scene->objects2d->head;
      while(entry != NULL) {
        object2d_t *obj = (object2d_t*) entry->element;
        if(obj == NULL) {
          continue;
        }

        if(obj->status & OBJECT_VISIBLE) {
          glPushMatrix();
            oxygarum_render_object2d(obj);
          glPopMatrix();
        }

        entry = entry->next;
      }

      // render texts
      entry = scene->texts->head;
      while(entry != NULL) {
        text_t *text = (text_t*) entry->element;
        if(text == NULL) {
          continue;
        }

        glPushMatrix();
          oxygarum_render_text(text);
        glPopMatrix();

        entry = entry->next;
      }*/
}

void SceneNode::drawDebugBox(void)
{
    glDisable(GL_LIGHTING);
    glUseProgram(0);
    glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    // back
    glVertex3f(this->size1.x, this->size1.y, this->size1.z);
    glVertex3f(this->size1.x, this->size2.y, this->size1.z);

    glVertex3f(this->size1.x, this->size2.y, this->size1.z);
    glVertex3f(this->size2.x, this->size2.y, this->size1.z);

    glVertex3f(this->size2.x, this->size2.y, this->size1.z);
    glVertex3f(this->size2.x, this->size1.y, this->size1.z);

    glVertex3f(this->size2.x, this->size1.y, this->size1.z);
    glVertex3f(this->size1.x, this->size1.y, this->size1.z);

    // middle
    glVertex3f(this->size1.x, this->size1.y, this->size1.z);
    glVertex3f(this->size1.x, this->size1.y, this->size2.z);

    glVertex3f(this->size1.x, this->size2.y, this->size1.z);
    glVertex3f(this->size1.x, this->size2.y, this->size2.z);

    glVertex3f(this->size2.x, this->size2.y, this->size1.z);
    glVertex3f(this->size2.x, this->size2.y, this->size2.z);

    glVertex3f(this->size2.x, this->size1.y, this->size1.z);
    glVertex3f(this->size2.x, this->size1.y, this->size2.z);

    // front
    glVertex3f(this->size1.x, this->size1.y, this->size2.z);
    glVertex3f(this->size1.x, this->size2.y, this->size2.z);

    glVertex3f(this->size1.x, this->size2.y, this->size2.z);
    glVertex3f(this->size2.x, this->size2.y, this->size2.z);

    glVertex3f(this->size2.x, this->size2.y, this->size2.z);
    glVertex3f(this->size2.x, this->size1.y, this->size2.z);

    glVertex3f(this->size2.x, this->size1.y, this->size2.z);
    glVertex3f(this->size1.x, this->size1.y, this->size2.z);

    glEnd();
}

void SceneNode::updateSize(void)
{
    this->size1 = Vector3D(0.1f, 0.1f, 0.1f);
    this->size2 = Vector3D(0.1f, 0.1f, 0.1f);
    /*
    	// check subnodes
    	ListEntry<SceneNode> *s_entry = this->subnodes->getHead();
    	while(s_entry != NULL)
    	{
    		SceneNode *subnode = s_entry->element;
    		if(subnode != NULL)
    		{
    			subnode->updateSize();
    			if(subnode->size.x > this->size.x) this->size.x = subnode->size.x;
    			if(subnode->size.y > this->size.y) this->size.y = subnode->size.y;
    			if(subnode->size.z > this->size.z) this->size.z = subnode->size.z;
    		}
    		s_entry = s_entry->getNext();
    	}
    */
    // check objects
    ListEntry<Object3D> *o_entry = this->objects3D->getHead();
    while(o_entry != NULL)
    {
        Object3D *obj = o_entry->element;
        if(obj != NULL)
        {
            Mesh3D *mesh = obj->mesh;
            if(mesh != NULL)
            {
                Vector3D m1 = Vector3D();
                Vector3D m2 = Vector3D();
                mesh->getMagnitude(&m1, &m2);

                m1.x = cos(obj->rotation.x) * m1.x;
                m1.y = cos(obj->rotation.y) * m1.y;
                m1.z = cos(obj->rotation.z) * m1.z;
                m2.x = cos(obj->rotation.x) * m2.x;
                m2.y = cos(obj->rotation.y) * m2.y;
                m2.z = cos(obj->rotation.z) * m2.z;
                m1.add(obj->position);
                m2.add(obj->position);

                if(m1.x < this->size1.x) this->size1.x = m1.x;
                if(m1.y < this->size1.y) this->size1.y = m1.y;
                if(m1.z < this->size1.z) this->size1.z = m1.z;
                if(m2.x > this->size2.x) this->size2.x = m2.x;
                if(m2.y > this->size2.y) this->size2.y = m2.y;
                if(m2.z > this->size2.z) this->size2.z = m2.z;
            }
        }
        o_entry = o_entry->getNext();
    }

    this->logger->log(INFO, "size is %f, %f, %f", this->size1.x, this->size1.y, this->size1.z);
}

};

