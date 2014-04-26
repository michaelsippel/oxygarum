/**
 *  include/screen.h
 *
 *  Copyright (C) 2013-2014 Michael Sippel
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

#ifndef _SCREEN_H
#define _SCREEN_H

#include "scene.h"
#include "camera.h"
#include "material.h"

/**
 * @class Viewport
 * @brief Definines the properties of a Screen
 */
class Viewport {
	public:
		Viewport();
		Viewport(int x_, int y_, int width_, int height_);
		~Viewport();

		int x, y;
		int width, height;
};

/**
 * @class Screen
 * @brief Class for rendering a scene.
 *
 * It sets up the viewport, position and rotation of the camera
 * and the projection-matrices for 2D/3D rendering.
 */
class Screen {
	public:
		Screen();
		Screen(Scene *scene_);
		Screen(Scene *scene_, Camera *camera_);
		Screen(Scene *scene_, Camera *camera_, Viewport viewport_);
		~Screen();

		Scene *scene;
		Camera *camera;
		Color background;
		Viewport viewport;

		void render(void);
};

#endif

