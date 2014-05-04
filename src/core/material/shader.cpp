/**
 *  src/core/material/shader.cpp
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
#include <string.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include "logger.h"
#include "material.h"
#include "shader.h"

namespace oxygarum {

Shader::Shader() {
}

Shader::Shader(GLuint type_, const char *source, int len) {
	this->compile(type_, source, len);
}

Shader::~Shader() {
	glDeleteShader(this->id);
}

void Shader::compile(GLuint type_, const char *source, int len) {
	this->type = type_;
	this->id = glCreateShader(this->type);

	glShaderSource(this->id, 1, (const GLchar**) &source, &len);
	glCompileShader(this->id);

	int llen;
	glGetShaderiv(this->id, GL_INFO_LOG_LENGTH , &llen);
	GLchar log[llen+1];
	glGetShaderInfoLog(this->id, llen+1, &llen, (GLchar*) &log);

	char *shadertype;
	switch(type) {
		case GL_VERTEX_SHADER:
			shadertype = "vertexshader";
			break;
		case GL_GEOMETRY_SHADER:
			shadertype = "geometryshader";
			break;
		case GL_FRAGMENT_SHADER:
			shadertype = "fragmentshader";
			break;
	}

	if(llen > 1) {
		this->logger->log(ERROR, "compiling %s:\n%s\n", shadertype, log);
	} else {
		this->logger->log(INFO, "shader compiled");	
	}
}

ShadeProgram::ShadeProgram() {
	this->id = glCreateProgram();
}

ShadeProgram::~ShadeProgram() {
	glDeleteProgram(this->id);
}

void ShadeProgram::attach(Shader *shader) {
	glAttachShader(this->id, shader->id);
}

void ShadeProgram::link(void) {
	glLinkProgram(this->id);
	int len;
	glGetProgramiv(this->id, GL_INFO_LOG_LENGTH , &len);
	char log[len+1];

	if(len > 1) {
		this->logger->log(ERROR, "linking program:\n", log);
	} else {
		this->logger->log(INFO, "program linked");
	}
}

void ShadeProgram::use(void) {
	glUseProgram(this->id);
}

GLuint ShadeProgram::getID(void) {
	return this->id;
}

};

