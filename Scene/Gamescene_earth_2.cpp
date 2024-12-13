#include "Gamescene_earth_2.h"

ALLEGRO_SAMPLE_INSTANCE *Gamescene_earth2::background_music = nullptr;

Gamescene_earth2::Gamescene_earth2(){
    init();
}

Gamescene_earth2::~Gamescene_earth2() {
    destroy();
}

void Gamescene_earth2::init() {
    DataCenter *DC = DataCenter::get_instance();
    SoundCenter *SC = SoundCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();

	Platform *PLT=DC->platforms;

	SC->init();
	FC->init();
	RectangleParams move_block_1 = {1,true,true,true,false,2.0, 0.0, 0.0, DC->window_width/20*7};
	RectangleParams move_block_2 = {1,true,true,true,false,2.0, 0.0, DC->window_width/20*8, DC->window_width/20*15};
	RectangleParams move_block_3 = {1,true,true,true,false,4.0, 0.0, 0.0, DC->window_width/20*15};
	
    //Load the background
    background_img = IC->get(Resource::earth_background_img_path);
	earth_wall = IC->get(Resource::earth_wall);
	earth_land = IC->get(Resource::earth_land);
	earth_mud = IC->get(Resource::earth_mud);
	earth_ice = IC->get(Resource::moon_ice);
	earth_cloud = IC->get(Resource::earth_cloud);
	earth_bird = IC->get(Resource::earth_bird);
	earth_goldbirck = IC->get(Resource::earth_goldbrick);
	earth_ladder = IC->get(Resource::earth_ladder);
	earth_to_moon_rocket = IC->get(Resource::earth_to_moon_rocket);

	mode[1]=normal_block;
	mode[2]=normal_block;
	mode[3]=ice_block;
	mode[4]=move_block_1;
	mode[5]=normal_block;
	mode[6]=move_block_3;
	mode[8]=move_block_2;
	mode[9]=normal_block;
	DC->platforms->loadmap(Resource::map_earth_2,mode,DC->window_width, DC->window_height);
	
	DC->platforms->textures[1] = earth_land;
	DC->platforms->textures[2] = earth_bird;
	DC->platforms->textures[3] = earth_ice;
	DC->platforms->textures[4] = earth_wall;
	DC->platforms->textures[5] = earth_ladder;
	DC->platforms->textures[6] = earth_wall;
	DC->platforms->textures[8] = earth_bird;
	DC->platforms->textures[9] = earth_goldbirck;
	
	
	DC->hero->init();
	hero_init();

	// Initialize other elements
    DC->platforms->init();
	DC->glasses->init();
	DC->rocket->init();

	button_width = 200;
	button_height = 100;
	pause_menu_button_x = pause_tryagain_button_x = (DC->window_width - button_width) / 2;
	pause_tryagain_button_y = DC->window_height / 2;
	pause_menu_button_y = pause_tryagain_button_y + 150;
	button_color = al_map_rgb(100, 200, 100);
	button_hover_color = al_map_rgb(150, 250, 150);  

	DC->hero->die_x_start = DC->window_width/20;
	DC->hero->die_x_end = DC->window_width;

	DC->hero->teleport_to_moon = false;

	state = STATE::PLAYING;

	Gamescene_earth2::BGM_played = true;
}


bool Gamescene_earth2::update() {
	DataCenter *DC = DataCenter::get_instance();
	OperationCenter *OC = OperationCenter::get_instance();
	SoundCenter *SC = SoundCenter::get_instance();

	if(BGM_played){
		background_music = SC->play(Resource::earth_background_music, ALLEGRO_PLAYMODE_LOOP);
		BGM_played = false;
	}

	if (DC->key_state[ALLEGRO_KEY_ESCAPE] && !DC->prev_key_state[ALLEGRO_KEY_ESCAPE]) {
        if (state == STATE::PLAYING) {
			SC->toggle_playing(background_music);
            state = STATE::PAUSE; 
			BGM_played = false;
        } else if (state == STATE::PAUSE) {
            state = STATE::PLAYING; 
			BGM_played = true;
        }
    }

	if(state == STATE::PLAYING){
		DC->hero->update();

		DC->platforms->update();

		DC->glasses->update();

		DC->rocket->update();

		OC->update();
		// game_update is finished. The states of current frame will be previous states of the next frame.
		if(DC->hero->hero_injured){
			DC->hero->init();
			hero_init();
			DC->hero->died_count++;
			DC->hero->hp = 3-DC->hero->died_count;
		}
		else if(DC->hero->hero_died){
			DC->hero->died_count = 0;
			std::cout << "Fail" << std::endl;
			SC->stop_playing(background_music);
			window = Scenetype::Fail;
			return false;
		}
		else if(DC->key_state[ALLEGRO_KEY_1]){
			SC->stop_playing(background_music);
			window = Scenetype::Game_moon;
			return false;
		}
	}

	if(state == STATE::PAUSE){
		if (DC->mouse_state[1] &&
			DC->mouse.x >= pause_menu_button_x && DC->mouse.x <= pause_menu_button_x + button_width &&
			DC->mouse.y >= pause_menu_button_y && DC->mouse.y <= pause_menu_button_y + button_height) {
			std::cout << "switch to menu" << std::endl;
			SC->stop_playing(background_music);
			window = Scenetype::Menu;  
			DC->hero->died_count = 0;
			DC->glasses->init();
			return false;
		}

		if (DC->mouse_state[1] &&
			DC->mouse.x >= pause_tryagain_button_x && DC->mouse.x <= pause_tryagain_button_x + button_width &&
			DC->mouse.y >= pause_tryagain_button_y && DC->mouse.y <= pause_tryagain_button_y + button_height) {
			std::cout << "Try Again" << std::endl;
			DC->hero->init();
            hero_init();
            state = STATE::PLAYING;
			BGM_played = true;
			DC->hero->died_count = 0;
			DC->glasses->init();
            return true;
		}
	}

	if(DC->hero->teleport_to_moon){
		DC->hero->died_count = 0;
		SC->stop_playing(background_music);
		window = Scenetype::earth2_to_moon;
		DC->hero->teleport_to_moon = false;
		return false;
	}

	
	std::cout << " teleport_to_moon:  " << DC->hero->teleport_to_moon << std::endl;

	memcpy(DC->prev_key_state, DC->key_state, sizeof(DC->key_state));
	memcpy(DC->prev_mouse_state, DC->mouse_state, sizeof(DC->mouse_state));

	return true;
}

