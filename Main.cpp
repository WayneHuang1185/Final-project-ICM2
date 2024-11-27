#include "Game.h"
#include "Menu.h"
#include "Window.h"
#include <iostream>

Menu *menu = nullptr;
Game *game = nullptr;

int main(int argc, char **argv) {
	switch(current_window){
		case Window::menu:
			menu = new Menu();
			menu->execute();
			break;
		case Window::earth:
			game = new Game();
			game->execute();
			break;
		case Window::exit:
			break;
		case Window::fail:
			break;
		case Window::ending:
			break;
	}
	delete menu;
	delete game;
	return 0;
}
