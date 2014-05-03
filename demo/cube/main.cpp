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
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	Camera *camera = new Camera(window, Vector3D(-5.0f, -2.0f, -5.0f), Vector3D(0.0f, -45.0f,  0.0f));

	Object3D *cube = new Object3D();
	Object3D *wall = new Object3D();
	Object3D *suzanne = new Object3D();
	camera->scene->objects3D->add(cube);
	camera->scene->objects3D->add(wall);
	camera->scene->objects3D->add(suzanne);

	Light *light = new Light(GL_LIGHT0, Color(1.0f, 1.0f, 1.0f, 1.0f));
	camera->scene->lights->add(light);

	struct loader::load_return *ret = loader::load_oxy3d("data/scene.oxy3d");
	cube->mesh = ret->meshes->getEntry("cube")->element;
	wall->mesh = ret->meshes->getEntry("wall")->element;
	suzanne->mesh = ret->meshes->getEntry("suzanne")->element;

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

		int mx, my;
		SDL_GetMouseState(&mx, &my);
		light->position.x = ((float)mx/window->getWidth()) * 20.0f;
		light->position.y = 5.0f - ((float)my/window->getHeight()) * 10.0f;
	}

	return 0;
}

