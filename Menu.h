#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <allegro5/allegro.h>

class Menu{
    public:
        void execute();

    public:
        Menu();
        ~Menu();
    void menu_init();
	bool menu_update();
	void menu_draw();

    private:
        ALLEGRO_BITMAP *background;
        ALLEGRO_DISPLAY *display;
};

#endif