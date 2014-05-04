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
	Logger *logger = new Logger("oxygarum");
	logger->log(INFO, "Hello from Logger!");

	Logger *sub_logger = new Logger(logger, "test_sub_logger");
	sub_logger->log(ERROR, "panic!!");

	SDLWindow *window = new SDLWindow("Oxygarum demo", 1025, 576);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	Scene *scene = new Scene();

	Object3D *cube = new Object3D();
	Object3D *wall = new Object3D();
	Object3D *suzanne = new Object3D();
	cube->setFlag(OBJECT_RENDER_VBO);
	wall->setFlag(OBJECT_RENDER_VBO);
	suzanne->setFlag(OBJECT_RENDER_VBO);
	scene->objects3D->add(cube);
	scene->objects3D->add(wall);
	scene->objects3D->add(suzanne);

	Light *light = new Light(GL_LIGHT0, Color(1.0f, 1.0f, 1.0f, 1.0f));
	scene->lights->add(light);

	struct loader::load_return *ret = loader::load_oxy3d("data/scene.oxy3d");
	cube->mesh = ret->meshes->getEntry("cube")->element;
	wall->mesh = ret->meshes->getEntry("wall")->element;
	suzanne->mesh = ret->meshes->getEntry("suzanne")->element;

	cube->mesh->instance = new RenderInstance(cube->mesh);
	wall->mesh->instance = new RenderInstance(wall->mesh);
	suzanne->mesh->instance = new RenderInstance(suzanne->mesh);

	Camera *left = new Camera(window, scene, Viewport(0,0, window->getWidth()/2, window->getHeight()));
	Camera *right = new Camera(window, scene, Viewport(window->getWidth()/2,0, window->getWidth()/2, window->getHeight()));
	left->position = Vector3D(-5.0f, -2.0f, -5.0f);
	left->rotation = Vector3D(0.0f, -44.5f,  0.0f);
	left->fov = 45.0f;

	right->position = Vector3D(-5.0f, -2.0f, -5.0f);
	right->rotation = Vector3D(0.0f, -45.5f,  0.0f);
	right->fov = 45.0f;

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

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		left->render();
		right->render();

		float frametime = window->update();

		int mx, my;
		SDL_GetMouseState(&mx, &my);
		light->position.x = ((float)mx/window->getWidth()) * 20.0f;
		light->position.y = 5.0f - ((float)my/window->getHeight()) * 10.0f;
	}

	return 0;
}

