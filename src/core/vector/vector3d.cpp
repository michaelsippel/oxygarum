/**
 *  src/core/vector/vector3d.cpp
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
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "vector.h"

namespace oxygarum
{

Vector3D::Vector3D()
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
}

Vector3D::Vector3D(float x_, float y_, float z_)
    : x(x_), y(y_), z(z_)
{
}

Vector3D::Vector3D(Vector3D o, Vector3D p)
{
    this->x = p.x - o.x;
    this->y = p.y - o.y;
    this->z = p.z - o.z;
}

Vector3D::~Vector3D()
{
}

void Vector3D::normalize(void)
{
    float len = this->length();

	if(len != 0.0f)
	{
    	this->x /= len;
    	this->y /= len;
    	this->z /= len;
	}
}

float Vector3D::length(void)
{
    return sqrt(
                    this->x * this->x +
                    this->y * this->y +
                    this->z * this->z
                );
}

void Vector3D::add(Vector3D v)
{
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
}

void Vector3D::add(float x_)
{
    this->x += x_;
    this->y += x_;
    this->z += x_;
}

void Vector3D::sub(Vector3D v)
{
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;
}

void Vector3D::sub(float x_)
{
    this->x -= x_;
    this->y -= x_;
    this->z -= x_;
}

void Vector3D::mul(Vector3D v)
{
    this->x *= v.x;
    this->y *= v.y;
    this->z *= v.z;
}

void Vector3D::mul(float x_)
{
    this->x *= x_;
    this->y *= x_;
    this->z *= x_;
}

void Vector3D::div(Vector3D v)
{
    if(v.x != 0.0f) this->x /= v.x;
    if(v.y != 0.0f) this->y /= v.y;
    if(v.z != 0.0f) this->z /= v.z;
}

void Vector3D::div(float x_)
{
    if(x_ != 0.0f)
    {
        this->x /= x_;
        this->y /= x_;
        this->z /= x_;
    }
}

void Vector3D::reflect(Vector3D normal)
{
	Vector3D a = *this;
	double product = a.dot(normal);
	this->x = a.x - 2 * normal.x * product;
	this->y = a.y - 2 * normal.y * product;
	this->z = a.z - 2 * normal.z * product;
}

void Vector3D::rotate(Vector3D v)
{
    // convert to rad
    v.mul(0.0174532925f);

    float sn, cs;

    // rotation on z-axis
    Vector3D rotZ = Vector3D();
    sn = sin(v.z);
    cs = cos(v.z);
    rotZ.x = this->x * cs - this->y * sn;
    rotZ.y = this->x * sn + this->y * cs;
    rotZ.z = this->z;
    *this = rotZ;

    // rotation on y-axis
    Vector3D rotY = Vector3D();
    sn = sin(v.y);
    cs = cos(v.y);
    rotY.x = this->x * cs + this->z * sn;
    rotY.y = this->y;
    rotY.z = -this->x * sn + this->z * cs;
    *this = rotY;

    // rotation on x-axis
    Vector3D rotX = Vector3D();
    sn = sin(v.x);
    cs = cos(v.x);
    rotX.x = this->x;
    rotX.y = this->y * cs - this->z * sn;
    rotX.z = this->y * sn + this->z * cs;
    *this = rotX;
}

float Vector3D::dot(Vector3D v)
{
    return (
               this->x * v.x +
               this->y * v.y +
               this->z * v.z);
}

void Vector3D::cross(Vector3D v1, Vector3D v2)
{
    this->x = (v1.y * v2.z) - (v1.z * v2.y);
    this->y = (v1.z * v2.x) - (v1.x * v2.z);
    this->z = (v1.x * v2.y) - (v1.y * v2.x);
}

void Vector3D::cross(Vector3D v)
{
    this->cross(*this, v);
}

void Vector3D::min(Vector3D v)
{
    if(v.x < this->x) this->x = v.x;
    if(v.y < this->y) this->y = v.y;
    if(v.z < this->z) this->z = v.z;
}

void Vector3D::max(Vector3D v)
{
    if(v.x > this->x) this->x = v.x;
    if(v.y > this->y) this->y = v.y;
    if(v.z > this->z) this->z = v.z;
}

};

