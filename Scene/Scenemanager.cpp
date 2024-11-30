#include "Scenemanager.h"
#include "Menu.h"
#include "Gamescene_earth.h"

Scenemanager::Scenemanager() : currentScene(nullptr) {}

Scenemanager::~Scenemanager() {}

void Scenemanager::Create_Scene(Scenetype type) {
    if(currentScene){
        delete currentScene;
        currentScene = nullptr;
    }

    switch (type) {
        case Scenetype::Menu:
            currentScene = new Menu();
            std::cout << "Create_Scene menu" << std::endl;
            break;
        case Scenetype::Game_earth:
            currentScene = new Gamescene_earth();
            std::cout << "Create_Scene gamescene_earth" << std::endl;
            break;
        case Scenetype::Fail:
            break;
        case Scenetype::Ending:
            break;
        default:
            break;
    }
}

bool Scenemanager::update_Scene() {
    if (currentScene) currentScene->update();
    return true;
}

void Scenemanager::draw_Scene() {
    if (currentScene) currentScene->draw();
}
