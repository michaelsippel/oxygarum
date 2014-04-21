/**
 *  src/core/material/texture.c
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
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <png.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "texture.h"

extern SDL_Window *sdl_window;
extern SDL_Renderer *sdl_renderer;

texture_t *oxygarum_load_texture_from_file(const char *path, group_t *params) {
  texture_t *tex = (texture_t*) malloc(sizeof(texture_t));
  
  SDL_Surface *surface = IMG_Load(path);
  tex->width = surface->w;
  tex->height = surface->h;
  tex->data = surface->pixels;

  tex->bpp = surface->format->BytesPerPixel;
  int mask       = surface->format->Rmask;

  switch(tex->bpp) {
    case 3:
      if (mask == 0x000000ff){
        tex->format = GL_RGB;
      } else {
        tex->format = GL_BGR;
      }
      break;
    case 4:
      if (mask == 0x000000ff){
        tex->format = GL_RGBA;
      } else {
        tex->format = GL_BGRA;
      }
      break;
    default: 
      return NULL;
  }

  // flip image
  int i,j,k;
  uint8_t tmp;
  #define SWAP(a,b) {tmp = a; a = b; b = tmp;}
  for(i = 0 ; i < (tex->height / 2); i++) {
    for(j = 0 ; j < tex->width * tex->bpp; j += tex->bpp) {
      for(k = 0; k < tex->bpp; k++) {
        SWAP(tex->data[(i * tex->width * tex->bpp) + j + k],
        tex->data[((tex->height - i - 1) * tex->width * tex->bpp) + j + k]);
      }
    }
  }

  oxygarum_load_texture(tex, params);  

  return tex;
}

void oxygarum_load_texture(texture_t *tex, group_t *params) {
  glGenTextures(1, &tex->id);
  glBindTexture(GL_TEXTURE_2D, tex->id);
  
  glTexImage2D(GL_TEXTURE_2D, 0, tex->bpp, tex->width, tex->height, 0, tex->format, GL_UNSIGNED_BYTE, tex->data);
  
  if(params != NULL) {
    group_entry_t *entry = params->head;
    while(entry != NULL) {
      texture_parameter_t *param = (texture_parameter_t*) entry->element;
      glTexParameteri(GL_TEXTURE_2D, param->type, param->value);
      
      entry = entry->next;
    }
  }
  
  glGenerateMipmap(GL_TEXTURE_2D);
}

