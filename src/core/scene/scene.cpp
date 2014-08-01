/**
 *  src/core/scene.cpp
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

/**
 * @author Michael Sippel <michamimosa@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>

#include "scene.h"
#include "object.h"
#include "particle.h"
#include "font.h"
#include "light.h"

namespace oxygarum
{

Scene::Scene()
{
    this->base_node = new SceneNode();
}

Scene::~Scene()
{
}

void Scene::render3D(void)
{
    this->base_node->useTransformation();
    this->base_node->render3D();
}

void Scene::render2D(void)
{
    this->base_node->render2D();
}

};

