/**
 *  src/render/text.c
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

unsigned int display_text_counter = 0;
display_text_t **display_texts;

void oxygarum_render_text(display_text_t *text) {
  glTranslatef(text->pos.x, text->pos.y, 0);
  glColor4f(text->color.color[0], 
            text->color.color[1], 
            text->color.color[2], 
            text->color.color[3]);
  oxygaurm_display_text(text->font, text->text);
}

void oxygarum_render_all_texts(void) {
  int i;
  for(i = 0; i < display_text_counter; i++) {
    if(display_texts[i] == NULL) {
      continue;
    }
    display_text_t *text = display_texts[i];
    
    glPushMatrix();
    oxygarum_render_text(text);
    glPopMatrix();
  }
}

int oxygarum_add_text(char *text, font_t *font, float x, float y) {
  int id;
  id = display_text_counter++;
  display_texts = realloc(display_texts, display_text_counter * sizeof(display_text_t));
  
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

