#include "DataCenter.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include "../Level.h"
#include "../Player.h"
#include "../monsters/Monster.h"
#include "../towers/Tower.h"
#include "../towers/Bullet.h"

#include "../Hero.h"
#include "../Hero2.h"
#include "../Platform.h"

// fixed settings
namespace DataSetting {
	constexpr double FPS = 60;
	constexpr int window_width = 1440;
	constexpr int window_height = 900;
	constexpr int game_field_length = 1000;
}

DataCenter::DataCenter() {
	this->FPS = DataSetting::FPS;
	this->window_width = DataSetting::window_width;
	this->window_height = DataSetting::window_height;
	this->game_field_length = DataSetting::game_field_length;
	memset(key_state, false, sizeof(key_state));
	memset(prev_key_state, false, sizeof(prev_key_state));
	mouse = Point(0, 0);
	memset(mouse_state, false, sizeof(mouse_state));
	memset(prev_mouse_state, false, sizeof(prev_mouse_state));
	// player = new Player();
	// level = new Level();

	hero = new Hero();
	hero2 = new Hero2();

	platforms = new Platform();

	platforms->loadmap("./assets/map.txt", window_width, window_height);
}

DataCenter::~DataCenter() {
	// delete player;
	// delete level;
	// for(Monster *&m : monsters) {
	// 	delete m;
	// }
	// for(Tower *&t : towers) {
	// 	delete t;
	// }
	// for(Bullet *&b : towerBullets) {
	// 	delete b;
	// }
	delete hero;
	delete hero2;

	delete platforms;
}