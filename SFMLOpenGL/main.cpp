// Author: Ben Millar C00236772
// Date: 18/03/2020

#define TINYC2_IMPL

#include "Game.h"

int main()
{
	srand(static_cast<unsigned>(std::time(nullptr)));
	Game game;
	game.run();
	return EXIT_SUCCESS;
}