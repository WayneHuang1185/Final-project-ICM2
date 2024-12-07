#ifndef SCENEMANAGER_H_INCLUDED
#define SCENEMANAGER_H_INCLUDED

#include "Scene.h"
#include <memory>

enum class Scenetype{
    Menu, 
    Setting,
    Introduction,
    Game_earth, 
    Game_earth_2,
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