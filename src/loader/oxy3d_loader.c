/**
 *  src/loader/oxy3d_loader.c
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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#include "vertex.h"
#include "face.h"
#include "object.h"
#include "material.h"
#include "texture.h"
#include "group.h"
#include "oxygarum.h"

static int end = 0;
int readstr(FILE *f, char *string) {
    int i = 0;
    do {
	if(fgets(string, 255, f) == NULL) {
          if(end == 0) {
            end = 1;
            strcpy(string, " ");
            return 0;
          } else {
            end = 0;
            return -1;
          }
        }
    } while ((string[0] == '#') || (string[0] == '\n'));
    int len = strlen(string);
    string[len-1] = '\0';
    return 0;
}
/*
struct str_enum {
  const char *str;
  GLenum val;
};

struct str_enum[] = {
{.str = "GL_TEXTURE_MIN_FILTER", .val = GL_TEXTURE_MIN_FILTER}
{.str = "GL_TEXTURE_MAG_FILTER", .val = GL_TEXTURE_MIN_FILTER}

{.str = "GL_NEAREST", .val = GL_NEAREST}
{.str = "GL_LINEAR", .val = GL_LINEAR}
{.str = "GL_NEAREST_MIPMAP_NEAREST", .val = GL_NEAREST_MIPMAP_NEAREST}
{.str = "GL_LINEAR_MIPMAP_NEAREST", .val = GL_LINEAR_MIPMAP_NEAREST}
{.str = "GL_NEAREST_MIPMAP_LINEAR", .val = GL_NEAREST_MIPMAP_LINEAR}
{.str = "GL_LINEAR_MIPMAP_LINEAR", .val = GL_LINEAR_MIPMAP_LINEAR}

{.str = "GL_TEXTURE_MIN_LOD", .val = GL_TEXTURE_MIN_FILTER}
{.str = "GL_TEXTURE_MAX_LOD", .val = GL_TEXTURE_MIN_FILTER}
{.str = "GL_TEXTURE_BASE_LEVEL", .val = GL_TEXTURE_MIN_FILTER}
{.str = "GL_TEXTURE_MAX_LEVEL", .val = GL_TEXTURE_MIN_FILTER}
{.str = "GL_TEXTURE_WRAP_R", .val = GL_TEXTURE_MIN_FILTER}
{.str = "GL_TEXTURE_WRAP_S", .val = GL_TEXTURE_MIN_FILTER}
{.str = "GL_TEXTURE_WRAP_T", .val = GL_TEXTURE_MIN_FILTER}
{.str = "GL_TEXTURE_PRIORITY", .val = GL_TEXTURE_MIN_FILTER}
{.str = "GL_TEXTURE_COMPARE_MODE", .val = GL_TEXTURE_MIN_FILTER}
{.str = "GL_TEXTURE_COMPARE_FUNC", .val = GL_TEXTURE_MIN_FILTER}
{.str = "GL_DEPTH_TEXTURE_MODE", .val = GL_TEXTURE_MIN_FILTER}
{.str = "GL_GENERATE_MIPMAP", .val = GL_TEXTURE_MIN_FILTER}


};

GLenum gl_str2enum(char *str) {
  GLenum a;
  
  return a;
}
*/

int count_char(char *string, char c) {
  int a = 0;
  
  while(*string != '\0') {
    if(*string == c) {
      a++;
    }
    string++;
  }
  
  return a;
}

struct load_return *oxygarum_load_oxy3d_file(const char *f_path, struct load_return *ret) {
  printf("loading %s\n", f_path);
  FILE *f = fopen(f_path, "rt");
  if(!f) {
    printf("Fehler beim öffnen!\n");
    return NULL;
  }
  
  if(ret == NULL) {
    ret = malloc(sizeof(struct load_return));
    memset(ret, 0, sizeof(struct load_return));
  }
  
