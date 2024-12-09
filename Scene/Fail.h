#ifndef FAIL_H_INCLUDED
#define FAIL_H_INCLUDED

#include <allegro5/allegro.h>
#include "../UI.h"
#include "scene.h"
#include "../Global.h"
#include "Scenemanager.h"

class Fail : public Scene{
    public:
        Fail();
        ~Fail();
        void init() override;
        bool update() override;
        void draw() override;
        void destroy() override;
    private:
        double menu_button_x, menu_button_y, button_width, button_height;
        ALLEGRO_COLOR button_color;
        ALLEGRO_COLOR button_hover_color;
        ALLEGRO_COLOR menu_button_current_color;
};

#endif