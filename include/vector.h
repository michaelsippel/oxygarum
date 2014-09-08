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

namespace oxygarum
{

/**
 * Vector class.
 */
class Vector3D
{
    public:
        Vector3D();
        Vector3D(Vector3D o, Vector3D p);
        Vector3D(float x_, float y_, float z_);
        ~Vector3D();

        float x, y, z;

        void normalize(void);
        float length(void);

        void add(Vector3D v);
        void add(float x_);
        void sub(Vector3D v);
        void sub(float x_);
        void mul(Vector3D v);
        void mul(float x_);
        void div(Vector3D v);
        void div(float x_);

        void rotate(Vector3D v);
        void scale(float x_);
        void reflect(Vector3D normal);

        float dot(Vector3D v);
        void cross(Vector3D v);
        void cross(Vector3D v1, Vector3D v2);

        void min(Vector3D v);
        void max(Vector3D v);
};

class Vector2D
{
    public:
        Vector2D();
        Vector2D(Vector2D o, Vector2D p);
        Vector2D(float x_, float y_);
        ~Vector2D();

        float x, y;

        void normalize(void);

        void add(Vector2D v);
        void add(float x_);
        void sub(Vector2D v);
        void sub(float x_);
        void mul(Vector2D v);
        void mul(float x_);
        void div(Vector2D v);
        void div(float x_);

        float dot(Vector2D v);
        void cross(Vector2D v);
        void cross(Vector2D v1, Vector2D v2);
};

};

#endif

