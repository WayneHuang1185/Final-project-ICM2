#include "Hero.h"
#include "data/DataCenter.h"
#include "data/GIFCenter.h"
#include "algif5/algif.h"
#include <allegro5/allegro_primitives.h>
#include "shapes/Rectangle.h"
#include "Platform.h"
#include <iostream>

namespace HeroSetting {
	static constexpr char gif_root_path[50] = "./assets/gif/Hero";
	static constexpr char gif_postfix[][10] = {
		"left", "right", "front", "back"
	};
}

void Hero::init(){
    for(size_t type = 0 ; type < static_cast<size_t>(HeroState::HEROSTATE_MAX) ; type++){
        char buffer[50];
        sprintf(buffer, "%s/dragonite_%s.gif",
                HeroSetting::gif_root_path,
                HeroSetting::gif_postfix[static_cast<int>(type)]);
        gifpath[static_cast<HeroState>(type)] = std::string(buffer);
    }
    GIFCenter *GIFC = GIFCenter::get_instance();
    ALGIF_ANIMATION *gif = GIFC->get(gifpath[state]);
    DataCenter *DC = DataCenter::get_instance();

    double x_offset = -600;
    double y_offset = -30;

    shape.reset(
        new Rectangle(
            DC->window_width / 2 - gif->width / 2 + x_offset,
            DC->window_height / 2 - gif->height / 2 + y_offset,
            DC->window_width / 2 + gif->width / 2 + x_offset,
            DC->window_height / 2 + gif->height / 2 + y_offset
        )
    );
}

void Hero::update() {
    DataCenter* DC = DataCenter::get_instance();
    Platform* platforms = DC->platforms;

    Rectangle* rect = dynamic_cast<Rectangle*>(shape.get());
    if (!rect) return;

    if (DC->key_state[ALLEGRO_KEY_W] && !DC->prev_key_state[ALLEGRO_KEY_W] && jump_count < 2) {
        v_speed = jump_speed;
        is_jumping = true;
        jump_count++;
    }

    if (DC->key_state[ALLEGRO_KEY_A]) {
        rect->update_center_x(rect->center_x() - speed);
        state = HeroState::LEFT;
    } else if (DC->key_state[ALLEGRO_KEY_D]) {
        rect->update_center_x(rect->center_x() + speed);
        state = HeroState::RIGHT;
    }

    rect->update_center_y(rect->center_y() + v_speed);
    v_speed += gravity;

    bool on_platform = false;
    for (const auto& platform : platforms->get_platforms()) {
        if (rect->y2 >= platform.y1 && rect->y1 < platform.y1 && 
            rect->x2 > platform.x1 && rect->x1 < platform.x2 &&  
            v_speed >= 0) { 
            rect->update_center_y(platform.y1 - (rect->y2 - rect->y1) / 2); 
            v_speed = 0;  
            is_jumping = false;  
            on_platform = true;
            jump_count = 0;
            break;
        }
    }

    if (!on_platform && rect->y2 < DC->window_height) {
        is_jumping = true; 
    } else if (rect->y2 >= DC->window_height) {
        rect->update_center_y(DC->window_height - (rect->y2 - rect->y1) / 2);
        v_speed = 0;
        is_jumping = false;
        jump_count = 0;
    }
}

void Hero::draw(){
    GIFCenter *GIFC = GIFCenter::get_instance();
    ALGIF_ANIMATION *gif = GIFC->get(gifpath[state]);
    DataCenter* DC = DataCenter::get_instance(); 

    algif_draw_gif(gif, shape->center_x() - gif->width/2, shape->center_y()-gif->height/2, 0);    
    
    Rectangle* rect = dynamic_cast<Rectangle*>(shape.get()); 
    if (rect) {
        al_draw_rectangle(
            rect->x1, rect->y1, rect->x2, rect->y2,
            al_map_rgb(255, 0, 0), 
            2.0 
        );
    }
}