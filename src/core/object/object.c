/**
 *  src/core/object/object.c
 *
 *  (C) Copyright 2012-2013 Michael Sippel
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

#include "vertex.h"
#include "face.h"
#include "object.h"

object3d_t *oxygarum_create_object3d(void) {
  object3d_t *object = malloc(sizeof(object3d_t));
  memset(object, 0, sizeof(object3d_t));
  
  object->status = OBJECT_VISIBLE;
  
  return object;
}

object2d_t *oxygarum_create_object2d(void) {
  object2d_t *object = malloc(sizeof(object2d_t));
  memset(object, 0, sizeof(object2d_t));
  
  object->status = OBJECT_VISIBLE;  
  
  return object;
}

void oxygarum_render_object3d(object3d_t *obj) {
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
  
  if(! obj->status & OBJECT_DEPTH_BUFFERING) {
    glDisable(GL_DEPTH_TEST);
  }
  
  if(obj->status & OBJECT_TRANSPARENT) {    
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }
  
  material_t *material = obj->mesh->material;
  entry = material->textures->head;
  i = 0;
  while(entry != NULL) {
    texture_t *tex = (texture_t*) entry->element;
    glActiveTexture(GL_TEXTURE0 + i);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex->id);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    entry = entry->next;
    i++;
  }
  
  glColor4fv(&material->color.color);
  
  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, material->shininess);
  
  glShadeModel(obj->shade_model);
  glUseProgram(obj->shade_program);
  
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
      glBindBuffer(GL_ARRAY_BUFFER, obj->mesh->instance->tex_id);
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
      oxygarum_render_face3d(obj->mesh, obj->mesh->faces[i]);
    }
  }
}

void oxygarum_render_object2d(object2d_t *obj) {
  int i;
  for(i = 0; i < obj->mesh->face_counter; i++) {
    oxygarum_render_face2d(obj->mesh, obj->mesh->faces[i]);
  }
}

