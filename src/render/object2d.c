/**
 *  src/render/object2d.c
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
#include <GL/glut.h>
#include "opengl.h"
#include "vertex.h"
#include "object.h"
#include "font.h"
#include "light.h"

unsigned int display_object2d_counter = 0;
display_obj2d_t **display_objects2d;

void oxygarum_render_object2d(display_obj2d_t *obj) {
  int i;
  glTranslatef(obj->pos.x, obj->pos.y, 0);
  glRotatef(obj->rot, 0.0f,0.0f,1.0f);
  
  material_t *material = obj->object->material;
  for(i = 0; i < material->texture_counter; i++) {
    glActiveTexture(GL_TEXTURE0 + i);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, material->textures[i]->id);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  }
  
  oxygarum_display_object2d(obj->object);
}

void oxygarum_render_all_objects2d(void) {
  int i;
  for(i = 0; i < display_object2d_counter; i++) {
    if(display_objects2d[i] == NULL) {
      continue;
    }
    
    display_obj2d_t *obj = display_objects2d[i];
    if(obj->status & OBJECT_VISIBLE) {
      glPushMatrix();
      oxygarum_render_object2d(obj);
      glPopMatrix();
    }
  }
}

int oxygarum_add_object2d(object2d_t *object, float x, float y) {
  int id;
  id = display_object2d_counter++;
  display_objects2d = realloc(display_objects2d, display_object2d_counter * sizeof(display_obj2d_t*));
  
  display_objects2d[id] = malloc(sizeof(display_obj2d_t));
  display_objects2d[id]->object = object;
  display_objects2d[id]->pos.x = x;
  display_objects2d[id]->pos.y = y;
  display_objects2d[id]->rot = 0;
  display_objects2d[id]->status = OBJECT_VISIBLE | OBJECT_DEPTH_BUFFERING;
  
  return id;
}

void oxygarum_remove_object2d(int id) {
  free(display_objects2d[id]);
  display_objects2d[id] = NULL;
}

void oxygarum_enable_object2d_status(int id, int status) {
  display_objects2d[id]->status |= status;
}

void oxygarum_disable_object2d_status(int id, int status) {
  display_objects2d[id]->status &= ~status;
}

void oxygarum_translate_object2d_to(int id, float new_x, float new_y) {
  display_objects2d[id]->pos.x = new_x;
  display_objects2d[id]->pos.y = new_y;
}

void oxygarum_rotate_object2d_to(int id, float new) {
  display_objects2d[id]->rot = new;
}

void oxygarum_translate_object2d(int id, float x_off, float y_off) {
  display_objects2d[id]->pos.x += x_off;
  display_objects2d[id]->pos.y += y_off;
}

void oxygarum_rotate_object2d(int id, float off) {
  display_objects2d[id]->rot += off;
}

vertex2d_t oxygarum_get_object2d_feedback(int id) {
  return display_objects2d[id]->feedback;
}

