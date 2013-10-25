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

mesh2d_t *oxygarum_load_oxy2d_file(const char *path) {
  FILE *f = fopen(path, "rt");
  if(!f) {
    printf("Fehler beim öffnen!\n");
    return NULL;
  }

  char line[256];
  
  int num_vertices = 0;
  int num_uvmaps = 0;
  int num_faces = 0;
  int num_textures = 0;
  int i,j;  

  readstr(f, line);
  sscanf(line, "MATERIAL\n");
  material_t *material;
  
  readstr(f, line);
  sscanf(line, "TEXTURES %d\n", &num_textures);

  readstr(f, line);
  material = oxygarum_create_material("material");
  texture_t **tex = calloc(num_textures, sizeof(texture_t*));

  for(i = 0; i < num_textures; i++) {
    int id;
    char tex_path[256];
    
    readstr(f, line);
    sscanf(line, "%d : %s\n", &id, tex_path);
    tex[id] = oxygarum_load_texture(tex_path, LINEAR, LINEAR, LINEAR);
  }
  
  oxygarum_material_init_textures(material, num_textures, tex);
  
  readstr(f, line);
  sscanf(line, "VERTICES %d\n", &num_vertices);
  vertex2d_t *vertices = calloc(num_vertices, sizeof(vertex2d_t));

  for(i = 0; i < num_vertices; i++) {
    int id;
    float x,y;    
    
    readstr(f, line);
    sscanf(line, "%d : %f %f\n", &id, &x, &y);
    
    vertices[id].x = x;
    vertices[id].y = y;
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
    fscanf(f, "%d ", &uv_id);
    
    for(j = 0; j < size; j++) {
      fscanf(f, " %d", &va[j]);
    }
    uv_t **uvs = calloc(1, sizeof(uv_t*));
    uvs[0] = uvmaps[uv_id];
    faces[id] = oxygarum_create_face(size, va, uvs);
  }

  mesh2d_t *obj = oxygarum_create_mesh2d(num_vertices, vertices, num_faces, faces, material);
  fclose(f);
  
  return obj;
}

