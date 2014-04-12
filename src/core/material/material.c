/**
 *  src/core/material/material.c
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
#include <stdlib.h>

#include "material.h"

material_t *oxygarum_create_material(void) {
  material_t *material = malloc(sizeof(material_t));
  material->color.rgb = (color_st_t) {.r=1,.g=1,.b=1,.a=1};
  material->textures = oxygarum_create_group();
  
  memcpy(&material->ambient,  (GLfloat[]){ 0.2f, 0.2f, 0.2f, 1.0f }, sizeof(material->ambient));
  memcpy(&material->diffuse,  (GLfloat[]){ 1.0f, 1.0f, 1.0f, 1.0f }, sizeof(material->diffuse));
  memcpy(&material->specular, (GLfloat[]){ 0.8f, 0.8f, 0.8f, 1.0f }, sizeof(material->specular));
  memcpy(&material->shininess,(GLfloat[]){ 1.0f },                   sizeof(material->shininess));
  
  return material;
}

void oxygarum_use_material(material_t *material) {
  if(material != NULL) {
    group_entry_t *entry = material->textures->head;
    int i = 0;
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

    glShadeModel(material->shade_model);
    glUseProgram(material->shade_program);

    GLint tex0 = glGetUniformLocation(material->shade_program, "Texture0");
    GLint tex1 = glGetUniformLocation(material->shade_program, "Texture1");
    GLint tex2 = glGetUniformLocation(material->shade_program, "Texture2");  

    glUniform1i(tex0, 0);
    glUniform1i(tex1, 1);
    glUniform1i(tex2, 2);
  }
}

