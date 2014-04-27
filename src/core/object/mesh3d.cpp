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
	int i, j;
	int *common_face_count = (int*) calloc(this->num_vertices, sizeof(int));

	Face *face;
	for(i = 0; i < this->num_faces; i++) {
		face = this->faces[i];

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
		this->normals[i].div(common_face_count[i]);
	}

	free(common_face_count);
}

void Mesh3D::renderInstance(int num_textures) {
	if(this->instance != NULL) {
		this->instance->render(num_textures);
	}
}

void Mesh3D::renderImmediate(void) {/*TODO
  int i;
  
  if(face->vertex_counter == 3)
    glBegin(GL_TRIANGLES);
  else if(face->vertex_counter == 4)
    glBegin(GL_QUADS);
  else
    glBegin(GL_POLYGON);
  
  for(i = 0; i < face->vertex_counter; i++) {
    vertex_id id = face->vertices[i];
    
    if(mesh->texcoords != NULL && face->uv_map != NULL) {
      int j;
      for(j = 0; j < material->textures->size; j++) {
        glMultiTexCoord2f(GL_TEXTURE0 + j, mesh->texcoords[face->uv_map[i]].u, mesh->texcoords[face->uv_map[i]].v);
      }
    }

    if(mesh->normals != NULL)
      glNormal3f(mesh->normals[id].x, mesh->normals[id].y, mesh->normals[id].z);
    
    glVertex3f(
 	mesh->vertices[id].x,
 	mesh->vertices[id].y,
 	mesh->vertices[id].z
    );
  }
  glEnd();*/
}

