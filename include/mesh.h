/**
 *  include/mesh.h
 *
 *  Copyright (C) 2013 Michael Sippel
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

#ifndef _MESH_H
#define _MESH_H

#include "vector.h"
#include "face.h"
#include "material.h"

class RenderInstance {
	public:
		RenderInstance();
		RenderInstance(Mesh3D *mesh_);
		~RenderInstance();

		Mesh3D *mesh;
		void create(void);

	private:
		unsigned int index_id;
		unsigned int vertex_id;
		unsigned int normal_id;
		unsigned int texcoord_id;

		unsigned int index_counter;
		unsigned int vertex_counter;
		unsigned int *indices;
		Vector3D *vertices;
		Vector3D *normals;
		Vector2D *texcoords;
};

class Mesh3D {
	friend class RenderInstance;

	public:
		Mesh3D();
		Mesh3D(int num_vertices_, Vector3D *vertices_);
		~Mesh3D();

		Material *default_material;
		RenderInstance *instance;

		void calc_normals(void);
		void renderInstance(void);
		void renderImmediate(void);

	private:
		int num_vertices;
		Vector3D *vertices;
		Vector3D *normals;

		int num_texcoords;
		Vector2D *texcoords;

		int num_faces;
		Face **faces;
};

class Mesh2D {
	public:
		Mesh2D();
		Mesh2D(int num_vertices_, Vector2D *vertices_);
		~Mesh2D();

		Material *default_material;

		void render(void);

	private:
		int num_vertices;
		Vector3D *vertices;

		int num_texcoords;
		Vector2D *texcoords;  

		int num_faces;
		Face **faces;
};

#endif

