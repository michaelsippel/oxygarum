/**
 *  src/loader/shader.c
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
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "shader.h"

void oxygarum_link_program(GLuint program) {
  glLinkProgram(program);
  int len;
  glGetProgramiv(program, GL_INFO_LOG_LENGTH , &len);
  char log[len+1];
  
  if(len > 1)
    printf("Error linking program:\n", log);
}

GLuint oxygarum_create_shader(GLuint type, char *text, int len) {
  GLuint id = glCreateShader(type);
  
  glShaderSource(id, 1, &text, &len);
  glCompileShader(id);
  
  int llen;
  glGetShaderiv(id, GL_INFO_LOG_LENGTH , &llen);
  char log[llen+1];
  glGetShaderInfoLog(id, llen+1, &llen, &log);
  
  char *shadertype;
  switch(type) {
    case GL_VERTEX_SHADER:
      shadertype = "Vertexshader";
      break;
    case GL_GEOMETRY_SHADER:
      shadertype = "Geometryshader";
      break;
    case GL_FRAGMENT_SHADER:
      shadertype = "Fragmentshader";
      break;
  }
  
  if(llen > 1)
    printf("Error compiling %s:\n%s\n", shadertype, log);
  
  return id;
}

GLuint oxygarum_create_shader_from_file(GLuint type, const char *shader_path) {
  FILE *file = fopen(shader_path, "r");
  
  GLuint shader;
  
  fseek(file, 0, SEEK_END);
  int len = ftell(file);
  char *text = malloc(len);
  fseek(file, 0, SEEK_SET);
  fread(text, len, 1, file);
  fclose(file);
  
  shader = oxygarum_create_shader(type, text, len);
  
  free(text);
  
  return shader;
}

