/**
 *  src/loader/oxy3d_loader.c
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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "vertex.h"
#include "face.h"
#include "object.h"
#include "material.h"
#include "texture.h"

void readstr(FILE *f, char *string) {
    do {
	fgets(string, 255, f);
    } while ((string[0] == '#') || (string[0] == '\n'));
    return;
}

GLenum gl_str2enum(char *str) {
  
}

struct load_return *oxygarum_load_oxy3d_file(const char *path) {
  FILE *f = fopen(path, "rt");
  if(!f) {
    printf("Fehler beim öffnen!\n");
    return NULL;
  }

  struct load_return *ret = malloc(sizeof(struct load_return));
  ret->textures = NULL;
  ret->materials = NULL;
  ret->meshs = NULL;
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
      group_join(ret->textures, inc->textures);
      group_join(ret->materials, inc->materials);
      group_join(ret->meshes, inc->meshes);
      group_join(ret->objects, inc->objects);
    } else if(strcmp(cmd, "tex") == 0) {
      char path[256];
      GLenum minfilter, magfilter;
      FOR_SUB_CMDS(1)
        switch(sub_cmd) {
          case 'p':
            strcpy(path, params);
            break;
          case 'f':
            char f1[32], f2[32];
            sscanf(params, "%s %s", &f1, &f2);
            if(strcmp(f1, "            

            break;
	}
      }
    } else if(strcmp(cmd, "mat") == 0) {
      
    } else if(strcmp(cmd, "msh") == 0) {
    } else if(strcmp(cmd, "obj") == 0) {
    }
  }
  
  fclose(f);
  
  return ret;
}

