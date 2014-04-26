/**
 *  include/vector.h
 *
 *  Copyright (C) 2014 Michael Sippel
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

#ifndef _VECTOR_H
#define _VECTOR_H

/**
 * Vector class.
 */
class Vector3D {
	public:
		Vector3D();
		Vector3D(Vector3D o, Vector3D p);
		Vector3D(float x_, float y_, float z_);
		~Vector3D();

		float x, y, z;

		void normalize(void);

		void add(Vector3D v);
		void sub(Vector3D v);
		float scalar(Vector3D v);
		void dot(Vector3D v);
		void dot(Vector3D v1, Vector3D v2);
};

class Vector2D {
	public:
		Vector2D();
		Vector2D(Vector2D o, Vector2D p);
		Vector2D(float x_, float y_);
		~Vector2D();

		float x, y;

		void normalize(void);

		void add(Vector2D v);
		void sub(Vector2D v);
		float scalar(Vector2D v);
		void dot(Vector2D v);
		void dot(Vector2D v1, Vector2D v2);
};

#endif

