/**
 *  include/transformation.h
 *
 *  (C) Copyright 2014 Michael Sippel
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
#ifndef _TRANSFORMATION_H
#define _TRANSFORMATION_H

#include "vertex.h"
#include "vector.h"

/**
 * Class for transforming in 3D-space
 */
Class Transform {
	public:
		Vertex3D *position;
		Vector3D *rotation;

		void setPosition(Vertex3D *position_);
		void setRotation(Vector3D *rotation_);
		void move(Vector3D *position_);
		void rotate(Vector3D *rotation_);
		void transform(Vertex3D *position_, Vector3D *rotation_);
};

#endif