void Gamescene_earth2::draw(){
	DataCenter *DC = DataCenter::get_instance();
	OperationCenter *OC = OperationCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();
	Rocket *rocket = DC->rocket;
	//Flush the screen first.
	al_clear_to_color(al_map_rgb(100, 100, 100));
	// background
	al_draw_bitmap(background_img, 0, 0, 0);

	OC->draw();
	DC->rocket->draw();
	if(!rocket->isgoing_up) DC->hero->draw();
	DC->platforms->draw();
	DC->glasses->draw();

	switch(state) {
		case STATE::PLAYING:{
			break;
		}
		case STATE::PAUSE: {

			al_draw_filled_rectangle(0, 0, DC->window_width, DC->window_height, al_map_rgba(50, 50, 50, 64));
			al_draw_text(
				FC->caviar_dreams[FontSize::LARGE], al_map_rgb(255, 255, 255),
				DC->window_width / 2., DC->window_height / 2. - 150,
				ALLEGRO_ALIGN_CENTRE, "GAME PAUSED");

			ALLEGRO_COLOR menu_color = button_color;
			if (DC->mouse.x >= pause_menu_button_x && DC->mouse.x <= pause_menu_button_x + button_width &&
				DC->mouse.y >= pause_menu_button_y && DC->mouse.y <= pause_menu_button_y + button_height) {
				menu_color = button_hover_color; 
			}
			al_draw_filled_rectangle(
				pause_menu_button_x, pause_menu_button_y,
				pause_menu_button_x + button_width, pause_menu_button_y + button_height,
				menu_color);
			al_draw_rectangle(
				pause_menu_button_x, pause_menu_button_y,
				pause_menu_button_x + button_width, pause_menu_button_y + button_height,
				al_map_rgb(0, 0, 0), 2.0); 
			al_draw_text(
				FC->caviar_dreams[FontSize::MEDIUM], al_map_rgb(0, 0, 0),
				pause_menu_button_x + button_width / 2,
				pause_menu_button_y + (button_height - al_get_font_line_height(FC->caviar_dreams[FontSize::MEDIUM])) / 2,
				ALLEGRO_ALIGN_CENTRE, "MENU");

			ALLEGRO_COLOR tryagain_color = button_color;
			if (DC->mouse.x >= pause_tryagain_button_x && DC->mouse.x <= pause_tryagain_button_x + button_width &&
				DC->mouse.y >= pause_tryagain_button_y && DC->mouse.y <= pause_tryagain_button_y + button_height) {
				tryagain_color = button_hover_color; 
			}
			al_draw_filled_rectangle(
				pause_tryagain_button_x, pause_tryagain_button_y,
				pause_tryagain_button_x + button_width, pause_tryagain_button_y + button_height,
				tryagain_color);
			al_draw_rectangle(
				pause_tryagain_button_x, pause_tryagain_button_y,
				pause_tryagain_button_x + button_width, pause_tryagain_button_y + button_height,
				al_map_rgb(0, 0, 0), 2.0);
			al_draw_text(
				FC->caviar_dreams[FontSize::MEDIUM], al_map_rgb(0, 0, 0),
				pause_tryagain_button_x + button_width / 2,
				pause_tryagain_button_y + (button_height - al_get_font_line_height(FC->caviar_dreams[FontSize::MEDIUM])) / 2,
				ALLEGRO_ALIGN_CENTRE, "TRY AGAIN");
			break;
		}
		case STATE::END:{
			break;
		}
	}
}


void Gamescene_earth2::destroy() {

	if(background_img) background_img = nullptr;
	if(background_music) background_music = nullptr;
	
    std::cout << "Gamescene_earth2 destroy" << std::endl;
}

void Gamescene_earth2::hero_init(){
	DataCenter *DC = DataCenter::get_instance();
	Platform *PLT=DC->platforms;

	DC->hero->hero_died = false;
	DC->hero->dash_length = PLT->get_block_height();
	DC->hero->dash_duration = 0.1*DC->FPS;
	DC->hero->max_jump_height = PLT->get_block_height()*3;
	DC->hero->max_jump_speed = -std::sqrt(1.5*DC->hero->up_gravity * DC->hero->max_jump_height);
	DC->hero->climb_speed = DC->hero->max_jump_speed/1.82;

	double spawn_x = DC->window_width/20;
	double spawn_y = 0;

	Rectangle* rect = dynamic_cast<Rectangle*>(DC->hero->shape.get());
    if (rect) {
        rect->update_center_x(spawn_x);
        rect->update_center_y(spawn_y);
    }
}