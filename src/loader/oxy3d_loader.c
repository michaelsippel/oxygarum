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

#include "vertex.h"
#include "face.h"
#include "object.h"
#include "material.h"
#include "texture.h"
#include "group.h"
#include "oxygarum.h"

void readstr(FILE *f, char *string) {
    do {
	fgets(string, 255, f);
    } while ((string[0] == '#') || (string[0] == '\n'));
    return;
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
struct load_return *oxygarum_load_oxy3d_file(const char *path) {
  FILE *f = fopen(path, "rt");
  if(!f) {
    printf("Fehler beim öffnen!\n");
    return NULL;
  }

  struct load_return *ret = malloc(sizeof(struct load_return));
  ret->textures = NULL;
  ret->materials = NULL;
  ret->meshes = NULL;
  ret->objects = NULL;
  
  char line[256];

int i;
#define FOR_SUB_CMDS(a) \
  for(i = 0; i < a; i++) { \
  readstr(f, line); \
  sub_cmd = line[0]; \
  strcpy(params, &line[2]);
  
  char cmd[3] = "cmd";
  char sub_cmd;
  char name[256];
  char params[256];
  while(1) {
    readstr(f, line);
    memcpy(cmd, line, 3);
    strcpy(name, &line[4]);
    if(strcmp(cmd, "inc") == 0) {
      struct load_return *inc = oxygarum_load_oxy3d_file(name);
      oxygarum_group_join(ret->textures, inc->textures);
      oxygarum_group_join(ret->materials, inc->materials);
      oxygarum_group_join(ret->meshes, inc->meshes);
      oxygarum_group_join(ret->objects, inc->objects);
    } else if(strcmp(cmd, "tex") == 0) {
      char path[256];
      //GLenum minfilter, magfilter;
      FOR_SUB_CMDS(1)
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
      texture_t *tex = oxygarum_load_texture_from_file(path, NULL);
      oxygarum_group_add(ret->textures, (void*) tex, name);
    } else if(strcmp(cmd, "mat") == 0) {
      material_t *mat = oxygarum_create_material();
      int r,g,b;
      float roughness;
      
      char c_tex_name[256];
      group_entry_t *t_entry;
      
      FOR_SUB_CMDS(2)
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
      oxygarum_group_add(ret->materials, (void*) mat, name);
    } else if(strcmp(cmd, "msh") == 0) {
      int num_vertices = 8;
      int num_uvmaps = 1;
      int num_faces = 6;
      
      FOR_SUB_CMDS(18)
        switch(sub_cmd) {
          case 'v':
            break;
        }
      }
    } else if(strcmp(cmd, "obj") == 0) {
      // TODO
    }
  }
  
  fclose(f);
  
  return ret;
}

