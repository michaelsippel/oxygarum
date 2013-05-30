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

typedef struct vertex3d {
  float x;
  float y;
  float z;
} vertex3d_t;

typedef struct vertex2d {
  float x;
  float y;
  float z;
} vertex2d_t;

typedef unsigned int vertex_id;

#endif

