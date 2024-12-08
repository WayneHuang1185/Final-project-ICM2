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

    //Load the background
    background_img = IC->get(Resource::earth_background_img_path);
	earth_wall = IC->get(Resource::earth_wall);
	earth_land = IC->get(Resource::earth_land);
	earth_mud = IC->get(Resource::earth_mud);

	DC->platforms->loadmap(Resource::map_earth_2, DC->window_width, DC->window_height);
	DC->platforms->textures[1] = earth_land;
	DC->platforms->textures[2] = earth_mud;
	DC->platforms->textures[3] = earth_wall;

	SC->init();
	FC->init();

    // Initialize other elements
    DC->hero->init();
    DC->platforms->init();

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

	if (DC->key_state[ALLEGRO_KEY_P] && !DC->prev_key_state[ALLEGRO_KEY_P]) {
        if (state == STATE::PLAYING) {
			SC->toggle_playing(background_music);
            state = STATE::PAUSE; 
			BGM_played = false;
        } else if (state == STATE::PAUSE) {
            state = STATE::PLAYING; 
			BGM_played = true;
        }
    }

	if(DC->key_state[ALLEGRO_KEY_ESCAPE]){
		std::cout << "switch to menu" << std::endl;
		SC->stop_playing(background_music);
		window = 0;
		return false;
	}

	if(state != STATE::PAUSE){
		DC->hero->update();

		DC->platforms->update();

		OC->update();
		// game_update is finished. The states of current frame will be previous states of the next frame.
	}

	memcpy(DC->prev_key_state, DC->key_state, sizeof(DC->key_state));
	memcpy(DC->prev_mouse_state, DC->mouse_state, sizeof(DC->mouse_state));

	return true;
}

void Gamescene_earth2::draw(){
	DataCenter *DC = DataCenter::get_instance();
	OperationCenter *OC = OperationCenter::get_instance();
	FontCenter *FC = FontCenter::get_instance();
	//Flush the screen first.
	al_clear_to_color(al_map_rgb(100, 100, 100));
	// background
    al_draw_bitmap(background_img, 0, 0, 0);

	DC->hero->draw();
	OC->draw();
	DC->platforms->draw();
	switch(state) {
		case STATE::PLAYING:{
			break;
		}
		case STATE::PAUSE: {
			// game layout cover
			al_draw_filled_rectangle(0, 0, DC->window_width, DC->window_height, al_map_rgba(50, 50, 50, 64));
			al_draw_text(
				FC->caviar_dreams[FontSize::LARGE], al_map_rgb(255, 255, 255),
				DC->window_width/2., DC->window_height/2.,
				ALLEGRO_ALIGN_CENTRE, "GAME PAUSED");
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