#include "Game.h"
#include "Menu.h"
#include "Window.h"

#include <iostream>

int main(int argc, char **argv) {
	Game *game = new Game();
	game->execute();
	delete game;
	return 0;
}
