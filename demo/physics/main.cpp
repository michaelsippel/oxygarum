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
    ball2->push(Vector3D(2.0f, 0.0f, 0.0f));
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

    Light *light = new Light(GL_LIGHT0, Color(1.0f, 1.0f, 1.0f, 1.0f));
    light->move(Vector3D(4.0f, 4.0f, 0.0f));
    scene->base_node->lights->add(light);

    Camera *cam = new Camera(window, scene, Viewport(0, 0, window->getWidth(), window->getHeight()));
    cam->position = new Vector3D(0.0f, -2.0f, 0.0f);
    cam->rotation = new Vector3D(0.0f, 0.0f, 0.0f);
    cam->fov = 90.0f;

    PhysicsContext *pc = new PhysicsContext();

    ForceField *gravity = new ForceField();
    gravity->velocity = Vector3D(0.0f, -9.80665f, 0.0f);

    //pc->fields->add(gravity);

    cube1 = new PhysicsObject();
    cube1->parent(ret->objects->getElement("cube1"));

    cube2 = new PhysicsObject();
    cube2->parent(ret->objects->getElement("cube2"));

    ball1 = new PhysicsObject();
    ball1->collision = new BoundingSphere(1.0f, ball1);
    ball1->parent(ret->objects->getElement("ball1"));
    ball1->collision->parent(ret->objects->getElement("ball1"));

    ball2 = new PhysicsObject();
    ball2->collision = new BoundingSphere(1.0f, ball2);
    ball2->parent(ret->objects->getElement("ball2"));
    ball2->collision->parent(ret->objects->getElement("ball2"));

//    pc->objects->add(cube1);
//    pc->objects->add(cube2);
    pc->objects->add(ball1);
    pc->objects->add(ball2);

    pc->collisions->add(ball1->collision);
    ball1->pull(Vector3D(0.0f, 2.0f, 0.0f));
    pc->collisions->add(ball2->collision);
    ball2->pull(Vector3D(0.0f, 1.0f, 0.0f));

    BoundingBox *bb = new BoundingBox();
    bb->box_size1 = Vector3D(-1.0f, -1.0f, -1.0f);
    bb->box_size2 = Vector3D( 1.0f, 1.0f, 1.0f);
    bb->move(Vector3D(0.0f, 0.0f, -5.0f));
    bb->update_poly();

    pc->collisions->add(bb);

    // main loop
    while(1)
    {
        // handle events
        window->poll_events();

        //scene->base_node->calcVolumeBox();

        // render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        cam->render();

        bb->useTransformation();
        bb->drawVolumeBox();

        // update
        float frametime = window->update();
        pc->update(frametime*0.001);
    }

    return 0;
}

