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

/**
 * @author Michael Sippel <michamimosa@gmail.com>
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

namespace oxygarum {

TextureParameter::TextureParameter()
{
}

TextureParameter::TextureParameter(GLenum type_, GLenum value_)
: type(type_), value(value_)
{
}

TextureParameter::~TextureParameter()
{
}

Texture::Texture() {
	this->params = new List<TextureParameter>();
	this->id = 0;
}

Texture::Texture(unsigned int width_, unsigned int height_, uint8_t *data_) {
	this->params = new List<TextureParameter>();
	this->id = 0;
	this->load(width_, height_, 3, data_);
}

Texture::Texture(unsigned int width_, unsigned int height_, unsigned int bpp_, uint8_t *data_) {
	this->params = new List<TextureParameter>();
	this->id = 0;
	this->load(width_, height_, bpp_, data_);
}

Texture::Texture(unsigned int width_, unsigned int height_, unsigned int bpp_, uint8_t *data_, List<TextureParameter> *params_)
: params(params_) {
	this->id = 0;
	this->load(width_, height_, bpp_, data_);
}

Texture::~Texture() {
	glDeleteTextures(1, &this->id);
}

void Texture::bind(void) {
	glBindTexture(GL_TEXTURE_2D, this->id);
}

void Texture::load(unsigned int width_, unsigned int height_, unsigned int bpp_, uint8_t *data_) {
	this->width = width_;
	this->height = height_;
	this->bpp = bpp_;
	this->data = data_;

	switch(this->bpp) {
		case 3:
			this->format = GL_RGB;
			break;

		case 4:
			this->format = GL_RGBA;
			break;

		default:
			return;
	}

	this->load();
}

void Texture::load(void) {
	if(this->id == 0) {
		glGenTextures(1, &this->id);
	}
	this->bind();

	glTexImage2D(GL_TEXTURE_2D, 0, this->bpp, this->width, this->height, 0, this->format, GL_UNSIGNED_BYTE, this->data);

	if(this->params != NULL) {
		ListEntry<TextureParameter> *entry = this->params->getHead();
		while(entry != NULL) {
			TextureParameter *param = entry->element;
			glTexParameteri(GL_TEXTURE_2D, param->type, param->value);

			entry = entry->getNext();
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}

GLuint Texture::getID(void) {
	return this->id;
}

};

