/**
 *  src/font/font.c
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
#include <string.h>
#include <GL/glut.h>

#include "font.h"

font_t *oxygaurm_create_font(texture_t *texture, int w, int h, char start, float space) {
  font_t *font = malloc(sizeof(font_t));
  
  font->texture = texture;
  font->grid_width = w;
  font->grid_height = h;
  font->font_width = texture->width / w;
  font->font_height = texture->height / h;
  font->ascii_start = start;
  font->num_fonts = w*h;
  
  font->list_base = glGenLists(0xff);
  glBindTexture(GL_TEXTURE_2D, texture->id);
  
  int x = 0, y = 0;
  float tw = 1.0f / w;
  float th = 1.0f / h;
  
  int i;
  for(i = 0; i < font->num_fonts; i++) {
    glNewList(font->list_base + i + start, GL_COMPILE);
    
    glBegin(GL_QUADS);
      glTexCoord2f(x * tw, 1 - y * th - th);
      glVertex2i(0.0f, 0.0f);
      
      glTexCoord2f(x * tw + tw, 1 - y * th - th);
      glVertex2i(font->font_width, 0.0f);
      
      glTexCoord2f(x * tw + tw, 1 - y * th);
      glVertex2i(font->font_width, font->font_height);
      
      glTexCoord2f(x * tw, 1 - y * th);
      glVertex2i(0.0f, font->font_height);
    glEnd();
    
    glTranslated(space, 0.0f, 0.0f);
    glEndList();
    
    if(++x >= w) {
      x = 0;
      y ++;
    }
  }
  
  return font;
}

void oxygaurm_display_text(font_t *font, char *text) {
  glBindTexture(GL_TEXTURE_2D, font->texture->id);
  glListBase(font->list_base);
  int len = strlen(text);
  glCallLists(len, GL_BYTE, text);
}

