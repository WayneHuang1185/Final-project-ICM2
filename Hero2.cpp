#include "Hero2.h"
#include "data/DataCenter.h"
#include "data/GIFCenter.h"
#include "algif5/algif.h"
#include "shapes/Rectangle.h"

void Hero2::update(){
    DataCenter *DC = DataCenter::get_instance();
    if(DC->key_state[ALLEGRO_KEY_UP]){
        shape->update_center_y(shape->center_y() - speed);
        state = HeroState::BACK;
    }
    else if(DC->key_state[ALLEGRO_KEY_LEFT]){
        shape->update_center_x(shape->center_x() - speed);
        state = HeroState::LEFT;
    }
    else if(DC->key_state[ALLEGRO_KEY_DOWN]){
        shape->update_center_y(shape->center_y() + speed);
        state = HeroState::FRONT;
    }
    else if(DC->key_state[ALLEGRO_KEY_RIGHT]){
        shape->update_center_x(shape->center_x() + speed);
        state = HeroState::RIGHT;
    }
}