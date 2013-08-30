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

object3d_t *oxygarum_load_oxy3d_file(const char *path) {
  FILE *f = fopen(path, "rt");
  if(!f) {
    printf("Fehler beim öffnen!\n");
    return NULL;
  }

  char line[256];
  
  int num_vertices = 0;
  int num_uvmaps = 0;
  int num_faces = 0;  
  int i,j;  
  
  readstr(f, line);
  sscanf(line, "MATERIAL\n");
  material_t *material;

  char tex_path[256];  

  readstr(f, line);
  sscanf(line, "%s\n", tex_path);
  
  material = oxygarum_create_material("material");
  material->texture = oxygarum_load_texture(tex_path, 1);
  
  readstr(f, line);
  sscanf(line, "AMBIENT %f %f %f %f\n", 
      &material->ambient[0],
      &material->ambient[1],
      &material->ambient[2],
      &material->ambient[3]
  );
    
  readstr(f, line);
  sscanf(line, "DIFFUSE %f %f %f %f\n", 
      &material->diffuse[0], 
      &material->diffuse[1], 
      &material->diffuse[2], 
      &material->diffuse[3]
  );
    
  readstr(f, line);
  sscanf(line, "SPECULAR %f %f %f %f\n", 
      &material->specular[0], 
      &material->specular[1], 
      &material->specular[2], 
      &material->specular[3]
  );
   
  readstr(f, line);
  sscanf(line, "SHININESS %f\n", &material->shininess[0]);
  
  readstr(f, line);
  sscanf(line, "VERTICES %d\n", &num_vertices);
  vertex3d_t **vertices = calloc(num_vertices, sizeof(vertex3d_t*));
  
  for(i = 0; i < num_vertices; i++) {
    int id;
    vertex3d_t *vertex = malloc(sizeof(vertex3d_t));
    
    readstr(f, line);
    sscanf(line, "%d : %f %f %f\n", &id, &vertex->x, &vertex->y, &vertex->z);
    
    vertices[id] = vertex;
  }
  
  readstr(f, line);
  sscanf(line, "UVMAPS %d\n", &num_uvmaps);
  uv_t **uvmaps = calloc(num_uvmaps, sizeof(uv_t*));

  for(i = 0; i < num_uvmaps; i++) {
    int id;
    int size;
    
    readstr(f, line);
    sscanf(line, "%d : SIZE %d\n", &id, &size);
    
    uvmaps[id] = calloc(size, sizeof(uv_t));

    for(j = 0; j < size; j++) {
      readstr(f, line);
      sscanf(line, "%f %f\n", &uvmaps[id][j].u, &uvmaps[id][j].v);
    }
  }
  
  readstr(f, line);
  sscanf(line, "FACES %d\n", &num_faces);
  face_t **faces = calloc(num_faces, sizeof(face_t*));
  
  for(i = 0; i < num_faces; i++) {
    int id;
    int size;
    
    readstr(f, line);
    sscanf(line, "%d : SIZE %d\n", &id, &size);
    
    int uv_id;
    vertex_id *va = calloc(size, sizeof(vertex_id));
    fscanf(f, "%d", &uv_id);
    
    for(j = 0; j < size; j++) {
      fscanf(f, " %d", &va[j]);
    }
    faces[id] = oxygarum_create_face(size, va, uvmaps[uv_id]);
  }
  
  object3d_t *obj = oxygarum_create_object3d(num_vertices, vertices, num_faces, faces, material);
  fclose(f);
  
  return obj;
}

