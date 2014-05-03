/**
 *  src/loader/oxy3d_loader.cpp
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

namespace oxygarum {
namespace loader {

static int end = 0;
int readstr(FILE *f, char *string) {
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

struct load_return *load_oxy3d(const char *path) {
	return load_oxy3d(path, NULL);
}

struct load_return *load_oxy3d(const char *f_path, struct load_return *ret) {
	//printf("loading %s\n", f_path);
	FILE *f = fopen(f_path, "rt");
	if(!f) {
		printf("Fehler beim öffnen!\n");
		return NULL;
	}

	if(ret == NULL) {
		ret = (struct load_return*) malloc(sizeof(struct load_return));
		memset(ret, 0, sizeof(struct load_return));
	}

	if(ret->textures == NULL) ret->textures = new List<Texture>();
	if(ret->shaders == NULL) ret->shaders = new List<ShadeProgram>();
	if(ret->materials == NULL) ret->materials = new List<Material>();
	if(ret->meshes == NULL) ret->meshes = new List<Mesh3D>();
	if(ret->objects == NULL) ret->objects = new List<Object3D>();

#define CMD_INCLUDE 0
#define CMD_TEXTURE 1
#define CMD_SHADER 2
#define CMD_MATERIAL 3
#define CMD_MESH 4

#define SET_CMD(x) strcpy(name, args);cmd_id = x;
#define RESET_CMD cmd_id = -1;fseek(f, pos1, SEEK_SET);read = 0;end = 0;

	char line[256];
	int i,j;
	int pos1 = 0;
	int pos2 = 0;

	char cmd[256];
	char args[256];
	int cmd_id = -1;

	// create some buffers
	char name[256];
	char path[256];
	char buf[256];
	Texture *tex = NULL;
	Material *mat = NULL;
	ShadeProgram *shader = NULL;
	Mesh3D *mesh = NULL;
	int read = 0;

	int num_vertices = 0;
	int num_normals = 0;
	int num_texcoords = 0;
	int num_faces = 0;
	Vector3D *vertices;
	Vector3D *normals;
	Vector2D *texcoords;
	Face **faces;

	while(readstr(f, line) == 0) {
		i = 0;
		while(line[i] != ' ') {
			cmd[i] = line[i];
			i++;
		}
		cmd[i] = '\0';
		strcpy(args, line + i + 1);

		// texture
		if(cmd_id == CMD_TEXTURE) {
			if(strcmp(cmd, "path") == 0) {
				strcpy(path, args);
			} else {
				tex = load_texture(path);
				ret->textures->add(tex, name);
				RESET_CMD;
			}

		// shader
		} else if(cmd_id == CMD_SHADER) {
			if(strcmp(cmd, "vsh") == 0) {
				Shader *vshader = load_shader(GL_VERTEX_SHADER, args);
				shader->attach(vshader);
			} else if(strcmp(cmd, "fsh") == 0) {
				Shader *fshader = load_shader(GL_FRAGMENT_SHADER, args);
				shader->attach(fshader);
			} else if(strcmp(cmd, "gsh") == 0) {
				Shader *gshader = load_shader(GL_GEOMETRY_SHADER, args);
				shader->attach(gshader);
			} else {
				shader->link();
				ret->shaders->add(shader, name);
				RESET_CMD;
			}

		// material
		} else if(cmd_id == CMD_MATERIAL) {
			if(strcmp(cmd, "color") == 0) {
				int r,g,b;
				sscanf(args, "%2x%2x%2x %f", &r, &g, &b, &mat->color.a);
				mat->color.r = (float)r / 0xff;
				mat->color.g = (float)g / 0xff;
				mat->color.b = (float)b / 0xff;
			} else if(strcmp(cmd, "roughness") == 0) {
				sscanf(args, "%f", &mat->roughness);
			} else if(strcmp(cmd, "emission") == 0) {
				sscanf(args, "%f", &mat->emission);
			} else if(strcmp(cmd, "refractivity") == 0) {
				sscanf(args, "%f", &mat->refractivity);
			} else if(strcmp(cmd, "tex") == 0) {
				int pos;
				sscanf(args, "%d %s %s", &pos, buf, path);
				ListEntry<Texture> *tex_entry = ret->textures->getEntry(path);
				mat->map_texture(tex_entry->element, buf, pos);
			} else if(strcmp(cmd, "shading") == 0) {
				shader = ret->shaders->getEntry(args)->element;
				mat->shade_program = shader;
			} else {
				mat->update_values();
				ret->materials->add(mat, name);
				RESET_CMD;
			}

		// mesh
		} else if(cmd_id == CMD_MESH) {
			if(strcmp(cmd, "usemtl") == 0 || strcmp(cmd, "m") == 0) {
				if(read) {
					ListEntry<Material> *mat_entry = ret->materials->getEntry(args);
					if(mat_entry != NULL) {
						mat = mat_entry->element;
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
					sscanf(args, "%f %f", &texcoords[num_texcoords].x, &texcoords[num_texcoords].y);
				}
				num_texcoords ++;
			} else if(strcmp(cmd, "f") == 0) {
				if(read) {
					int num_values = count_char(args, ' ') + 1;
					int line_pos = 0;

					int *face_vertices = (int*) calloc(num_values, sizeof(int));
					int *face_coords = (int*) calloc(num_values, sizeof(int));

					for(i = 0; i < num_values; i++) {
						j = 0;
						while(args[line_pos] != ' ') {
							buf[j] = args[line_pos];
							j++;
							line_pos++;
						}
						buf[j] = '\0';
						line_pos++;
						int num_sub_values = count_char(buf, '/');
						switch(num_sub_values) {
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
			} else {
				if(read) {
					Mesh3D *mesh = new Mesh3D(num_vertices, vertices, num_texcoords, texcoords, num_faces, faces, mat);
					ret->meshes->add(mesh, name);
					RESET_CMD;
				} else {
					read = 1;
					end = 0;
					fseek(f, pos2, SEEK_SET);
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

		// begin
		} else {
			if(strcmp(cmd, "include") == 0) {
				ret = load_oxy3d(args, ret);

			} else if(strcmp(cmd, "texture") == 0) {
				SET_CMD(CMD_TEXTURE);

			} else if(strcmp(cmd, "shader") == 0) {
				SET_CMD(CMD_SHADER);
				shader = new ShadeProgram();

			} else if(strcmp(cmd, "material") == 0) {
				SET_CMD(CMD_MATERIAL);
				mat = new Material();

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

};
};

