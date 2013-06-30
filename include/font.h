/**
 *  include/font.h
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
#ifndef _FONT_H
#define _FONT_H

#include "vertex.h"
#include "texture.h"
#include "material.h"

typedef struct font {
  texture_t *texture;
  int list_base;
  unsigned int grid_width;
  unsigned int grid_height;
  unsigned int font_width;
  unsigned int font_height;
  unsigned int num_fonts;
  char ascii_start;
} font_t;

typedef struct display_text {
  font_t *font;
  char *text;
  vertex2d_t pos;
  color_t color;
} display_text_t;

font_t *oxygaurm_create_font(texture_t *texture, int w, int h, char start, float space);
void oxygaurm_display_text(font_t *font, char *text);
int oxygarum_add_text(char *text, font_t *font, float x, float y);
void oxygarum_remove_text(int id);
void oxygarum_update_text(int id, char *text, font_t *font, float x, float y);
void oxygarum_set_text_color(int id, color_t color);
void oxygarum_remove_text(int id);

#endif

