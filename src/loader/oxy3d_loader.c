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

int readstr(FILE *f, char *string) {
    int i = 0;
    do {
	if(fgets(string, 255, f) == NULL) {
          return -1;
        }
    } while ((string[0] == '#') || (string[0] == '\n'));
    int len = strlen(string);
    string[len-1] = 0;
    
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

int count_arguments(FILE *f) {
  int a = -1;
  char line[256];
  char second;
  
  int pos = ftell(f);
  do {
    readstr(f, line);
    second = line[1];
    a++;
  } while(second == ' ');
  fseek(f, pos, SEEK_SET);
  
  return a;
}

struct load_return *oxygarum_load_oxy3d_file(const char *path) {
  FILE *f = fopen(path, "rt");
  if(!f) {
    printf("Fehler beim öffnen!\n");
    return NULL;
  }
  
  struct load_return *ret = malloc(sizeof(struct load_return));
  ret->textures = oxygarum_create_group();
  ret->materials = oxygarum_create_group();
  ret->meshes = oxygarum_create_group();
  ret->objects = oxygarum_create_group();
  
  char line[256];
  int i;
  
#define FOR_SUB_CMDS \
  num_args = count_arguments(f); \
  printf("[LOAD] %d arguments\n", num_args);\
  for(i = 0; i < num_args; i++) { \
    readstr(f, line); \
    sub_cmd = line[0]; \
    strcpy(params, &line[2]);
  
  char cmd[3] = "cmd";
  char sub_cmd;
  char name[256];
  char params[256];
  int pos = 0;
  int num_args = 0;  
  
  while(readstr(f, line) == 0) {
    memcpy(cmd, line, 3);
    strcpy(name, &line[4]);
    
    if(strcmp(cmd, "inc") == 0) {
      printf("[LOAD] include:\n");
      struct load_return *inc = oxygarum_load_oxy3d_file(name);
      oxygarum_group_join(ret->textures, inc->textures);
      oxygarum_group_join(ret->materials, inc->materials);
      oxygarum_group_join(ret->meshes, inc->meshes);
      oxygarum_group_join(ret->objects, inc->objects);
      printf("\tpath: %s\n", name);
    } else if(strcmp(cmd, "tex") == 0) {
      printf("[LOAD] texture:\n");
      char path[256];
      //GLenum minfilter, magfilter;
      FOR_SUB_CMDS
        switch(sub_cmd) {
          case 'p':
            strcpy(path, params);
            break;
          /*case 'f':
            char f1[32], f2[32];
            sscanf(params, "%s %s", &f1, &f2);
            if(strcmp(f1, "            

            break;*/
	}
      }
      printf("\tname: %s\n\tpath: %s\n", name, path);
      texture_t *tex = oxygarum_load_texture_from_file(path, NULL);
      oxygarum_group_add(ret->textures, (void*) tex, name);
    } else if(strcmp(cmd, "mat") == 0) {
      printf("[LOAD] material:\n");
      material_t *mat = oxygarum_create_material();
      int r,g,b;
      float roughness;
      
      char c_tex_name[256];
      group_entry_t *t_entry;
      
      FOR_SUB_CMDS
        switch(sub_cmd) {
          case 'c':
            sscanf(params, "%2x%2x%2x %f %s", &r, &g, &b, &mat->color.color[3], &c_tex_name);
            mat->color.color[0] = (float)r / 0xff;
            mat->color.color[1] = (float)g / 0xff;
            mat->color.color[2] = (float)b / 0xff;
            t_entry = oxygarum_get_group_entry(ret->textures, c_tex_name);
            if(t_entry != NULL) {
              texture_t *c_tex = (texture_t*) t_entry->element;
              oxygarum_group_add(mat->textures, c_tex, t_entry->name);
            }
            break;
          case 'r':
            sscanf(params, "%f", &roughness);
            break;
	}
      }
      printf("[LOAD] material %s:\n\tcolor: %2x%2x%2x %f\n\troughness: %f\n", name, r, g, b, mat->color.color[3], roughness);
      oxygarum_group_add(ret->materials, (void*) mat, name);
    } else if(strcmp(cmd, "msh") == 0) {
      printf("[LOAD] mesh:\n");
      int num_vertices = 0;
      int num_normals = 0;
      int num_uvmaps = 0;
      int num_texcoords = 0;
      int num_faces = 0;
      
      // count vertices
      pos = ftell(f);
      FOR_SUB_CMDS
        switch(sub_cmd) {
          case 'v':
            num_vertices ++;
            break;
          case 'n':
            num_normals ++;
            break;
          case 't':
            num_texcoords ++;
            break;
          case 'f':
            num_faces ++;
            break;
        }
      }
      printf("\t%d vertices, %d faces\n", num_vertices, num_faces);
      // TODO
    } else if(strcmp(cmd, "obj") == 0) {
      // TODO
    }
  }
  
  fclose(f);
  
  return ret;
}

