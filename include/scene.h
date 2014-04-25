/**
 *  include/scene.h
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

#ifndef _SCENE_H
#define _SCENE_H

#include "object.h"
#include "particle.h"
#include "physics.h"
#include "light.h"
#include "font.h"
#include "group.h"

/**
 * Class for a set of objects
 */
Class Scene {
	public:
		Scene();
		~Scene();

		List<Object3D> *objects3D;
		List<Object2D> *objects2D;
		List<Text> *texts;
		List<ParticleEmitter> *particle_emitters;
		List<Light> *lights;

		ListEntry *addObject3D(Object3D *object);
		ListEntry *addObject2D(Object3D *object);
		ListEntry *addText(Text *text);
		ListEntry *addParticleEmitter(ParticleEmitter *emitter);
		ListEntry *addLight(Light *light);

		void render3D(void);
		void render2D(void);
};

#endif

