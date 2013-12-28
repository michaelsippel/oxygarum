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
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "texture.h"

extern SDL_Window *sdl_window;
extern SDL_Renderer *sdl_renderer;

static texture_id texture_counter = 0;

texture_t *oxygarum_load_texture(const char *path, int minfilter, int magfilter, int mipmapping) {
  texture_t *tex = (texture_t*) malloc(sizeof(texture_t));
  /* FIXME: why this don't work?
  SDL_Texture *sdltex = IMG_LoadTexture(sdl_renderer, path);
  uint32_t format;
  int access;

  if(SDL_QueryTexture(sdltex, &format, &access, &tex->width, &tex->height) != 0) {
    printf("Can't query texture!\n");
    return;   
  }

  int pitch;
  if(SDL_QueryTexturePixels(sdltex, &tex->data, &pitch) != 0) {
    printf("Can't query pixels!\n");
    return;
  } 

  */

  SDL_Surface *surface = IMG_Load(path);
  tex->width = surface->w;
  tex->height = surface->h;
  tex->data = surface->pixels;

  // get the number of channels in the SDL surface
  tex->num_colors = surface->format->BytesPerPixel;
  int mask       = surface->format->Rmask;

  switch(tex->num_colors) {
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
      return;
  }

  glGenTextures(1, &tex->id);
  glBindTexture(GL_TEXTURE_2D, tex->id);
  
  glTexImage2D(GL_TEXTURE_2D, 0, tex->num_colors, tex->width, tex->height, 0, tex->format, GL_UNSIGNED_BYTE, tex->data);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
  switch(minfilter) {
    case LINEAR:
      switch(mipmapping) {
        case NO_MIPMAP:
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
          break;
        case LINEAR:
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
          break;
        case NEAREST:
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
          break;
      }
      break;
    case NEAREST:
      switch(mipmapping) {
        case NO_MIPMAP:
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
          break;
        case LINEAR:
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
          break;
        case NEAREST:
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
          break;
      }
      break;
  }

  switch(magfilter) {
    case LINEAR:
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      break;
    case NEAREST:
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      break;
  }
  
  if(mipmapping != NO_MIPMAP) {
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  
  return tex;
}

