/**
 *  src/oxy3d_loader.c
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
    } while ((string[0] == '/') || (string[0] == '\n'));
    return;
}

object_t *oxygarum_load_oxy3d_file(const char *path) {
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
  printf("%d materials\n", num_materials);
  for(i = 0; i < num_materials; i++) {
    int id;
    char path[256];
    
    readstr(f, line);
    sscanf(line, "%d : %s\n", &id, path);
    
    materials[id] = oxygarum_create_material("material");
    materials[id]->texture = oxygarum_load_texture(path);
    printf("\t%d(%d): texture path: \'%s\'\n", id, i, path);
    
    readstr(f, line);
    sscanf(line, "AMBIENT %f %f %f %f\n", 
      &materials[id]->ambient[0],
      &materials[id]->ambient[1],
      &materials[id]->ambient[2],
      &materials[id]->ambient[3]
    );
    
    readstr(f, line);
    sscanf(line, "DIFFUSE %f %f %f %f\n", 
      &materials[id]->diffuse[0], 
      &materials[id]->diffuse[1], 
      &materials[id]->diffuse[2], 
      &materials[id]->diffuse[3]
    );
    
    readstr(f, line);
    sscanf(line, "SPECULAR %f %f %f %f\n", 
      &materials[id]->specular[0], 
      &materials[id]->specular[1], 
      &materials[id]->specular[2], 
      &materials[id]->specular[3]
    );
    
    readstr(f, line);
    sscanf(line, "SHININESS %f\n", &materials[id]->shininess[0]);
  }
  
  readstr(f, line);
  sscanf(line, "VERTICES %d\n", &num_vertices);
  vertex_t **vertices = calloc(num_vertices, sizeof(vertex_t*));
  printf("%d vertices\n", num_vertices);
  for(i = 0; i < num_vertices; i++) {
    int id;
    vertex_t *vertex = malloc(sizeof(vertex_t));
    
    readstr(f, line);
    sscanf(line, "%d : %lf %lf %lf\n", &id, &vertex->x, &vertex->y, &vertex->z);
    
    vertices[id] = vertex;
    printf("\t%d(%d): %lf, %lf, %lf\n", id, i, vertex->x, vertex->y, vertex->z);
  }
  
  readstr(f, line);
  sscanf(line, "UVMAPS %d\n", &num_uvmaps);
  uv_t **uvmaps = calloc(num_uvmaps, sizeof(uv_t*));
  printf("%d uvmaps\n", num_uvmaps);
  for(i = 0; i < num_uvmaps; i++) {
    int id;
    int size;
    
    readstr(f, line);
    sscanf(line, "%d : SIZE %d\n", &id, &size);
    
    uvmaps[id] = calloc(size, sizeof(uv_t));
    printf("\t%d(%d): size %d\n", id, i, size);
    for(j = 0; j < size; j++) {
      readstr(f, line);
      sscanf(line, "%lf %lf\n", &uvmaps[id][j].u, &uvmaps[id][j].v);
      printf("\t\t%d: %lf, %lf\n", j, uvmaps[id][j].u, uvmaps[id][j].v);
    }
  }
  
  readstr(f, line);
  sscanf(line, "FACES %d\n", &num_faces);
  face_t **faces = calloc(num_faces, sizeof(face_t*));
  printf("%d faces\n", num_faces);
  for(i = 0; i < num_faces; i++) {
    int id;
    int size;
    
    readstr(f, line);
    sscanf(line, "%d : SIZE %d\n", &id, &size);
    
    int uv_id, mat_id;
    vertex_id *va = calloc(size, sizeof(vertex_id));
    fscanf(f, "%d %d", &uv_id, &mat_id);
    printf("\t%d(%d): size %d\n", id, i, size);
    for(j = 0; j < size; j++) {
      fscanf(f, " %d", &va[j]);
      printf("\t\t%d: %d\n", j, va[j]);
    }
    faces[id] = oxygarum_create_face(size, va, materials[mat_id], uvmaps[uv_id]);
  }
  
  object_t *obj = oxygarum_create_object(num_vertices, vertices, num_faces, faces);
  fclose(f);
  
  return obj;
}

