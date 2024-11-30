#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <allegro5/allegro.h>
#include "../UI.h"
#include "scene.h"
#include "../Global.h"
#include "Scenemanager.h"

class Menu : public Scene{
    public:
        Menu();
        ~Menu();
        void init() override;
	    bool update() override;
	    void draw() override;
        void destroy() override;
    private:
        double button_x, button_y, button_width, button_height;
        ALLEGRO_COLOR button_color;
        ALLEGRO_COLOR button_hover_color;
        ALLEGRO_COLOR button_current_color;
};

#endif