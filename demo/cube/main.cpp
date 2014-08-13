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

int main(int argc, char **argv)
{
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

    scene->base_node->objects3D->add(cube, "cube");
    scene->base_node->objects3D->add(wall, "wall");
    scene->base_node->objects3D->add(suzanne, "suzanne");

    Light *light = new Light(GL_LIGHT0, Color(1.0f, 1.0f, 1.0f, 1.0f));
    scene->base_node->lights->add(light);

    struct loader::load_return *ret = loader::load_oxy3d("data/scene.oxy3d");
    cube->mesh = ret->meshes->getEntry("cube")->element;
    wall->mesh = ret->meshes->getEntry("wall")->element;
    suzanne->mesh = ret->meshes->getEntry("suzanne")->element;

    cube->mesh->instance = new RenderInstance(cube->mesh);
    wall->mesh->instance = new RenderInstance(wall->mesh);
    suzanne->mesh->instance = new RenderInstance(suzanne->mesh);

    Camera *left = new Camera(window, scene);//, Viewport(0, 0, window->getWidth()/2, window->getHeight()));
    Camera *right = new Camera(window, scene, Viewport(window->getWidth()/2, 0, window->getWidth()/2+1, window->getHeight()));
    left->position = Vector3D(-27.9f, -20.1f, -10.4f);
    left->rotation = Vector3D(30.0f, -60.5f,  0.0f);
    left->fov = 45.0f;

    right->position = Vector3D(-8.0f, -2.0f, -4.0f);
    right->rotation = Vector3D(0.0f, -60.5f,  0.0f);
    right->fov = 45.0f;

    //right->viewport.background = Color(1.0f, 0.0f, 0.0f, 1.0f);
    scene->base_node->calcVolumeBox();
    Logger *fps_logger = new Logger("fps");
    float time = 0;

    // main loop
    while(1)
    {
        // handle events
        window->poll_events();

        // render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        left->render();
        scene->base_node->calcVolumeBox();
        //right->render();

        // update
        float frametime = window->update();
        time += frametime;
        if(time >= 1000)
        {
            fps_logger->log(INFO, "%f fps, %f ms per frame", 1/frametime*1000, frametime);
            time = 0;
        }

        int mx, my;
        SDL_GetMouseState(&mx, &my);
        float x = ((float)mx/window->getWidth()*2) * 180.0f;
        float y = ((float)my/window->getHeight()*2) * 180.0f;

        wall->setRotation(Vector3D(y,x, y));
    }

    return 0;
}

