/**
 *  src/core/material/texture.cpp
 *
 *  (C) Copyright 2013-2014 Michael Sippel
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

Texture::Texture() {
	params = new List<texture_parameter_t>();
}

Texture::Texture(const char *path) {
	params = new List<texture_parameter_t>();
	this->read_file(path);
}

Texture::Texture(const char *path, List<texture_parameter_t> *params_)
: params(params_) {
	this->read_file(path);
}

Texture::~Texture() {
}

void Texture::read_file(const char *path) {
	SDL_Surface *surface = IMG_Load(path);
	this->width = surface->w;
	this->height = surface->h;
	this->data = surface->pixels;

	this->bpp = surface->format->BytesPerPixel;
	int mask  = surface->format->Rmask;

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
	for(i = 0 ; i < (this->height / 2); i++) {
		for(j = 0 ; j < this->width * this->bpp; j += this->bpp) {
			for(k = 0; k < this->bpp; k++) {
				SWAP(this->data[(i * this->width * this->bpp) + j + k],
				this->data[((this->height - i - 1) * this->width * this->bpp) + j + k]);
			}
		}
	}
}

void Texture::bind(void) {
	glBindTexture(GL_TEXTURE_2D, this->id);
}

void Texture::load(void) {
  glGenTextures(1, &this->id);
  this->bind();
  
  glTexImage2D(GL_TEXTURE_2D, 0, this->bpp, this->width, this->height, 0, this->format, GL_UNSIGNED_BYTE, this->data);
  
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

