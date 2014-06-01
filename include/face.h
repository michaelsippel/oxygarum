/**
 *  include/face.h
 *
 *  Copyright (C) 2012-2013 Michael Sippel
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

#ifndef _FACE_H
#define _FACE_H

#include "vector.h"

namespace oxygarum
{

class Mesh3D;
class Mesh2D;
class RenderInstance;

class Face
{
        friend class Mesh3D;
        friend class Mesh2D;
        friend class RenderInstance;

    public:
        Face();
        Face(int num_vertices_, int *vertices_);
        Face(int num_vertices_, int *vertices_, int *texcoords_);
        ~Face();

        Vector3D getNormal();

    private:
        int num_vertices;
        int *vertices;
        int *texcoords;
        Vector3D normal;
};

};

#endif

