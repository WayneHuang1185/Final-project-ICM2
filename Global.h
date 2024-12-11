#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#include <stdio.h>
#include <allegro5/allegro.h>
#define GAME_TERMINATE -1
#include "shapes/Point.h"

#define MAX_ELEMENT 100
enum class Scenetype{
    Menu, 
    Setting,
    Introduction,
    Game_earth, 
    Game_earth_2,
    Game_moon,
    Fail,
    Ending,
    Leave,
};
struct RectangleParams {
    int move_type=-1;
    bool can_move = false;
    bool visible = true;
    bool can_hold = true;
    double vx = 0;
    double vy = 0;
    double x_length = 0;
    double y_length = 0;
    double left_boundary = 0;
    double right_boundary = 0;
};
extern Scenetype window;
extern bool key_state[ALLEGRO_KEY_MAX];
extern bool mouse_state[ALLEGRO_MOUSE_MAX_EXTRA_AXES];
extern Point mouse;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_EVENT event;
extern ALLEGRO_TIMER *fps;
extern bool debug_mode;


#endif