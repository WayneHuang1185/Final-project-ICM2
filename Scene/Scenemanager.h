#ifndef SCENEMANAGER_H_INCLUDED
#define SCENEMANAGER_H_INCLUDED

#include "Scene.h"
#include <memory>

enum class Scenetype{
    Menu, 
    Game_earth, 
    Ending, 
    Fail
};

class Scenemanager{
    public:
        Scenemanager();
        ~Scenemanager();

        void Create_Scene(Scenetype);
        bool update_Scene();
        void draw_Scene();
    private:
        Scene *currentScene;
};

#endif