#include "Menu.h"
#include "../Utils.h"
#include "../data/DataCenter.h"
#include "../data/OperationCenter.h"
#include "../data/SoundCenter.h"
#include "../data/ImageCenter.h"
#include "../data/FontCenter.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <iostream>

Menu::Menu() {
    init();
}

Menu::~Menu() {
    destroy();
}

void Menu::init() {
    // std::cout << "Menu initialized" << std::endl;
    DataCenter *DC = DataCenter::get_instance();
    SoundCenter *SC = SoundCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();
    
    button_width = 200;
    button_height = 50;


    button_x = (DC->window_width - button_width) / 2;
    button_y = (DC->window_height - button_height) / 2;

    button_color = al_map_rgb(100, 200, 100);         
    button_hover_color = al_map_rgb(150, 250, 150);  
    button_current_color = button_color;             

    SC->init();
	FC->init();

    // std::cout << "Menu constructed" << std::endl;
}

bool Menu::update() {
    DataCenter* DC = DataCenter::get_instance();

    // std::cout << "in menu update" << std::endl;

    if (DC->mouse.x >= button_x && DC->mouse.x <= button_x + button_width &&
        DC->mouse.y >= button_y && DC->mouse.y <= button_y + button_height) {
        button_current_color = button_hover_color; 

        if (DC->mouse_state[1]) { 
            std::cout << "Button clicked! Switching to Gamescene_earth." << std::endl;
            window = 1;  
            return false;  
        }
    } else {
        button_current_color = button_color; 
    }

    return true;
}

void Menu::draw() {
    DataCenter *DC = DataCenter::get_instance();
    // std::cout << "in menu draw" << std::endl;

    al_clear_to_color(al_map_rgb(100, 100, 100));

    al_draw_filled_rectangle(button_x, button_y, button_x + button_width, button_y + button_height, button_current_color);
    al_draw_rectangle(button_x, button_y, button_x + button_width, button_y + button_height, al_map_rgb(0, 0, 0), 2);

    FontCenter* FC = FontCenter::get_instance();
    al_draw_text(FC->caviar_dreams[24], al_map_rgb(0, 0, 0),
                 button_x + button_width / 2, button_y + button_height / 2 - 12,
                 ALLEGRO_ALIGN_CENTER, "Start Game");
}

void Menu::destroy() {
    // std::cout << "Menu destroyed" << std::endl;
}
