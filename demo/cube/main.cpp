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
	Camera *camera = new Camera(window, Vector3D(0.0f, 0.0f, 1.0f));

	Vector3D vertices[4] = {
		Vector3D(-1.0f, 1.0f, 0.0f),
		Vector3D( 1.0f, 1.0f, 0.0f),
		Vector3D( 1.0f,-1.0f, 0.0f),
		Vector3D(-1.0f,-1.0f, 0.0f)
	};

	Vector2D texcoords[4] = {
		Vector2D(-1.0f, 1.0f),
		Vector2D( 1.0f, 1.0f),
		Vector2D( 1.0f,-1.0f),
		Vector2D(-1.0f,-1.0f)
	};

	int indices[4] = {0, 1, 2, 3};
	Face *faces[1] = {
		new Face(4, (int*) &indices, (int*) &indices)
	};

	Mesh3D *mesh = new Mesh3D(4, (Vector3D*) &vertices, 4, (Vector2D*) &texcoords, 1, (Face**) &faces);
	mesh->instance = new RenderInstance(mesh);

	Object3D *obj = new Object3D();
	obj->mesh = mesh;
	obj->setFlag(OBJECT_RENDER_VBO);

	Texture *tex = new Texture("data/wall_diffuse.png");
	obj->material = new Material(Color(1.0f, 1.0f, 1.0f, 1.0f));
	obj->material->map_texture(tex, "Texture0", 0);

	camera->scene->objects3D->add(obj);

	glEnable(GL_TEXTURE_2D);

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
		obj->move(Vector3D(0.0f, 0.0f, -0.01*frametime));
	}

	return 0;
}

