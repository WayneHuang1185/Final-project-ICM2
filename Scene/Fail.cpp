#include "Fail.h"
#include "../Utils.h"
#include "../data/DataCenter.h"
#include "../data/OperationCenter.h"
#include "../data/SoundCenter.h"
#include "../data/ImageCenter.h"
#include "../data/FontCenter.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <iostream>

Fail::Fail(){
    init();
}

Fail::~Fail(){
    destroy();
}

void Fail::init(){
    DataCenter *DC = DataCenter::get_instance();
    SoundCenter *SC = SoundCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();

    button_width = 200;
    button_height = 100;

    menu_button_x = (DC->window_width - button_width) / 2;
    menu_button_y = (DC->window_height - button_height) / 2;

    button_color = al_map_rgb(100, 200, 100);         
    button_hover_color = al_map_rgb(150, 250, 150);  

    menu_button_current_color = button_color;

    SC->init();
	FC->init();
}

bool Fail::update(){
    DataCenter* DC = DataCenter::get_instance();

    if (DC->mouse.x >= menu_button_x && DC->mouse.x <= menu_button_x + button_width &&
        DC->mouse.y >= menu_button_y && DC->mouse.y <= menu_button_y + button_height) {
            menu_button_current_color = button_hover_color; 
            if (DC->mouse_state[1]) { 
                std::cout << "Button clicked! Switching to Gamescene_earth." << std::endl;
                window = 0;  
                return false;  
            }
        }
    else menu_button_current_color = button_color;

    return true;
}

void Fail::draw(){
    DataCenter *DC = DataCenter::get_instance();
    FontCenter* FC = FontCenter::get_instance();

    al_clear_to_color(al_map_rgb(100, 100, 100));

    al_draw_filled_rectangle(menu_button_x, menu_button_y, menu_button_x + button_width, menu_button_y + button_height, menu_button_current_color);

    al_draw_rectangle(menu_button_x, menu_button_y, menu_button_x + button_width, menu_button_y + button_height, al_map_rgb(0, 0, 0), 2);

    al_draw_text(FC->caviar_dreams[24], al_map_rgb(0, 0, 0),
                menu_button_x + button_width / 2,
				menu_button_y + (button_height - al_get_font_line_height(FC->caviar_dreams[FontSize::MEDIUM])) / 2,
				ALLEGRO_ALIGN_CENTRE, "MENU");
}

void Fail::destroy(){

}