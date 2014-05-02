/**
 *  src/core/material/material.cpp
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

#include <stdlib.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include "material.h"
#include "shader.h"

namespace oxygarum {

Material::Material() {
	this->textures = new List<mapped_texture>();

	this->color = Color();
	this->roughness = 0.8f;
	this->emission = 0.0f;
	this->refractivity = 0.5f;
	this->shade_program = 0;
	this->update_values();
}

Material::Material(Color color_)
: color(color_) {
	this->textures = new List<mapped_texture>();

	this->roughness = 0.8f;
	this->emission = 0.0f;
	this->refractivity = 0.5f;
	this->shade_program = 0;
	this->update_values();
}

Material::~Material() {
}

void Material::update_values() {
	// ambient
	this->gl_ambient[0] = (GLfloat) 1.0f;
	this->gl_ambient[1] = (GLfloat) 1.0f;
	this->gl_ambient[2] = (GLfloat) 1.0f;
	this->gl_ambient[3] = (GLfloat) 1.0f;
 
	// diffuse
	this->gl_diffuse[0] = (GLfloat) this->roughness;
	this->gl_diffuse[1] = (GLfloat) this->roughness;
	this->gl_diffuse[2] = (GLfloat) this->roughness;
	this->gl_diffuse[3] = (GLfloat) 1.0f;

	// specular
	this->gl_specular[0] = (GLfloat) 1.0f - this->roughness;
	this->gl_specular[1] = (GLfloat) 1.0f - this->roughness;
	this->gl_specular[2] = (GLfloat) 1.0f - this->roughness;
	this->gl_specular[3] = (GLfloat) 1.0f;
  
	// emission
	this->gl_emission[0] = (GLfloat) this->emission;
	this->gl_emission[1] = (GLfloat) this->emission;
	this->gl_emission[2] = (GLfloat) this->emission;
	this->gl_emission[3] = (GLfloat) 1.0;

	// shininess
	this->gl_shininess[0] = (GLfloat) this->refractivity;
}

GLint Material::map_texture(Texture *tex, char *name, GLint mapping) {
	mapped_texture_t *mapped_tex = (mapped_texture_t*) malloc(sizeof(mapped_texture_t));

	mapped_tex->texture = tex;
	mapped_tex->location = glGetUniformLocation(this->shade_program, name);
	mapped_tex->mapping = mapping;

	this->textures->add(mapped_tex);

	return mapped_tex->location;
}

void Material::use(void) {
	glUseProgram(this->shade_program);

	ListEntry<mapped_texture> *entry = this->textures->getHead();
	int i = 0;
	while(entry != NULL) {
		mapped_texture_t *mapped_tex = entry->element;
		glActiveTexture(GL_TEXTURE0 + mapped_tex->mapping);

		glEnable(GL_TEXTURE_2D);
		mapped_tex->texture->bind();
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		if(this->shade_program != 0) {
			glUniform1i(mapped_tex->location, mapped_tex->mapping);
		}

		entry = entry->getNext();
		i++;
	}

	this->color.use();
	glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat*) &this->gl_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat*) &this->gl_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat*) &this->gl_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, (GLfloat*) &this->gl_emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, (GLfloat*) &this->gl_shininess);
}

};

