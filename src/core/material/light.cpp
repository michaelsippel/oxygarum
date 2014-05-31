/**
 *  src/core/material/light.cpp
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

/**
 * @author Michael Sippel <michamimosa@gmail.com>
 */
#include <GL/glew.h>
#include <GL/gl.h>
#include <light.h>

namespace oxygarum
{

Light::Light()
{
    this->gl_light = GL_LIGHT0;
}

Light::Light(GLenum gl_light_)
    : gl_light(gl_light_)
{
}

Light::Light(GLenum gl_light_, Color color)
    : gl_light(gl_light_)
{
    this->ambient[0] = 0.0f;
    this->ambient[1] = 0.0f;
    this->ambient[2] = 0.0f;
    this->ambient[3] = 1.0f;
    this->diffuse[0] = color.r*0.8;
    this->diffuse[1] = color.g*0.8;
    this->diffuse[2] = color.b*0.8;
    this->diffuse[3] = color.a*0.8;
    this->specular[0] = color.r;
    this->specular[1] = color.g;
    this->specular[2] = color.b;
    this->specular[3] = color.a;
    this->r_pos[0] = 0.0f;
    this->r_pos[1] = 0.0f;
    this->r_pos[2] = 0.0f;
    this->r_pos[3] = 1.0f;
}

Light::~Light()
{
}

void Light::update(void)
{
    glEnable(this->gl_light);
    glLightfv(this->gl_light, GL_AMBIENT, (GLfloat*) &this->ambient);
    glLightfv(this->gl_light, GL_DIFFUSE, (GLfloat*) &this->diffuse);
    glLightfv(this->gl_light, GL_SPECULAR, (GLfloat*) &this->specular);
    glLightfv(this->gl_light, GL_POSITION, (GLfloat*) &this->r_pos);
}

};

