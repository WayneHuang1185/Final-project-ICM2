#include "Game.h"
#include "Menu.h"
#include "Window.h"
#include <iostream>

int main(int argc, char **argv) {
	Game *game = new Game();	
	game->execute();
	switch(current_window){
		case Window::menu:
			break;
		case Window::earth:
			break;
		case Window::exit:
			break;
		case Window::fail:
			break;
		case Window::ending:
			break;
	}
	delete game;
	return 0;
}
