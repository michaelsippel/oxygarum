/**
 *  src/render/display.c
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
#include <unistd.h>
#include <stdio.h>
#include <GL/glut.h>
#include "opengl.h"
#include "vertex.h"
#include "object.h"
#include "font.h"
#include "light.h"

static vertex3d_t loc = {.x = 0, .y = 0, .z = 0};
static vertex3d_t rot = {.x = 0, .y = 0, .z = 0};
void (*oxygarum_animate)(void);

unsigned int display_object3d_counter = 0;
unsigned int display_object2d_counter = 0;
unsigned int display_text_counter = 0;
display_obj3d_t **display_objects3d;
display_obj2d_t **display_objects2d;
display_text_t **display_texts;
unsigned int absolute_light_counter = 0;
light_t **absolute_lights;

static int frame_counter = 0;
static int time_cur = 0, time_prev = 0, time_diff = 0;
static float fps = 0;
static float frame_time = 0;
static float max_fps = 0;

void oxygarum_calc_fps(void) {
  frame_counter++;
  time_cur = glutGet(GLUT_ELAPSED_TIME);
  
  time_diff = time_cur - time_prev;
  frame_time = time_diff / frame_counter;
  if(time_diff > 1000) {
    fps = frame_counter / (time_diff / 1000.0f);
    time_prev = time_cur;
    frame_counter = 0;
  }
}

void oxygarum_animation_func(void (*handler)(void)) {
  oxygarum_animate = handler;
}

float oxygarum_get_fps(void) {
  return fps;
}

float oxygarum_get_frametime(void) {
  return frame_time;
}

void oxygarum_set_max_fps(float _max_fps) {
  max_fps = _max_fps;
}

void oxygarum_update(void) {
  oxygarum_calc_fps();
  
  // Animate
  if(oxygarum_animate)
    oxygarum_animate();
  
  glutPostRedisplay();
}

void oxygarum_timer(int value) {
  oxygarum_update();
  if(max_fps > 0) {
    float min_time = 1000000/max_fps;
    float wait_time = min_time - frame_time;
    glutTimerFunc(wait_time/1000, &oxygarum_timer, 0);
  }
}

void oxygarum_idle(void) {
  if(! (max_fps > 0)) {
    oxygarum_update();
  }
}

void oxygarum_display(void) {
  int i,j;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.1, 0.1, 0.1, 1.0);  
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  glRotatef(rot.x, 1.0f,0.0f,0.0f);
  glRotatef(rot.y, 0.0f,1.0f,0.0f);
  glRotatef(rot.z, 0.0f,0.0f,1.0f);  
  
  glTranslatef(loc.x, loc.y, loc.z);
  
  for(i = 0; i < absolute_light_counter; i++) {
    light_t *l = absolute_lights[i];
    glLightfv(l->gl_light, GL_POSITION, l->pos);
  }
  
  float feedback[3] = {-1.0f, -1.0f, -1.0f};  
  

  for(i = 0; i < display_object3d_counter; i++) {
    if(display_objects3d[i] == NULL) {
      continue;
    }
    
    display_obj3d_t *obj = display_objects3d[i];
    if(obj->status & OBJECT_VISIBLE) {
      glPushMatrix();
      
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
      
      glPushAttrib(GL_ENABLE_BIT);
      
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
      
      for(j = 0; j < material->texture_counter; j++) {
        glActiveTexture(GL_TEXTURE0 + j);
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, material->textures[j]->id);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
      }
      
      glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
      glMaterialfv(GL_FRONT, GL_SHININESS, material->shininess);
      
      glShadeModel(obj->shade_model);
      if(obj->glsl) {
        glUseProgram(obj->shader);
      }      
      
      if(obj->status & OBJECT_RENDER_VBO) {
        glBindBuffer(GL_ARRAY_BUFFER, obj->object->vbo_normal_id);
        glNormalPointer(GL_FLOAT, 0, NULL);
        
        glBindBuffer(GL_ARRAY_BUFFER, obj->object->vbo_vertex_id);
        glVertexPointer(3, GL_FLOAT, 0, NULL);

        for(j = 0; j < material->texture_counter; j++) {
          glClientActiveTexture(GL_TEXTURE0 + j);
          glEnableClientState(GL_TEXTURE_COORD_ARRAY);
          glBindBuffer(GL_ARRAY_BUFFER, obj->object->vbo_tex_id[j]);
          glTexCoordPointer(2, GL_FLOAT, 0, NULL);
        }        

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->object->vbo_index_id);    
        
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glDrawElements(GL_TRIANGLES, obj->object->vbo_index_counter, GL_UNSIGNED_INT, NULL);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
      } else {
        oxygarum_display_object3d(obj->object);
      }
      
      glPopAttrib();
      glPopMatrix();
    }
  }
  
  glPushAttrib(GL_ENABLE_BIT);
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  // display fonts and 2d-objects
  
  glOrtho(0, oxygarum_get_width(), 0, oxygarum_get_height(), -1, 1); 
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  for(i = 0; i < display_object2d_counter; i++) {
    if(display_objects2d[i] == NULL) {
      continue;
    }
    
    display_obj2d_t *obj = display_objects2d[i];
    if(obj->status & OBJECT_VISIBLE) {
      glPushMatrix();
      
      glTranslatef(obj->pos.x, obj->pos.y, 0);
      glRotatef(obj->rot, 0.0f,0.0f,1.0f);
      
      material_t *material = obj->object->material;
      for(j = 0; j < material->texture_counter; j++) {
        glActiveTexture(GL_TEXTURE0 + j);
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, material->textures[j]->id);
        if(i == 0) {
          glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        } else {
          glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        }
      }
      
      oxygarum_display_object2d(obj->object);
      
      glPopMatrix();
    }
  }
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, oxygarum_get_width(), 0, oxygarum_get_height(), -1, 1); 
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  for(i = 0; i < display_text_counter; i++) {
    if(display_texts[i] == NULL) {
      continue;
    }
    display_text_t *text = display_texts[i];
    
    glPushMatrix();
    
    glTranslatef(text->pos.x, text->pos.y, 0);
    glColor4f(text->color.color[0], 
              text->color.color[1], 
              text->color.color[2], 
              text->color.color[3]);
    oxygaurm_display_text(text->font, text->text);
    
    glPopMatrix();
  }
  
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  
  glPopAttrib();
  
  glFlush();
  glutSwapBuffers();
}

int oxygarum_add_object3d(object3d_t *object, float x, float y, float  z) {
  int id;
  id = display_object3d_counter++;
  
  if(display_object3d_counter > 0) {
    display_objects3d = realloc(display_objects3d, display_object3d_counter * sizeof(display_obj3d_t));
  } else {
    display_objects3d = malloc(sizeof(display_obj3d_t));
  }
  
  display_objects3d[id] = malloc(sizeof(display_obj3d_t));
  display_objects3d[id]->object = object;
  display_objects3d[id]->pos.x = x;
  display_objects3d[id]->pos.y = y;
  display_objects3d[id]->pos.z = z;
  display_objects3d[id]->rot.x = 0;
  display_objects3d[id]->rot.y = 0;
  display_objects3d[id]->rot.z = 0;
  display_objects3d[id]->shade_model = GL_FLAT;
  display_objects3d[id]->glsl = 0;
  display_objects3d[id]->status = OBJECT_VISIBLE | OBJECT_DEPTH_BUFFERING | OBJECT_RENDER_VBO;
  
  return id;
}
void oxygarum_object3d_use_glsl(int id, GLuint shader) {
  display_objects3d[id]->shader = shader;
  display_objects3d[id]->glsl = 1;
}
void oxygarum_remove_object3d(int id) {
  free(display_objects3d[id]);
  display_objects3d[id] = NULL;
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

int oxygarum_add_object2d(object2d_t *object, float x, float y) {
  int id;
  id = display_object2d_counter++;
  
  if(display_object2d_counter > 0) {
    display_objects2d = realloc(display_objects2d, display_object2d_counter * sizeof(display_obj2d_t));
  } else {
    display_objects2d = malloc(sizeof(display_obj2d_t));
  }
  
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

int oxygarum_add_text(char *text, font_t *font, float x, float y) {
  int id;
  id = display_text_counter++;
  if(display_text_counter > 0) {
    display_texts = realloc(display_texts, display_text_counter * sizeof(display_text_t));
  } else {
    display_texts = malloc(sizeof(display_text_t));
  }
  
  display_texts[id] = malloc(sizeof(display_text_t));
  display_texts[id]->text = text;
  display_texts[id]->font = font;
  display_texts[id]->pos.x = x;
  display_texts[id]->pos.y = y;
  display_texts[id]->color.rgb = (color_st_t) {.r = 1, .b = 1, .g = 1, .a = 1};
  
  return id;
}
void oxygarum_remove_text(int id) {
  free(display_texts[id]);
  display_texts[id] = NULL;
}
void oxygarum_update_text(int id, char *text, font_t *font, float x, float y) {
  display_texts[id]->pos.x = x;
  display_texts[id]->pos.y = y;
  
  if(text != NULL) display_texts[id]->text = text;
  if(font != NULL) display_texts[id]->font = font;
}
void oxygarum_set_text_color(int id, color_t color) {
  display_texts[id]->color = color;
}

int oxygarum_add_light(light_t *light, int light_pos) {
  glLightfv(light->gl_light, GL_AMBIENT,  light->ambient);
  glLightfv(light->gl_light, GL_DIFFUSE,  light->diffuse);
  glLightfv(light->gl_light, GL_SPECULAR, light->specular);
  glLightfv(light->gl_light, GL_POSITION, light->pos);
  
  glEnable(light->gl_light);
  
  if(light_pos == LIGHT_POSITION_ABSOLUTE) {
    int id;
    id = absolute_light_counter++;
    if(absolute_light_counter > 0) {
      absolute_lights = realloc(absolute_lights, absolute_light_counter * sizeof(light_t));
    } else {
      absolute_lights = malloc(sizeof(light_t));
    }
    
    absolute_lights[id] = light;
    return id;
  }
  
  return -1;
}
void oxygarum_remove_absolute_light(int id) {
  free(absolute_lights[id]);
  absolute_lights[id] = NULL;
}

void oxygarum_translate_camera_to(float new_x, float new_y, float new_z) {
  loc.x = new_x;
  loc.y = new_y;
  loc.z = new_z;
}
void oxygarum_rotate_camera_to(float new_x, float new_y, float new_z) {
  rot.x = new_x;
  rot.y = new_y;
  rot.z = new_z;
}
void oxygarum_translate_camera(float x_off, float y_off, float z_off) {
  loc.x += x_off;
  loc.y += y_off;
  loc.z += z_off;
}
void oxygarum_rotate_camera(float x_off, float y_off, float z_off) {
  rot.x += x_off;
  rot.y += y_off;
  rot.z += z_off;
}

