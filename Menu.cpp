#include "Menu.h"
#include "Utils.h"
#include "Window.h"
#include "data/DataCenter.h"
#include "data/OperationCenter.h"
#include "data/SoundCenter.h"
#include "data/ImageCenter.h"
#include "data/FontCenter.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <vector>
#include <cstring>

void Menu::execute() {
	DataCenter *DC = DataCenter::get_instance();

	bool run = true;
	while (run) {
		while (al_get_next_event(event_queue, &event)) {
			switch (event.type) {
				case ALLEGRO_EVENT_DISPLAY_CLOSE:
					run = false;
					break;
				case ALLEGRO_EVENT_KEY_DOWN:
					DC->key_state[event.keyboard.keycode] = true;
					break;
				case ALLEGRO_EVENT_KEY_UP:
					DC->key_state[event.keyboard.keycode] = false;
					break;
				case ALLEGRO_EVENT_MOUSE_AXES:
					DC->mouse.x = event.mouse.x;
					DC->mouse.y = event.mouse.y;
					break;
				case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
					DC->mouse_state[event.mouse.button] = true;
					break;
				case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
					DC->mouse_state[event.mouse.button] = false;
					break;
				default:
					break;
			}
		}

	if (menu_update()) {
			menu_draw();
		}
	}
}


Menu::Menu(){
	DataCenter *DC = DataCenter::get_instance();
	GAME_ASSERT(al_init(), "failed to initialize allegro.");

	bool addon_init = true;
	addon_init &= al_init_primitives_addon();
	addon_init &= al_init_font_addon();
	addon_init &= al_init_ttf_addon();
	addon_init &= al_init_image_addon();
	addon_init &= al_init_acodec_addon();
	GAME_ASSERT(addon_init, "failed to initialize allegro addons.");

	// initialize events
	bool event_init = true;
	event_init &= al_install_keyboard();
	event_init &= al_install_mouse();
	event_init &= al_install_audio();
	GAME_ASSERT(event_init, "failed to initialize allegro events.");

	GAME_ASSERT(
		display = al_create_display(DC->window_width, DC->window_height),
		"failed to create display.");
	GAME_ASSERT(
		timer = al_create_timer(1.0 / DC->FPS),
		"failed to create timer.");
	GAME_ASSERT(
		event_queue = al_create_event_queue(),
		"failed to create event queue.");

	debug_log("Game initialized.\n");
	menu_init();
}

void Menu::menu_init(){
	DataCenter *DC = DataCenter::get_instance();
	SoundCenter *SC = SoundCenter::get_instance();
	ImageCenter *IC = ImageCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();
	// set window icon

	hover = false;
	font = al_create_builtin_font(); 
	button_x = (DC->window_width - button_width)/2;
	button_y = (DC->window_height - button_height)/2;

	// register events to event_queue

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);
}

bool Menu::menu_update() {
	DataCenter *DC = DataCenter::get_instance();

	hover = DC->mouse.x >= button_x && DC->mouse.x <= button_x + button_width &&
			DC->mouse.y >= button_y && DC->mouse.y <= button_y + button_height;

	if (DC->mouse_state[1] && hover) {
		current_window = Window::earth;
		debug_log("Button clicked!\n");
		return false;
		
	}

	memcpy(DC->prev_key_state, DC->key_state, sizeof(DC->key_state));
	memcpy(DC->prev_mouse_state, DC->mouse_state, sizeof(DC->mouse_state));
	return true;
}


void Menu::menu_draw() {
	al_clear_to_color(al_map_rgb(100, 100, 200));

	// 根据鼠标悬停状态更改按钮颜色
	ALLEGRO_COLOR button_color = hover ? al_map_rgb(200, 200, 255) : al_map_rgb(255, 255, 255);

	al_draw_filled_rectangle(
		button_x, button_y,
		button_x + button_width, button_y + button_height,
		button_color
	);

	al_draw_rectangle(
		button_x, button_y,
		button_x + button_width, button_y + button_height,
		al_map_rgb(0, 0, 0),
		2.0
	);
	
	al_draw_text(
		font,
		al_map_rgb(0, 0, 0), 
		button_x + button_width / 2,
		button_y + button_height / 2,
		ALLEGRO_ALIGN_CENTER,
		"PLAY"
	);

	al_flip_display();
}


Menu::~Menu(){
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_font(font);
}


