/**
 *  include/camera.h
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

#ifndef _CAMERA_H
#define _CAMERA_H

#include "transformation.h"
#include "window.h"
#include "scene.h"
#include "camera.h"
#include "material.h"

namespace oxygarum {

/**
 * @class Viewport
 * @brief Definines the properties of a Screen
 */
class Viewport {
	public:
		Viewport();
		Viewport(int x_, int y_, int width_, int height_);
		Viewport(int x_, int y_, int width_, int height_, Color background_);
		~Viewport();

		int x, y;
		int width, height;
		Color background;

		void use(void);
};

/**
 * @class Camera
 * @brief Camera Class.
 *
 * Defines the Location and Rotation of View
 */
class Camera : public Transformation3D {
	public:
		Camera();
		Camera(SDLWindow *window_);
		Camera(SDLWindow *window_, Scene *scene_);
		Camera(SDLWindow *window_, Scene *scene_, Viewport viewport_);
		Camera(SDLWindow *window_, Transformation3D transform);
		Camera(SDLWindow *window_, Transformation3D transform, Viewport viewport_);
		Camera(SDLWindow *window_, Vector3D position_);
		Camera(SDLWindow *window_, Vector3D position_, Vector3D rotation_);
		Camera(SDLWindow *window_, Vector3D position_, Vector3D rotation_, float fov_);
		~Camera();

		Scene *scene;
		Camera *camera;
		Viewport viewport;
		SDLWindow *window;
		float fov;

		void use(void);
		void render(void);
};

};

#endif

