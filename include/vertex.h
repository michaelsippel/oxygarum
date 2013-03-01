/**
 *  include/vertex.h
 *
 *  (C) Copyright 2012 Michael Sippel
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
#ifndef _VERTEX_H
#define _VERTEX_H

#define MAX_VERTICES 20000

typedef struct vertex {
  double x;
  double y;
  double z;
} vertex_t;

typedef unsigned int vertex_id;

#ifndef _VERTICES
#define _VERTICES
extern vertex_t vertices[MAX_VERTICES];
#endif

/// adds the vertex to the vertices array and returns the id
vertex_id oxygarum_add_vertex(vertex_t vertex);

#endif
