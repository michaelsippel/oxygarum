//
// this simple demo will draw a rotating
// textured cube using the oxygarum 3D-Engine.
//
// Copyright (C) 2012-2013 Michael Sippel
// <micha.linuxfreak@gmail.com>
//

#include <oxygarum.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void readstr(FILE *f, char *string) {
    do {
	fgets(string, 255, f);
    } while ((string[0] == '/') || (string[0] == '\n'));
    return;
}

int main(int argc, char **argv) {
  oxygarum_set_resolution(800, 600);
  oxygarum_set_title("Oxygarum test");
  oxygarum_set_flag(OXYGARUM_FULLSCREEN, 0);
  init_oxygarum(argc, argv);  
  
  printf("Loading object from \'%s\'...\n", "cube.3d");
  FILE *f = fopen("cube.3d", "rt");
  if(!f) {
    printf("Fehler beim öffnen!\n");
    exit(1);
  }

  char line[256];
  
  int num_materials;
  int num_verticies;
  int num_uvmaps;
  int num_faces;  
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
  }

  readstr(f, line);
  sscanf(line, "VERTICIES %d\n", &num_verticies);
  vertex_id *verticies = calloc(num_verticies, sizeof(vertex_id));
  printf("%d verticies\n", num_verticies);
  for(i = 0; i < num_verticies; i++) {
    int id;
    vertex_t vertex;
    
    readstr(f, line);
    sscanf(line, "%d : %lf %lf %lf\n", &id, &vertex.x, &vertex.y, &vertex.z);
    
    verticies[id] = oxygarum_add_vertex(vertex);
    printf("\t%d(%d): %lf, %lf, %lf\n", id, i, vertex.x, vertex.y, vertex.z);
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

  object_t *obj = oxygarum_create_object(num_faces, faces);
  oxygarum_add_object(obj, 0, 0, 0);

  fclose(f);

  glutMainLoop();
  
  return 0;
}

