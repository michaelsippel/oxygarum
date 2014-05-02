//
// A simple demo
//
// Copyright (C) 2012-2013 Michael Sippel
// <michamimosa@gmail.com>
//

#include <oxygarum.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace oxygarum;

int main(int argc, char **argv) {
	SDLWindow *window = new SDLWindow("Oxygarum demo", 1024, 576);
	Camera *camera = new Camera(window, Vector3D(0.0f, -2.0f, -10.0f));

	Object3D *cube = new Object3D();
	camera->scene->objects3D->add(cube);

	struct loader::load_return *ret = loader::load_oxy3d("data/scene.oxy3d");
	cube->mesh = ret->meshes->getEntry("cube")->element;

	// main loop
	while(1) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					exit(0);
					break;
			}
		}
		camera->render();

		float frametime = window->update();
	}

	return 0;
}

