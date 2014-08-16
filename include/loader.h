/**
 *  include/loader.h
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

#ifndef _LOADER_H
#define _LOADER_H

#include "texture.h"
#include "shader.h"
#include "material.h"
#include "mesh.h"
#include "object.h"

namespace oxygarum
{
namespace loader
{

List<Mesh3D> *load_obj(const char *path);
List<Mesh3D> *load_obj(const char *path, List<Material> *materials);

struct load_return
{
    List<Texture> *textures;
    List<ShadeProgram> *shaders;
    List<Material> *materials;
    List<Mesh3D> *meshes;
    List<Object3D> *objects;
};

struct load_return *load_oxy3d(const char *path);
struct load_return *load_oxy3d(const char *f_path, struct load_return *ret);

};
};

#endif

