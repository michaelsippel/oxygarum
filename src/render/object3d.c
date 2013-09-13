/**
 *  src/render/object3d.c
 *
 *  (C) Copyright 2013 Michael Sippel
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
#include <unistd.h>
#include <stdio.h>
#include <GL/gl.h>
#include "vertex.h"
#include "object.h"
#include "font.h"
#include "light.h"

unsigned int display_object3d_counter = 0;
display_obj3d_t **display_objects3d;

void oxygarum_render_object3d(display_obj3d_t *obj) {
  int i;
  float feedback[3] = {-1.0f, -1.0f, -1.0f};  
  
  glFeedbackBuffer(3, GL_3D, feedback);      
  glRenderMode(GL_FEEDBACK);
  glBegin(GL_POINTS);
    glVertex3f(0.0f,0.0f,0.0f);
  glEnd();
  glRenderMode(GL_RENDER);  
  
  obj->feedback.x = feedback[1];
  obj->feedback.y = feedback[2];
  
  glTranslatef(obj->pos.x, obj->pos.y, obj->pos.z);
  glRotatef(obj->rot.x, 1.0f,0.0f,0.0f);
  glRotatef(obj->rot.y, 0.0f,1.0f,0.0f);
  glRotatef(obj->rot.z, 0.0f,0.0f,1.0f);
  
  if(! obj->status & OBJECT_DEPTH_BUFFERING) {
    glDisable(GL_DEPTH_TEST);
  }
  
  if(obj->status & OBJECT_TRANSPARENT) {    
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }
  
  material_t *material = obj->object->material;  
  
  for(i = 0; i < material->texture_counter; i++) {
    glActiveTexture(GL_TEXTURE0 + i);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, material->textures[i]->id);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  }
  
  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, material->shininess);
  
  glShadeModel(obj->shade_model);
  glUseProgram(obj->shade_program);
  
  if(obj->status & OBJECT_RENDER_VBO && obj->object->instance != NULL) {
    glBindBuffer(GL_ARRAY_BUFFER, obj->object->instance->normal_id);
    glNormalPointer(GL_FLOAT, 0, NULL);
    
    glBindBuffer(GL_ARRAY_BUFFER, obj->object->instance->vertex_id);
    glVertexPointer(3, GL_FLOAT, 0, NULL);
    
    for(i = 0; i < material->texture_counter; i++) {
      glClientActiveTexture(GL_TEXTURE0 + i);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glBindBuffer(GL_ARRAY_BUFFER, obj->object->instance->tex_id[i]);
      glTexCoordPointer(2, GL_FLOAT, 0, NULL);
    }
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->object->instance->index_id);    
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glDrawElements(GL_TRIANGLES, obj->object->instance->index_counter, GL_UNSIGNED_INT, NULL);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
  } else {
    oxygarum_display_object3d(obj->object);
  }
}

void oxygarum_render_all_objects3d(void) {
  int i;
  for(i = 0; i < display_object3d_counter; i++) {
    if(display_objects3d[i] == NULL) {
      continue;
    }
    
    display_obj3d_t *obj = display_objects3d[i];
    if(obj->status & OBJECT_VISIBLE) {
      glPushMatrix();
      glPushAttrib(GL_ENABLE_BIT);
      
      oxygarum_render_object3d(obj);
      
      glPopAttrib();
      glPopMatrix();
    }
  }
}

int oxygarum_add_object3d(object3d_t *object, float x, float y, float  z) {
  int id;
  id = display_object3d_counter++;
  display_objects3d = realloc(display_objects3d, display_object3d_counter * sizeof(display_obj3d_t));
  
  display_objects3d[id] = malloc(sizeof(display_obj3d_t));
  display_objects3d[id]->object = object;
  display_objects3d[id]->pos.x = x;
  display_objects3d[id]->pos.y = y;
  display_objects3d[id]->pos.z = z;
  display_objects3d[id]->rot.x = 0;
  display_objects3d[id]->rot.y = 0;
  display_objects3d[id]->rot.z = 0;
  display_objects3d[id]->shade_model = GL_FLAT;
  display_objects3d[id]->shade_program = 0;
  display_objects3d[id]->status = OBJECT_VISIBLE | OBJECT_DEPTH_BUFFERING | OBJECT_RENDER_VBO;
  
  return id;
}

void oxygarum_remove_object3d(int id) {
  free(display_objects3d[id]);
  display_objects3d[id] = NULL;
}

void oxygarum_object3d_set_shade_program(int id, GLuint shader) {
  display_objects3d[id]->shade_program = shader;
}

void oxygarum_set_shade_mode(int id, int mode) {
  display_objects3d[id]->shade_model = mode;
}

void oxygarum_enable_object3d_status(int id, int status) {
  display_objects3d[id]->status |= status;
}

void oxygarum_disable_object3d_status(int id, int status) {
  display_objects3d[id]->status &= ~status;
}

void oxygarum_translate_object3d_to(int id, float new_x, float new_y, float new_z) {
  display_objects3d[id]->pos.x = new_x;
  display_objects3d[id]->pos.y = new_y;
  display_objects3d[id]->pos.z = new_z;
}

void oxygarum_rotate_object3d_to(int id, float new_x, float new_y, float new_z) {
  display_objects3d[id]->rot.x = new_x;
  display_objects3d[id]->rot.y = new_y;
  display_objects3d[id]->rot.z = new_z;
}

void oxygarum_translate_object3d(int id, float x_off, float y_off, float z_off) {
  display_objects3d[id]->pos.x += x_off;
  display_objects3d[id]->pos.y += y_off;
  display_objects3d[id]->pos.z += z_off;
}

void oxygarum_rotate_object3d(int id, float x_off, float y_off, float z_off) {
  display_objects3d[id]->rot.x += x_off;
  display_objects3d[id]->rot.y += y_off;
  display_objects3d[id]->rot.z += z_off;
}

vertex2d_t oxygarum_get_object3d_feedback(int id) {
  return display_objects3d[id]->feedback;
}

