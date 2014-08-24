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

PhysicsObject *cube1;
PhysicsObject *cube2;
PhysicsObject *ball1;
PhysicsObject *ball2;

void key(int argc, void **argv)
{
    printf("PUS!\n");
    ball2->push(Vector3D(1.0f, 0.0f, 0.0f));
}

int main(int argc, char **argv)
{
    Logger *logger = new Logger("demo");
    logger->log(INFO, "Hello World");

    SDLWindow *window = new SDLWindow("Oxygarum demo", 1025, 576);
    window->eventmgr->register_handler(SDL_KEYDOWN, &key);

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

    //pc->fields->add(gravity);

    cube1 = new PhysicsObject();
    cube1->trans = ret->objects->getElement("cube1");

    cube2 = new PhysicsObject();
    cube2->trans = ret->objects->getElement("cube2");

    ball1 = new PhysicsObject();
    ball1->trans = ret->objects->getElement("ball1");
    ball1->collision = new CollisionPoint();
    ball1->collision->trans = ball1->trans;

    ball2 = new PhysicsObject();
    ball2->trans = ret->objects->getElement("ball2");
    ball2->collision = new CollisionPoint();
    ball2->collision->trans = ball2->trans;


    pc->objects->add(cube1);
    pc->objects->add(cube2);
    pc->objects->add(ball1);
    pc->objects->add(ball2);

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

