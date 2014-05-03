/**
 *  src/loader/shader_loader.cpp
 *
 *  Copyright (C) 2013-2014 Michael Sippel
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
#include <stdio.h>
#include <string.h>
#include "shader.h"

namespace oxygarum {
namespace loader {

Shader *load_shader(GLuint type, const char *path) {
	FILE *file = fopen(path, "r");

	fseek(file, 0, SEEK_END);
	int len = ftell(file);
	char *text = (char*) malloc(len);
	fseek(file, 0, SEEK_SET);
	fread(text, len, 1, file);
	fclose(file);

  	Shader *shader = new Shader(type, text, len);
	free(text);

	return shader;
}

};
};

