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

#include <xml.h>

#include "vector.h"
#include "face.h"
#include "object.h"
#include "material.h"
#include "texture.h"
#include "list.h"
#include "loader.h"
#include "oxygarum.h"

namespace oxygarum
{
namespace loader
{

struct load_return *load_oxy3d(const char *path)
{
    return load_oxy3d(path, NULL);
}

struct load_return *load_oxy3d(const char *path, struct load_return *ret)
{
    if(ret == NULL)
    {
        ret = (struct load_return*) malloc(sizeof(struct load_return));
        memset(ret, 0, sizeof(struct load_return));
    }

    if(ret->textures == NULL) ret->textures = new List<Texture>();
    if(ret->shaders == NULL) ret->shaders = new List<ShadeProgram>();
    if(ret->materials == NULL) ret->materials = new List<Material>();
    if(ret->meshes == NULL) ret->meshes = new List<Mesh3D>();
    if(ret->objects == NULL) ret->objects = new List<Object3D>();

	XMLNode *base_node = new XMLNode(path);

	ListEntry<XMLNode> *entry = base_node->subnodes->getHead();
	while(entry != NULL)
	{
		XMLNode *node = entry->element;
		if(strcmp(node->name, "program") == 0)
		{
			XMLParam *p = node->getParam("name");
			if(p != NULL)
			{
				ShadeProgram *prog = new ShadeProgram();

				ListEntry<XMLNode> *s_entry = node->subnodes->getHead();
				while(s_entry != NULL)
				{
					XMLNode *s_node = s_entry->element;
					if(strcmp(s_node->name, "shader") == 0)
					{
						XMLParam *type_p = s_node->getParam("type");
						if(type_p != NULL)
						{
							GLuint type;
							if(strcmp(type_p->value, "vertexshader") == 0)
							{
								type = GL_VERTEX_SHADER;
							}
							else if(strcmp(type_p->value, "fragmentshader") == 0)
							{
								type = GL_FRAGMENT_SHADER;
							}
							else if(strcmp(type_p->value, "geometryshader") == 0)
							{
								type = GL_GEOMETRY_SHADER;
							}

							printf("load %s\n", s_node->text);
							Shader *shader = load_shader(type, s_node->text);
							prog->attach(shader);
						}
					}
					s_entry = s_entry->getNext();
				}

				prog->link();
				printf("add %s\n", p->value);
				ret->shaders->add(prog, p->value);
			}
		}
		else if(strcmp(node->name, "texture") == 0)
		{
			XMLParam *p = node->getParam("name");
			if(p != NULL)
			{
				printf("load %s\n", node->text);
				Texture *tex = load_texture(node->text);
				printf("add %s\n", p->value);
				ret->textures->add(tex, p->value);
			}
		}
		else if(strcmp(node->name, "material") == 0)
		{
			XMLParam *p = node->getParam("name");
			if(p != NULL)
			{
				Material *mat = new Material();

				ListEntry<XMLNode> *m_entry = node->subnodes->getHead();
				while(m_entry != NULL)
				{
					XMLNode *m_node = m_entry->element;
					if(strcmp(m_node->name, "color") == 0)
					{
						XMLParam *color_p = m_node->getParam("value");
						if(color_p != NULL)
						{
							int r,g,b;
							sscanf(color_p->value, "#%2x%2x%2x", &r, &g, &b);
							mat->color.r = (float) r / 256;
							mat->color.g = (float) g / 256;
							mat->color.b = (float) b / 256;
						}

						XMLParam *alpha_p = m_node->getParam("alpha");
						if(alpha_p != NULL)
						{
							sscanf(alpha_p->value, "%f", &mat->color.a);
						}
					}
					else if(strcmp(m_node->name, "param") == 0)
					{
						XMLParam *type_p = m_node->getParam("type");
						XMLParam *value_p = m_node->getParam("value");

						if(type_p != NULL && value_p != NULL)
						{
							if(strcmp(type_p->value, "roughness") == 0)
							{
								sscanf(value_p->value, "%f", &mat->roughness);
							}
							else if(strcmp(type_p->value, "emission") == 0)
							{
								sscanf(value_p->value, "%f", &mat->emission);
							}
						}
					}
					else if(strcmp(m_node->name, "shading") == 0)
					{
						mat->shade_program = ret->shaders->getElement(m_node->text);
					}
					else if(strcmp(m_node->name, "texture") == 0)
					{
						XMLParam *id_p = m_node->getParam("id");
						XMLParam *name_p = m_node->getParam("name");

						if(id_p != NULL && name_p != NULL)
						{
							Texture *tex = ret->textures->getElement(m_node->text);
							if(tex != NULL)
							{
								int id;
								sscanf(id_p->value, "%d", &id);
								mat->map_texture(tex, name_p->value, id);
							}
						}
					}

					m_entry = m_entry->getNext();
				}

				ret->materials->add(mat, p->value);
			}
		}
		else if(strcmp(node->name, "obj") == 0)
		{
			printf("load %s\n", node->text);
			List<Mesh3D> *meshes = load_obj(node->text, ret->materials);
			ret->meshes->join(meshes);
		}
		else if(strcmp(node->name, "object") == 0)
		{
			XMLParam *p = node->getParam("name");
			if(p != NULL)
			{
				Object3D *obj = new Object3D();

				ListEntry<XMLNode> *o_entry = node->subnodes->getHead();
				while(o_entry != NULL)
				{
					XMLNode *o_node = o_entry->element;
					if(strcmp(o_node->name, "mesh") == 0)
					{
						obj->mesh = ret->meshes->getElement(o_node->text);
						printf("%x\n", obj->mesh);
					}

					o_entry = o_entry->getNext();
				}

				printf("add %s\n", p->value);
				ret->objects->add(obj, p->value);
			}
		}

		entry = entry->getNext();
	}

    return ret;
}

};
};

