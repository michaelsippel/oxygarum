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
  material->textures = oxygarum_create_group();

  material->color.rgb.r = 1.0f;
  material->color.rgb.b = 1.0f;
  material->color.rgb.g = 1.0f;
  material->color.rgb.a = 1.0f;
  
  material->roughness = 0.8f;
  material->emission = 0.0f;
  material->refractivity = 0.0f;
  
  material->shade_model = 0; 
  
  oxygarum_update_material_values(material);
  
  return material;
}

void oxygarum_update_material_values(material_t *material) {
  // ambient
  material->gl_ambient[0] = (GLfloat) 1.0f;
  material->gl_ambient[1] = (GLfloat) 1.0f;
  material->gl_ambient[2] = (GLfloat) 1.0f;
  material->gl_ambient[3] = (GLfloat) 1.0f;
  
  // diffuse
  material->gl_diffuse[0] = (GLfloat) material->roughness;
  material->gl_diffuse[1] = (GLfloat) material->roughness;
  material->gl_diffuse[2] = (GLfloat) material->roughness;
  material->gl_diffuse[3] = (GLfloat) 1.0f;
  
  // specular
  material->gl_specular[0] = (GLfloat) 1.0f - material->roughness;
  material->gl_specular[1] = (GLfloat) 1.0f - material->roughness;
  material->gl_specular[2] = (GLfloat) 1.0f - material->roughness;
  material->gl_specular[3] = (GLfloat) 1.0f;
  
  // emission
  material->gl_emission[0] = (GLfloat) material->emission;
  
  // shininess
  material->gl_shininess[0] = (GLfloat) 0.0f;
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
      
      entry = entry->next;
      i++;
    }
    
    glColor4fv(&material->color.color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, &material->gl_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &material->gl_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, &material->gl_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, &material->gl_emission);
    glMaterialfv(GL_FRONT, GL_SHININESS, &material->gl_shininess);
    
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

