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
    
    play_button_width = setting_button_width = introduction_button_width = exit_button_width = 200;
    play_button_height = setting_button_height = introduction_button_height = exit_button_height = 100;


    play_button_x = (DC->window_width - play_button_width) / 5 * 2;
    play_button_y = (DC->window_height - play_button_height) / 6 * 4;

    setting_button_x = (DC->window_width - setting_button_width) / 5 * 3;
    setting_button_y = (DC->window_height - play_button_height) / 6 * 4;

    introduction_button_x = (DC->window_width - play_button_width) / 5 * 2;
    introduction_button_y = (DC->window_height - play_button_height) / 6 * 5;

    exit_button_x = (DC->window_width - setting_button_width) / 5 * 3;
    exit_button_y = (DC->window_height - play_button_height) / 6 * 5;

    button_color = al_map_rgb(100, 200, 100);         
    button_hover_color = al_map_rgb(150, 250, 150);  
    play_button_current_color = setting_button_current_color = introduction_button_current_color = exit_button_current_color = button_color;             

    SC->init();
	FC->init();

    // std::cout << "Menu constructed" << std::endl;
}

bool Menu::update() {
    DataCenter* DC = DataCenter::get_instance();

    // std::cout << "in menu update" << std::endl;

    if (DC->mouse.x >= play_button_x && DC->mouse.x <= play_button_x + play_button_width &&
        DC->mouse.y >= play_button_y && DC->mouse.y <= play_button_y + play_button_height) {
            play_button_current_color = button_hover_color; 
            if (DC->mouse_state[1]) { 
                std::cout << "Button clicked! Switching to Gamescene_earth." << std::endl;
                window = 1;  
                return false;  
            }
        }
    else play_button_current_color = button_color;

    if(DC->mouse.x >= setting_button_x && DC->mouse.x <= setting_button_x + setting_button_width &&
            DC->mouse.y >= setting_button_y && DC->mouse.y <= setting_button_y + setting_button_height){
                setting_button_current_color = button_hover_color;
                if(DC->mouse_state[1]){
                    std::cout << "button clicked! switching to setting." << std::endl;
                    window = 2;
                    return false;
                }
            }
    else setting_button_current_color = button_color;

    if(DC->mouse.x >= introduction_button_x && DC->mouse.x <= introduction_button_x + introduction_button_width &&
            DC->mouse.y >= introduction_button_y && DC->mouse.y <= introduction_button_y + introduction_button_height){
                introduction_button_current_color = button_hover_color;
                if(DC->mouse_state[1]){
                    std::cout << "button clicked! switching to introduction." << std::endl;
                    window = 3;
                    return false;
                }
            }
    else introduction_button_current_color = button_color;

    if(DC->mouse.x >= exit_button_x && DC->mouse.x <= exit_button_x + exit_button_width &&
            DC->mouse.y >= exit_button_y && DC->mouse.y <= exit_button_y + exit_button_height){
                exit_button_current_color = button_hover_color;
                if(DC->mouse_state[1]){
                    std::cout << "button clicked! game terminate." << std::endl;
                    window = -1;
                    return false;
                }
            }
        
    else exit_button_current_color = button_color; 

    return true;
}

void Menu::draw() {
    DataCenter *DC = DataCenter::get_instance();
    FontCenter* FC = FontCenter::get_instance();
    // std::cout << "in menu draw" << std::endl;

    al_clear_to_color(al_map_rgb(100, 100, 100));

    al_draw_filled_rectangle(play_button_x, play_button_y, play_button_x + play_button_width, play_button_y + play_button_height, play_button_current_color);
    al_draw_filled_rectangle(setting_button_x, setting_button_y, setting_button_x+setting_button_width, setting_button_y+setting_button_height, setting_button_current_color);
    al_draw_filled_rectangle(introduction_button_x, introduction_button_y, introduction_button_x+introduction_button_width, introduction_button_y+introduction_button_height, introduction_button_current_color);
    al_draw_filled_rectangle(exit_button_x, exit_button_y, exit_button_x+exit_button_width, exit_button_y+exit_button_height, exit_button_current_color);

    al_draw_rectangle(play_button_x, play_button_y, play_button_x + play_button_width, play_button_y + play_button_height, al_map_rgb(0, 0, 0), 2);
    al_draw_rectangle(setting_button_x, setting_button_y, setting_button_x+setting_button_width, setting_button_y+setting_button_height, al_map_rgb(0, 0, 0), 2);
    al_draw_rectangle(introduction_button_x, introduction_button_y, introduction_button_x+introduction_button_width, introduction_button_y+introduction_button_height, al_map_rgb(0, 0, 0), 2);
    al_draw_rectangle(exit_button_x, exit_button_y, exit_button_x+exit_button_width, exit_button_y+exit_button_height, al_map_rgb(0, 0, 0), 2);

    al_draw_text(FC->caviar_dreams[24], al_map_rgb(0, 0, 0),
                 play_button_x + play_button_width / 2, play_button_y + play_button_height / 2 - 12,
                 ALLEGRO_ALIGN_CENTER, "Start Game");
    al_draw_text(FC->caviar_dreams[24], al_map_rgb(0, 0, 0),
                 setting_button_x + setting_button_width / 2, setting_button_y + setting_button_height / 2 - 12,
                 ALLEGRO_ALIGN_CENTER, "Setting");
    al_draw_text(FC->caviar_dreams[24], al_map_rgb(0, 0, 0),
                 introduction_button_x + introduction_button_width / 2, introduction_button_y + introduction_button_height / 2 - 12,
                 ALLEGRO_ALIGN_CENTER, "Introduction");
    al_draw_text(FC->caviar_dreams[24], al_map_rgb(0, 0, 0),
                 exit_button_x + exit_button_width / 2, exit_button_y + exit_button_height / 2 - 12,
                 ALLEGRO_ALIGN_CENTER, "Exit");
}

void Menu::destroy() {
    // std::cout << "Menu destroyed" << std::endl;
}
