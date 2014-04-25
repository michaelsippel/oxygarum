/**
 *  src/core/object/object3d.cpp
 *
 *  (C) Copyright 2012-2014 Michael Sippel
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include "object.h"

Object3D::Object3D() {
	this->position = Vector3D();
	this->rotation = Vector3D();

	this->mesh = NULL;
	this->material = NULL;

	this->status = OBJECT_VISIBLE | OBJECT_DEPTH_BUFFERING;
}

Object3D::Object3D(Transformation3D transform) {
	this->position = transform.position;
	this->rotation = transform.rotation;

	this->mesh = NULL;
	this->material = NULL;

	this->status = OBJECT_VISIBLE | OBJECT_DEPTH_BUFFERING;
}

Object3D::Object3D(Vector3D position_)
: position(position_) {
	this->rotation = Vector3D();

	this->mesh = NULL;
	this->material = NULL;

	this->status = OBJECT_VISIBLE | OBJECT_DEPTH_BUFFERING;
}

Object3D::Object3D(Vector3D position_, Vector3D rotation_)
: position(position_), rotation(rotation_) {
	this->mesh = NULL;
	this->material = NULL;

	this->status = OBJECT_VISIBLE | OBJECT_DEPTH_BUFFERING;
}

Object3D::~Object3D() {
}

void Object3D::setFlag(int flag) {
	this->status |= flag;
}

void Object3D::removeFlag(int flag) {
	this->status &= ~flag;
}

int Object3D::getStatus(void) {
	return status;
}

void Object3D::render(void) {
  int i;
  group_entry_t *entry;  

  glTranslatef(obj->pos.x, obj->pos.y, obj->pos.z);
  glRotatef(obj->rot.x, 1.0f,0.0f,0.0f);
  glRotatef(obj->rot.y, 0.0f,1.0f,0.0f);
  glRotatef(obj->rot.z, 0.0f,0.0f,1.0f);
  
  float feedback[3] = {-1.0f, -1.0f, -1.0f};  
  
  glFeedbackBuffer(3, GL_3D, feedback);      
  glRenderMode(GL_FEEDBACK);
  glBegin(GL_POINTS);
    glVertex3f(0.0f,0.0f,0.0f);
  glEnd();
  glRenderMode(GL_RENDER);  
  
  obj->feedback.x = feedback[1];
  obj->feedback.y = feedback[2];  
  
  if(! (obj->status & OBJECT_DEPTH_BUFFERING)) {
    glDisable(GL_DEPTH_TEST);
  }
  
  if(obj->status & OBJECT_TRANSPARENT) {    
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }
  
  material_t *material = obj->material;
  if(material == NULL) {
    material = obj->mesh->default_material;
  }
  oxygarum_use_material(material);

  if(obj->status & OBJECT_RENDER_VBO && obj->mesh->instance != NULL) {
    glBindBuffer(GL_ARRAY_BUFFER, obj->mesh->instance->normal_id);
    glNormalPointer(GL_FLOAT, 0, NULL);
    
    glBindBuffer(GL_ARRAY_BUFFER, obj->mesh->instance->vertex_id);
    glVertexPointer(3, GL_FLOAT, 0, NULL);
    
    entry = material->textures->head;
    i = 0;
    while(entry != NULL) {
      glClientActiveTexture(GL_TEXTURE0 + i);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glBindBuffer(GL_ARRAY_BUFFER, obj->mesh->instance->texcoord_id);
      glTexCoordPointer(2, GL_FLOAT, 0, NULL);
      
      entry = entry->next;
      i++;
    }
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->mesh->instance->index_id);    
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glDrawElements(GL_TRIANGLES, obj->mesh->instance->index_counter, GL_UNSIGNED_INT, NULL);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
  } else {
    for(i = 0; i < obj->mesh->face_counter; i++) {    
      oxygarum_render_face3d(obj->mesh, material, obj->mesh->faces[i]);
    }
  }
}

