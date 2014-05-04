/**
 *  src/core/object/mesh.cpp
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

/**
 * @author Michael Sippel <michamimosa@gmail.com>
 */

#include <GL/glew.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logger.h"
#include "object.h"
#include "mesh.h"

namespace oxygarum {

RenderInstance::RenderInstance() {
	this->num_vertices = 0;
	this->num_indices = 0;

	this->index_id = 0;
	this->vertex_id = 0;
	this->normal_id = 0;
	this->texcoord_id = 0;

	this->indices = NULL;
	this->vertices = NULL;
	this->normals = NULL;
	this->texcoords = NULL;
}

RenderInstance::RenderInstance(Mesh3D *mesh_)
: mesh(mesh_) {
	this->num_vertices = 0;
	this->num_indices = 0;

	this->index_id = 0;
	this->vertex_id = 0;
	this->normal_id = 0;
	this->texcoord_id = 0;

	this->indices = NULL;
	this->vertices = NULL;
	this->normals = NULL;
	this->texcoords = NULL;

	this->create();
}

RenderInstance::~RenderInstance() {
}

void RenderInstance::render(int num_textures) {
	glBindBuffer(GL_ARRAY_BUFFER, this->normal_id);
	glNormalPointer(GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, this->vertex_id);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	int i;
	for(i = 0; i < num_textures; i++) {
		glClientActiveTexture(GL_TEXTURE0 + i);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, this->texcoord_id);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->index_id);    

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glDrawElements(GL_TRIANGLES, this->num_indices, GL_UNSIGNED_INT, NULL);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void RenderInstance::create(void) {
	int i,j,l;

	// indices
	this->num_indices = 0;
	this->num_vertices = 0;
	for(i = 0; i < mesh->num_faces; i++) {
		this->num_indices += mesh->faces[i]->num_vertices - 2;
		this->num_vertices += mesh->faces[i]->num_vertices;
	}
	this->num_indices *= 3;

	this->indices  = (unsigned int*) calloc(this->num_indices, sizeof(unsigned int));
	this->vertices = (Vector3D*) calloc(this->num_vertices, sizeof(Vector3D));
	this->normals  = (Vector3D*) calloc(this->num_vertices, sizeof(Vector3D));
	this->texcoords= (Vector2D*) calloc(this->num_vertices, sizeof(Vector2D));

	int cur_index = 0;
	int cur_vertex = 0;
	for(i = 0; i < mesh->num_faces; i++) {
		Face *face = mesh->faces[i];
		for(j = 0; j < face->num_vertices-2; j++) {
			for(l = 0; l < j+3; l++) {
				this->indices[cur_index] = cur_vertex + l;

				cur_index++;
				if(l == 0) l = j;
     		 	}
    		}

		for(j = 0; j < face->num_vertices; j++) {
			this->vertices[cur_vertex].x = mesh->vertices[face->vertices[j]].x;
			this->vertices[cur_vertex].y = mesh->vertices[face->vertices[j]].y;
			this->vertices[cur_vertex].z = mesh->vertices[face->vertices[j]].z;

			if(mesh->normals != NULL) {
				this->normals [cur_vertex].x = mesh->normals[face->vertices[j]].x;
				this->normals [cur_vertex].y = mesh->normals[face->vertices[j]].y;
				this->normals [cur_vertex].z = mesh->normals[face->vertices[j]].z;
			}

			if(mesh->texcoords != NULL && face->texcoords != NULL) {
				this->texcoords[cur_vertex].x = mesh->texcoords[face->texcoords[j]].x;
				this->texcoords[cur_vertex].y = mesh->texcoords[face->texcoords[j]].y;
			}
 
			cur_vertex++;
		}
	}

	glGenBuffers(1, &this->index_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->index_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->num_indices*sizeof(unsigned int), this->indices, GL_STATIC_DRAW);

	glGenBuffers(1, &this->vertex_id);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertex_id);
	glBufferData(GL_ARRAY_BUFFER, this->num_vertices*sizeof(Vector3D), this->vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &this->normal_id);
	glBindBuffer(GL_ARRAY_BUFFER, this->normal_id);
	glBufferData(GL_ARRAY_BUFFER, this->num_vertices*sizeof(Vector3D), this->normals, GL_STATIC_DRAW);

	glGenBuffers(1, &this->texcoord_id);
	glBindBuffer(GL_ARRAY_BUFFER, this->texcoord_id);
	glBufferData(GL_ARRAY_BUFFER, this->num_vertices*sizeof(Vector2D), this->texcoords, GL_STATIC_DRAW);

	this->logger->log(INFO, "render-instance created (%d indices, %d vertices)", this->num_indices, this->num_vertices);
}

};

