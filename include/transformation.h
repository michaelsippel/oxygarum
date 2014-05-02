/**
 *  include/transformation.h
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

#ifndef _TRANSFORMATION_H
#define _TRANSFORMATION_H

#include "vector.h"

namespace oxygarum {

/**
 * @class Transformation3D
 * @brief Class for transforming in 3D-space
 */
class Transformation3D {
	public:
		Transformation3D();
		Transformation3D(Vector3D position_, Vector3D rotation_);
		Transformation3D(Vector3D position_, Vector3D rotation_, Vector3D scaling_);
		~Transformation3D();

		Vector3D position;
		Vector3D rotation;
		Vector3D scaling;

		void setPosition(Vector3D position_);
		void setRotation(Vector3D rotation_);
		void setScaling(Vector3D scale_);
		void setScaling(float x_);

		void move(Vector3D position_);
		void rotate(Vector3D rotation_);
		void scale(Vector3D scaling_);
		void scale(float x_);

		void useTransformation(void);
};

/**
 * @class Transformation2D
 * @brief Class for transforming in 2D-space
 */
class Transformation2D {
	public:
		Transformation2D();
		Transformation2D(Vector2D position_, float rotation_);
		Transformation2D(Vector2D position_, float rotation_, Vector2D scaling_);
		~Transformation2D();

		Vector2D position;
		float rotation;
		Vector2D scaling;

		void setPosition(Vector2D position_);
		void setRotation(float rotation_);
		void setScaling(Vector2D scaling_);
		void setScaling(float x_);

		void move(Vector2D position_);
		void rotate(float rotation_);
		void scale(Vector2D scaling_);
		void scale(float x_);

		void useTransformation(void);
};

};

#endif