  if(ret->textures == NULL) ret->textures = oxygarum_create_group();
  if(ret->shaders == NULL) ret->shaders = oxygarum_create_group();
  if(ret->materials == NULL) ret->materials = oxygarum_create_group();
  if(ret->meshes == NULL) ret->meshes = oxygarum_create_group();
  if(ret->objects == NULL) ret->objects = oxygarum_create_group();
  
#define CMD_INCLUDE 0
#define CMD_TEXTURE 1
#define CMD_SHADER 2
#define CMD_MATERIAL 3
#define CMD_MESH 4

#define SET_CMD(x) strcpy(name, args);cmd_id = x;
#define RESET_CMD cmd_id = -1;fseek(f, pos1, SEEK_SET);read = 0;end = 0;

  char line[256];
  int i,j,k;
  int pos1 = 0;
  int pos2 = 0;
  
  char cmd[256];
  char args[256];
  int cmd_id = -1;
  
  // create some buffers
  char name[256];
  char path[256];
  char buf[256];
  texture_t *tex = NULL;
  material_t *mat = NULL;
  GLuint shader;
  mesh3d_t *mesh = NULL;
  int read = 0;
  
  int num_vertices = 0;
  int num_normals = 0;
  int num_uvmaps = 0;
  int num_texcoords = 0;
  int num_faces = 0;
  vertex3d_t *vertices;
  vector3d_t *normals;
  uv_t *texcoords;
  face_t **faces;
  
  
  while(readstr(f, line) == 0) {
    j = 0;
    while(line[j] != ' ') {
      cmd[j] = line[j];
      j++;
    }
    cmd[j] = '\0';
    strcpy(args, line + j + 1); 

    // texture
    if(cmd_id == CMD_TEXTURE) {

      if(strcmp(cmd, "path") == 0) {
        strcpy(path, args);
      } else {
        tex = oxygarum_load_texture_from_file(path, NULL);
        oxygarum_group_add(ret->textures, (void*) tex, name);
        RESET_CMD;
      }

    // shader
    } else if(cmd_id == CMD_SHADER) {
      if(strcmp(cmd, "vsh") == 0) {
        GLint vshader = oxygarum_create_shader_from_file(GL_VERTEX_SHADER, args);
        glAttachShader(shader, vshader);
      } else if(strcmp(cmd, "fsh") == 0) {
        GLint vshader = oxygarum_create_shader_from_file(GL_FRAGMENT_SHADER, args);
        glAttachShader(shader, vshader);
      } else if(strcmp(cmd, "gsh") == 0) {
        GLint vshader = oxygarum_create_shader_from_file(GL_GEOMETRY_SHADER, args);
        glAttachShader(shader, vshader);
      } else {
        glLinkProgram(shader);
        oxygarum_group_add(ret->shaders, (void*) shader, name);
        RESET_CMD;
      }

    // material
    } else if(cmd_id == CMD_MATERIAL) {
      if(strcmp(cmd, "color") == 0) {
        int r,g,b;
        sscanf(args, "%2x%2x%2x %f", &r, &g, &b, &mat->color.color[3]);
        mat->color.color[0] = (float)r / 0xff;
        mat->color.color[1] = (float)g / 0xff;
        mat->color.color[2] = (float)b / 0xff;
      } else if(strcmp(cmd, "roughness") == 0) {
        sscanf(args, "%f", &mat->roughness);
      } else if(strcmp(cmd, "emission") == 0) {
        sscanf(args, "%f", &mat->emission);
      } else if(strcmp(cmd, "t") == 0) {
        group_entry_t *tex_entry = oxygarum_get_group_entry(ret->textures, args);
        if(tex_entry != NULL) {
          tex = (texture_t*) tex_entry->element;
          oxygarum_group_add(mat->textures, tex, tex_entry->name);
        }
      } else if(strcmp(cmd, "s") == 0) {
        shader = (GLint) oxygarum_get_group_entry(ret->shaders, args)->element;
        mat->shade_program = shader;
      } else {
        oxygarum_update_material_values(mat);
        oxygarum_group_add(ret->materials, (void*) mat, name);
        RESET_CMD;
      }

    // mesh
    } else if(cmd_id == CMD_MESH) {
      if(strcmp(cmd, "usemtl") == 0 || strcmp(cmd, "m") == 0) {
        if(read) {
          group_entry_t *mat_entry = oxygarum_get_group_entry(ret->materials, args);
          if(mat_entry != NULL) {
            mat = (material_t*) mat_entry->element;
          }
        }
      } else if(strcmp(cmd, "v") == 0) {
        if(read) {
          sscanf(args, "%f %f %f", &vertices[num_vertices].x, &vertices[num_vertices].y, &vertices[num_vertices].z);
        }
        num_vertices ++;
      } else if(strcmp(cmd, "n") == 0) {
        if(read) {
          sscanf(args, "%f %f %f", &normals[num_normals].x, &normals[num_normals].y, &normals[num_normals].z);
        }
        num_normals ++;
      } else if(strcmp(cmd, "vt") == 0) {
        if(read) {
          sscanf(args, "%f %f", &texcoords[num_texcoords].u, &texcoords[num_texcoords].v);
        }
        num_texcoords ++;
      } else if(strcmp(cmd, "f") == 0) {
        if(read) {
          int num_values = count_char(args, ' ') + 1;
          int line_pos = 0;
          
          vertex_id *face_vertices = calloc(num_values, sizeof(vertex_id));
          uv_id *face_coords = calloc(num_values, sizeof(uv_id));
          
          for(j = 0; j < num_values; j++) {
            k = 0;
            while(args[line_pos] != ' ') {
              buf[k] = args[line_pos];
              k++;
              line_pos++;
            }
            buf[k] = '\0';
            line_pos++;
            int num_sub_values = count_char(buf, '/');
            switch(num_sub_values) {
              case 0:
                sscanf(buf, "%d", &face_vertices[j]);
                face_vertices[j] --;
                break;
              case 1:
                sscanf(buf, "%d/%d", &face_vertices[j], &face_coords[j]);
                face_vertices[j] --;
                face_coords[j] --;
                break;
              case 2:
                //sscanf(buf, "%d/%d/%d", &face_vertices[j], &face_coords[j], &face_normals[j]);
                break;
            }
          }
          faces[num_faces] = oxygarum_create_face(num_values, face_vertices, face_coords);
        }
        num_faces ++;
      } else {
        if(read) {
          mesh3d_t *mesh = oxygarum_create_mesh3d(num_vertices, vertices, num_texcoords, texcoords, num_faces, faces, mat);
          oxygarum_group_add(ret->meshes, (void*) mesh, name);
          RESET_CMD;
        } else {
          read = 1;
          end = 0;
          fseek(f, pos2, SEEK_SET);
          vertices = calloc(num_vertices, sizeof(vertex3d_t));
          normals = calloc(num_normals, sizeof(vector3d_t));
          texcoords = calloc(num_texcoords, sizeof(uv_t));
          faces = calloc(num_faces, sizeof(face_t*));
          num_vertices = 0;
          num_normals = 0;
          num_texcoords = 0;
          num_faces = 0;
        }
      }

    // begin
    } else {
      if(strcmp(cmd, "include") == 0) {
        ret = oxygarum_load_oxy3d_file(args, ret);

      } else if(strcmp(cmd, "texture") == 0) {
        SET_CMD(CMD_TEXTURE);

      } else if(strcmp(cmd, "shader") == 0) {
        SET_CMD(CMD_SHADER);
        shader = glCreateProgram();

      } else if(strcmp(cmd, "material") == 0) {
        SET_CMD(CMD_MATERIAL);
        mat = oxygarum_create_material();

      } else if(strcmp(cmd, "mesh") == 0) {
        pos2 = ftell(f);
        mesh = NULL;
        mat = NULL;
        SET_CMD(CMD_MESH);
      }
    }

    pos1 = ftell(f);
  }
  
  fclose(f);
  
  return ret;
}

