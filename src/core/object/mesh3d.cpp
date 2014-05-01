/**
 *  src/object/mesh3d.cpp
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object.h"
#include "mesh.h"

Mesh3D::Mesh3D() {
}

Mesh3D::Mesh3D(int num_vertices_, Vector3D *vertices_, int num_faces_, Face **faces_)
: num_vertices(num_vertices_), vertices(vertices_), num_faces(num_faces_), faces(faces_) {
	this->calc_normals();
	this->texcoords = NULL;
	this->instance = NULL;
	this->default_material = NULL;
}

Mesh3D::Mesh3D(int num_vertices_, Vector3D *vertices_, int num_texcoords_, Vector2D *texcoords_, int num_faces_, Face **faces_)
: num_vertices(num_vertices_), vertices(vertices_), num_texcoords(num_texcoords_), texcoords(texcoords_), num_faces(num_faces_), faces(faces_) {
	this->calc_normals();
	this->instance = NULL;
	this->default_material = NULL;
}

Mesh3D::Mesh3D(int num_vertices_, Vector3D *vertices_, int num_texcoords_, Vector2D *texcoords_, int num_faces_, Face **faces_, Material *material_)
: num_vertices(num_vertices_), vertices(vertices_), num_texcoords(num_texcoords_), texcoords(texcoords_), num_faces(num_faces_), faces(faces_), default_material(material_) {
	this->calc_normals();
	this->instance = NULL;
}

Mesh3D::~Mesh3D() {
}

void Mesh3D::calc_normals(void) {
	this->normals = (Vector3D*) calloc(this->num_vertices, sizeof(Vector3D));

	int i, j;
	int common_face_count[this->num_vertices];

	for(i = 0; i < this->num_faces; i++) {
		Face *face = this->faces[i];

		Vector3D edge1 = Vector3D(this->vertices[face->vertices[0]], this->vertices[face->vertices[1]]);
		Vector3D edge2 = Vector3D(this->vertices[face->vertices[1]], this->vertices[face->vertices[2]]);

		face->normal.dot(edge1, edge2);
		face->normal.normalize();

		for(j = 0; j < face->num_vertices; j++) {
			this->normals[face->vertices[j]].add(face->normal);
			common_face_count[face->vertices[j]]++;
		}
	}

	for(i = 0; i < this->num_vertices; i++) {
		this->normals[i].div((float)common_face_count[i]);
	}
}

void Mesh3D::renderInstance(int num_textures) {
	if(this->instance != NULL) {
		this->instance->render(num_textures);
	}
}

void Mesh3D::renderImmediate(int num_textures) {
	int i,j,k;

	for(i = 0; i < this->num_faces; i++) {
		Face *face = this->faces[i];

		switch(face->num_vertices) {
			case 3:
				glBegin(GL_TRIANGLES);
				break;
			case 4:
				glBegin(GL_QUADS);
				break;
			default:
				glBegin(GL_POLYGON);
				break;
		}

		for(j = 0; j < face->num_vertices; j++) {
			int id = face->vertices[j];

			if(this->texcoords != NULL && face->texcoords != NULL) {
				for(k = 0; k < num_textures; k++) {
					glMultiTexCoord2f(GL_TEXTURE0 + k, this->texcoords[face->texcoords[k]].x, this->texcoords[face->texcoords[k]].y);
				}
			}

			if(this->normals != NULL) {
				glNormal3f(this->normals[id].x, this->normals[id].y, this->normals[id].z);
			}

			glVertex3f(
				this->vertices[id].x,
				this->vertices[id].y,
				this->vertices[id].z
			);
		}
		glEnd();
	}
}

