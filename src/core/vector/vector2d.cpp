/**
 *  src/core/vector/vector2d.cpp
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

Vector2D::Vector2D()
{
    this->x = 0.0f;
    this->y = 0.0f;
}

Vector2D::Vector2D(float x_, float y_)
    : x(x_), y(y_)
{
}

Vector2D::Vector2D(Vector2D o, Vector2D p)
{
    this->x = p.x - o.x;
    this->y = p.y - o.y;
}

Vector2D::~Vector2D()
{
}

void Vector2D::normalize(void)
{
    float len = sqrt(
                    this->x * this->x +
                    this->y * this->y
                );

    this->x /= len;
    this->y /= len;
}

void Vector2D::add(Vector2D v)
{
    this->x += v.x;
    this->y += v.y;
}

void Vector2D::add(float x_)
{
    this->x += x_;
    this->y += x_;
}

void Vector2D::sub(Vector2D v)
{
    this->x -= v.x;
    this->y -= v.y;
}

void Vector2D::sub(float x_)
{
    this->x -= x_;
    this->y -= x_;
}

float Vector2D::scalar(Vector2D v)
{
    return (this->x * v.x +
            this->y * v.y);
}

void Vector2D::dot(Vector2D v1, Vector2D v2)
{
    this->x = (v1.y * v2.x) - (v1.x * v2.y);
    this->y = (v1.x * v2.y) - (v1.y * v2.x);
}

void Vector2D::dot(Vector2D v)
{
    this->dot(*this, v);
}

};

