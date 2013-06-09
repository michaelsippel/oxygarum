/**
 *  src/loader/oxy2d_loader.c
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

#define DEBUG 1

object2d_t *oxygarum_load_oxy2d_file(const char *path) {
  FILE *f = fopen(path, "rt");
  if(!f) {
    printf("Fehler beim öffnen!\n");
    return NULL;
  }

  char line[256];
  
  int num_materials = 0;
  int num_vertices = 0;
  int num_uvmaps = 0;
  int num_faces = 0;  
  int i,j;  
  
  readstr(f, line);
  sscanf(line, "MATERIALS %d\n", &num_materials);
  material_t **materials = calloc(num_materials, sizeof(material_t));

#if DEBUG == 1
  printf("%d materials\n", num_materials);
#endif

  for(i = 0; i < num_materials; i++) {
    int id;
    char path[256];
    
    readstr(f, line);
    sscanf(line, "%d : %s\n", &id, path);
    
    materials[id] = oxygarum_create_material("material");
    materials[id]->texture = oxygarum_load_texture(path);

#if DEBUG == 1
    printf("\t%d(%d): texture path: \'%s\'\n", id, i, path);
#endif
  }
  
  readstr(f, line);
  sscanf(line, "VERTICES %d\n", &num_vertices);
  vertex2d_t **vertices = calloc(num_vertices, sizeof(vertex2d_t*));

#if DEBUG == 1
  printf("%d vertices\n", num_vertices);
#endif

  for(i = 0; i < num_vertices; i++) {
    int id;
    vertex2d_t *vertex = malloc(sizeof(vertex2d_t));
    
    readstr(f, line);
    sscanf(line, "%d : %f %f\n", &id, &vertex->x, &vertex->y);
    
    vertices[id] = vertex;
#if DEBUG == 1
    printf("\t%d(%d): %f, %f\n", id, i, vertex->x, vertex->y);
#endif
  }
  
  readstr(f, line);
  sscanf(line, "UVMAPS %d\n", &num_uvmaps);
  uv_t **uvmaps = calloc(num_uvmaps, sizeof(uv_t*));
#if DEBUG == 1
  printf("%d uvmaps\n", num_uvmaps);
#endif
  for(i = 0; i < num_uvmaps; i++) {
    int id;
    int size;
    
    readstr(f, line);
    sscanf(line, "%d : SIZE %d\n", &id, &size);
    
    uvmaps[id] = calloc(size, sizeof(uv_t));
#if DEBUG == 1
    printf("\t%d(%d): size %d\n", id, i, size);
#endif
    for(j = 0; j < size; j++) {
      readstr(f, line);
      sscanf(line, "%f %f\n", &uvmaps[id][j].u, &uvmaps[id][j].v);
#if DEBUG == 1
      printf("\t\t%d: %f, %f\n", j, uvmaps[id][j].u, uvmaps[id][j].v);
#endif
    }
  }
  
  readstr(f, line);
  sscanf(line, "FACES %d\n", &num_faces);
  face_t **faces = calloc(num_faces, sizeof(face_t*));
#if DEBUG == 1
  printf("%d faces\n", num_faces);
#endif
  for(i = 0; i < num_faces; i++) {
    int id;
    int size;
    
    readstr(f, line);
    sscanf(line, "%d : SIZE %d\n", &id, &size);
    
    int uv_id, mat_id;
    vertex_id *va = calloc(size, sizeof(vertex_id));
    fscanf(f, "%d %d", &uv_id, &mat_id);
#if DEBUG == 1
    printf("\t%d(%d): size %d\n", id, i, size);
#endif
    for(j = 0; j < size; j++) {
      fscanf(f, " %d", &va[j]);
#if DEBUG == 1
      printf("\t\t%d: %d\n", j, va[j]);
#endif
    }
    faces[id] = oxygarum_create_face(size, va, materials[mat_id], uvmaps[uv_id]);
  }
  
  object2d_t *obj = oxygarum_create_object2d(num_vertices, vertices, num_faces, faces);
  fclose(f);
  
  return obj;
}

