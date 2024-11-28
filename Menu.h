#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <allegro5/allegro.h>
#include "UI.h"

class Menu{
    public:
        void execute();
    public:
        Menu();
        ~Menu();
        void menu_init();
	    void menu_update();
	    void menu_draw();
};

#endif