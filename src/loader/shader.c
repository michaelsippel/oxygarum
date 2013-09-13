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

void print_log(GLuint shader) {
  int blen, slen;
  char log[100];
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH , &blen);
  glGetShaderInfoLog(shader, blen, slen, &log);

  if(log[0] != '\0')
    printf("%s\n", log);
}

GLuint oxygarum_create_shader(GLuint type, char *text, int len) {
  GLuint id = glCreateShader(type);
  
  glShaderSource(id, 1, &text, &len);
  glCompileShader(id);
  print_log(id);  
  
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

