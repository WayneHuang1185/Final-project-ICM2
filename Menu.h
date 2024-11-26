#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "data/DataCenter.h"
#include "UI.h"

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
        double button_x;
        double button_y;
        double button_width = 200;
        double button_height = 100;
        bool hover;

        ALLEGRO_EVENT event;
	    ALLEGRO_BITMAP *background;

        ALLEGRO_DISPLAY *display;
	    ALLEGRO_TIMER *timer;
	    ALLEGRO_EVENT_QUEUE *event_queue;
        ALLEGRO_FONT *font;
	    UI *ui;
};

#endif