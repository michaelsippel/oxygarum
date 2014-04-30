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

	List<int> *l = new List<int>();
	ListEntry<int> *e = l->getHead();//new ListEntry<int>();

	return 0;
}

