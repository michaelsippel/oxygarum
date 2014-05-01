//
// this simple demo will draw a rotating
// textured cube using the oxygarum 3D-Engine.
//
// Copyright (C) 2012-2013 Michael Sippel
// <michamimosa@gmail.com>
//

#include <oxygarum.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
	SDLWindow *window = new SDLWindow("Oxygarum demo", 800, 600);
	Camera *camera = new Camera(window, Vector3D(0.0f, 0.0f, -5.0f));

	Vector3D vertices[4] = {
		Vector3D(-1.0f, 1.0f, 0.0f),
		Vector3D( 1.0f, 1.0f, 0.0f),
		Vector3D( 1.0f,-1.0f, 0.0f),
		Vector3D(-1.0f,-1.0f, 0.0f)
	};

	int indices[4] = {0, 1, 2, 3};
	Face *faces[1] = {
		new Face(4, (int*) &indices)
	};

	Mesh3D *mesh = new Mesh3D(4, (Vector3D*) &vertices, 1, (Face**) &faces);
	Object3D *obj = new Object3D();
	obj->mesh = mesh;

	camera->scene->objects3D->add(obj);

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

		// update (calculate frametime, handle events, etc.)
		float frametime = window->update();
	}

	return 0;
}

