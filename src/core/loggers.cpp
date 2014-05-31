/**
 *  src/object/loggers.cpp
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

#include "logger.h"

#include "window.h"
#include "mesh.h"
#include "object.h"
#include "material.h"
#include "shader.h"
#include "scene.h"

namespace oxygarum
{
Logger *engine_logger = new Logger("oxygarum");
Logger *SDLWindow::logger = new Logger(engine_logger, "window");

Logger *Scene::logger = new Logger(engine_logger, "scene");

Logger *Object3D::logger = new Logger(engine_logger, "object3d");
Logger *Mesh3D::logger = new Logger(Object3D::logger, "mesh3d");
Logger *RenderInstance::logger = new Logger(Mesh3D::logger, "renderinstance");

Logger *Material::logger = new Logger(engine_logger, "material");
Logger *Shader::logger = new Logger(Material::logger, "shader");
Logger *ShadeProgram::logger = new Logger(Material::logger, "shadeprogram");
};

