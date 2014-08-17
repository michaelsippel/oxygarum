/**
 *  src/loader/obj_loader.cpp
 *
 *  Copyright (C) 2013-2014 Michael Sippel
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.	If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @author Michael Sippel <michamimosa@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#include "vector.h"
#include "face.h"
#include "object.h"
#include "material.h"
#include "texture.h"
#include "list.h"
#include "oxygarum.h"

namespace oxygarum
{
namespace loader
{

static int end = 0;
int readstr(FILE *f, char *string)
{
    do
    {
        if(fgets(string, 255, f) == NULL)
        {
            if(end == 0)
            {
                end = 1;
                strcpy(string, " ");
                return 0;
            }
            else
            {
                end = 0;
                return -1;
            }
        }
    }
    while ((string[0] == '#') || (string[0] == '\n'));

    int len = strlen(string);
    string[len-1] = '\0';
    return 0;
}

int count_char(char *string, char c)
{
    int a = 0;

    while(*string != '\0')
    {
        if(*string == c)
        {
            a++;
        }
        string++;
    }

    return a;
}

List<Mesh3D> *load_obj(const char *path)
{
    return load_obj(path, NULL);
}

List<Mesh3D> *load_obj(const char *path, List<Material> *materials)
{
    //printf("loading %s\n", f_path);
    FILE *f = fopen(path, "rt");
    if(!f)
    {
        printf("Fehler beim öffnen!\n");
        return NULL;
    }

    List<Mesh3D> *meshes = new List<Mesh3D>();

    char line[256];
    char cmd[256];
    char args[256];
    int i,j;

    // create some buffers
    Material *mat = NULL;
    Mesh3D *mesh = NULL;
    char name[256];
    char buf[256];
    int m_read = 0;
    int read = 0;
    int start_pos = 0;

    int num_vertices = 0;
    int num_normals = 0;
    int num_texcoords = 0;
    int num_faces = 0;
    Vector3D *vertices;
    Vector3D *normals;
    Vector2D *texcoords;
    Face **faces;

    while(readstr(f, line) == 0)
    {
        i = 0;
        while(line[i] != ' ')
        {
            cmd[i] = line[i];
            i++;
        }
        cmd[i] = '\0';
        strcpy(args, line + i + 1);

        if(m_read)
        {
            if(strcmp(cmd, "usemtl") == 0)
            {
                if(read)
                {
                    if(materials != NULL)
                    {
                        mat = materials->getElement(args);
                    }
                }
            }
            else if(strcmp(cmd, "s") == 0)
            {
            }
            else if(strcmp(cmd, "v") == 0)
            {
                if(read)
                {
                    sscanf(args, "%f %f %f", &vertices[num_vertices].x, &vertices[num_vertices].y, &vertices[num_vertices].z);
                }
                num_vertices ++;
            }
            else if(strcmp(cmd, "n") == 0)
            {
                if(read)
                {
                    sscanf(args, "%f %f %f", &normals[num_normals].x, &normals[num_normals].y, &normals[num_normals].z);
                }
                num_normals ++;
            }
            else if(strcmp(cmd, "vt") == 0)
            {
                if(read)
                {
                    sscanf(args, "%f %f", &texcoords[num_texcoords].x, &texcoords[num_texcoords].y);
                }
                num_texcoords ++;
            }
            else if(strcmp(cmd, "f") == 0)
            {
                if(read)
                {
                    int num_values = count_char(args, ' ') + 1;
                    int line_pos = 0;

                    int *face_vertices = (int*) calloc(num_values, sizeof(int));
                    int *face_coords = (int*) calloc(num_values, sizeof(int));

                    for(i = 0; i < num_values; i++)
                    {
                        j = 0;
                        while(args[line_pos] != ' ' && args[line_pos] != '\0')
                        {
                            buf[j] = args[line_pos];
                            j++;
                            line_pos++;
                        }
                        buf[j] = '\0';
                        line_pos++;
                        int num_sub_values = count_char(buf, '/');

                        switch(num_sub_values)
                        {
                            case 0:
                                sscanf(buf, "%d", &face_vertices[i]);
                                face_vertices[i] --;
                                break;
                            case 1:
                                sscanf(buf, "%d/%d", &face_vertices[i], &face_coords[i]);
                                face_vertices[i] --;
                                face_coords[i] --;
                                break;
                            case 2:
                                //sscanf(buf, "%d/%d/%d", &face_vertices[i], &face_coords[i], &face_normals[i]);
                                break;
                        }
                    }
                    faces[num_faces] = new Face(num_values, face_vertices, face_coords);
                }
                num_faces ++;
            }
            else
            {
                if(read)
                {
                    mesh = new Mesh3D(num_vertices, vertices, num_texcoords, texcoords, num_faces, faces, mat);
                    meshes->add(mesh, name);
					printf("loaded mesh %s: %x\n", name, mesh);
                }
                else
                {
                    read = 1;
                    end = 0;
                    fseek(f, start_pos, SEEK_SET);
                    vertices = (Vector3D*) calloc(num_vertices, sizeof(Vector3D));
                    normals = (Vector3D*) calloc(num_normals, sizeof(Vector3D));
                    texcoords = (Vector2D*) calloc(num_texcoords, sizeof(Vector2D));
                    faces = (Face**) calloc(num_faces, sizeof(Face*));
                    num_vertices = 0;
                    num_normals = 0;
                    num_texcoords = 0;
                    num_faces = 0;
                }
            }
        }

        if(strcmp(cmd, "o") == 0)
        {
            mesh = NULL;
            mat = NULL;
            num_vertices = 0;
            num_normals = 0;
            num_texcoords = 0;
            num_faces = 0;

            strcpy(name, args);
            start_pos = ftell(f);

            m_read = 1;
        }

    }

    fclose(f);

    return meshes;
}

};
};

