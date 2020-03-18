#include "Game.h"

int main()
{
	srand(static_cast<unsigned>(std::time(nullptr)));
	Game game;
	game.run();
	return EXIT_SUCCESS;
}