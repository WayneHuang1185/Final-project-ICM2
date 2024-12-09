#include "Scenemanager.h"
#include "Menu.h"
#include "Gamescene_earth.h"
#include "Gamescene_earth_2.h"
#include "Setting.h"
#include "Introduction.h"
#include "Fail.h"

Scenemanager::Scenemanager() : currentScene(nullptr) {}

Scenemanager::~Scenemanager() {}

void Scenemanager::Create_Scene(Scenetype &type) {
    if(currentScene){
        delete currentScene;
        currentScene = nullptr;
    }

    switch (type) {
        case Scenetype::Menu: // 0
            currentScene = new Menu();
            std::cout << "Create_Scene menu" << std::endl;
            break;
        case Scenetype::Setting: // 1
            currentScene = new Setting();
            std::cout << "Create_Scene Setting" << std::endl;
            break;
        case Scenetype::Introduction: // 2
            currentScene = new Introduction();
            std::cout << "Create_Scene Introduction" << std::endl;
            break;
        case Scenetype::Game_earth:  // 3
            currentScene = new Gamescene_earth();
            std::cout << "Create_Scene gamescene_earth" << std::endl;
            break;
        case Scenetype::Game_earth_2: // 4
            currentScene = new Gamescene_earth2();
            std::cout << "Create_Scene gamescene_earth_2" << std::endl;
            break;
        case Scenetype::Fail: // 5
            currentScene = new Fail();
            std::cout << "Create_Scene Fail" << std::endl;
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
