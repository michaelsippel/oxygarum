/**
 *  src/core/vector/volumebox.cpp
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
#include <GL/glew.h>
#include <GL/gl.h>
#include "vector.h"
#include "volumebox.h"

namespace oxygarum
{

VolumeBox::VolumeBox()
{
    this->calcVolumeBox();
}

VolumeBox::~VolumeBox()
{
}

void VolumeBox::calcVolumeBox(void)
{
    this->box_size1 = Vector3D();
    this->box_size2 = Vector3D();
}

void VolumeBox::drawVolumeBox(void)
{
    glDisable(GL_LIGHTING);
    glUseProgram(0);
    glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    // back
    glVertex3f(this->box_size1.x, this->box_size1.y, this->box_size1.z);
    glVertex3f(this->box_size1.x, this->box_size2.y, this->box_size1.z);

    glVertex3f(this->box_size1.x, this->box_size2.y, this->box_size1.z);
    glVertex3f(this->box_size2.x, this->box_size2.y, this->box_size1.z);

    glVertex3f(this->box_size2.x, this->box_size2.y, this->box_size1.z);
    glVertex3f(this->box_size2.x, this->box_size1.y, this->box_size1.z);

    glVertex3f(this->box_size2.x, this->box_size1.y, this->box_size1.z);
    glVertex3f(this->box_size1.x, this->box_size1.y, this->box_size1.z);

    // middle
    glVertex3f(this->box_size1.x, this->box_size1.y, this->box_size1.z);
    glVertex3f(this->box_size1.x, this->box_size1.y, this->box_size2.z);

    glVertex3f(this->box_size1.x, this->box_size2.y, this->box_size1.z);
    glVertex3f(this->box_size1.x, this->box_size2.y, this->box_size2.z);

    glVertex3f(this->box_size2.x, this->box_size2.y, this->box_size1.z);
    glVertex3f(this->box_size2.x, this->box_size2.y, this->box_size2.z);

    glVertex3f(this->box_size2.x, this->box_size1.y, this->box_size1.z);
    glVertex3f(this->box_size2.x, this->box_size1.y, this->box_size2.z);

    // front
    glVertex3f(this->box_size1.x, this->box_size1.y, this->box_size2.z);
    glVertex3f(this->box_size1.x, this->box_size2.y, this->box_size2.z);

    glVertex3f(this->box_size1.x, this->box_size2.y, this->box_size2.z);
    glVertex3f(this->box_size2.x, this->box_size2.y, this->box_size2.z);

    glVertex3f(this->box_size2.x, this->box_size2.y, this->box_size2.z);
    glVertex3f(this->box_size2.x, this->box_size1.y, this->box_size2.z);

    glVertex3f(this->box_size2.x, this->box_size1.y, this->box_size2.z);
    glVertex3f(this->box_size1.x, this->box_size1.y, this->box_size2.z);

    glEnd();
}

};

