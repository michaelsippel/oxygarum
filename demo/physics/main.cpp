//
// A physics demo
//
// Copyright (C) 2014 Michael Sippel
// <michamimosa@gmail.com>
//

#include <oxygarum.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace oxygarum;

int main(int argc, char **argv)
{
    Logger *logger = new Logger("demo");
    logger->log(INFO, "Hello World");

    SDLWindow *window = new SDLWindow("Oxygarum demo", 1025, 576);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    struct loader::load_return *ret = loader::load_oxy3d("data/scene.xml");

    Scene *scene = new Scene();
    scene->base_node->objects3D->join(ret->objects);

    //Light *light = new Light(GL_LIGHT0, Color(1.0f, 1.0f, 1.0f, 1.0f));
    //light->move(Vector3D(4.0f, 4.0f, 0.0f));
    //scene->base_node->lights->add(light);

    Camera *cam = new Camera(window, scene, Viewport(0, 0, window->getWidth(), window->getHeight()));
    cam->position = Vector3D(0.0f, -2.0f, 0.0f);
    cam->rotation = Vector3D(0.0f, 0.0f, 0.0f);
    cam->fov = 90.0f;

    scene->base_node->calcVolumeBox();

    PhysicsContext *pc = new PhysicsContext();

    ForceField *gravity = new ForceField();
    gravity->velocity = Vector3D(0.0f, -9.80665f, 0.0f);

    pc->fields->add(gravity);

    PhysicsObject *cube = new PhysicsObject();
    cube->object = ret->objects->getElement("cube1");

    pc->objects->add(cube);

    // main loop
    while(1)
    {
        // handle events
        window->poll_events();

        // render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        cam->render();

        // update
        float frametime = window->update();
        pc->update(frametime*0.001);
    }

    return 0;
}

