/**
 *  include/light.h
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

#ifndef _LIGHT_H
#define _LIGHT_H

#include <GL/gl.h>
#include "vector.h"
#include "transformation.h"
#include "material.h"

namespace oxygarum
{

class Light : public Transformation3D
{
    public:
        Light();
        Light(GLenum gl_light_);
        Light(GLenum gl_light_, Color color);
        ~Light();

        GLfloat ambient[4];
        GLfloat diffuse[4];
        GLfloat specular[4];
        GLfloat r_pos[4];
        GLenum gl_light;

        void update(void);
};

};

#endif

