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

  printf("%s\n", log);
}

GLuint oxygarum_create_shader(char *vert_text, int vert_len, char *frag_text, int frag_len) {
  GLuint program = glCreateProgram();
  GLuint vertex_shader   = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  
  glShaderSource(vertex_shader, 1, &vert_text, &vert_len);
  glShaderSource(fragment_shader, 1, &frag_text, &frag_len);
  
  glCompileShader(vertex_shader);
  glCompileShader(fragment_shader);
  
  printf("Vertex Shader:\n");
  print_log(vertex_shader);
  
  printf("Fragment Shader:\n");
  print_log(fragment_shader);
  
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
  
  glLinkProgram(program);
  printf("\n");
  
  return program;
}

GLuint oxygarum_create_shader_from_file(const char *vertex_shader_path, const char *fragment_shader_path) {
  FILE *vert_file = fopen(vertex_shader_path, "r");
  FILE *frag_file = fopen(fragment_shader_path, "r");
  
  GLuint shader;
  
  fseek(vert_file, 0, SEEK_END);
  fseek(frag_file, 0, SEEK_END);
  int vert_len = ftell(vert_file);
  int frag_len = ftell(frag_file);
  char *vert_text = malloc(vert_len);
  char *frag_text = malloc(frag_len);
  fseek(vert_file, 0, SEEK_SET);
  fseek(frag_file, 0, SEEK_SET);
  fread(vert_text, vert_len, 1, vert_file);
  fread(frag_text, frag_len, 1, frag_file);
  
  fclose(vert_file);
  fclose(frag_file);
  
  shader = oxygarum_create_shader(vert_text, vert_len, frag_text, frag_len);
  
  free(vert_text);
  free(frag_text);
  
  return shader;
}

