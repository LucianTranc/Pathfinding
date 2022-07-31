#include <SDL.h>
#include "Game.h"
#include <iostream>

Game* game = nullptr;

int main(int argc, char* argv[]) {


	const int FPS = 120;
	const int frameDelay = 1000 / FPS;
	
	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->init("Pathfinding", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	game->createGameObjects();

	game->start();

	while (game->running()) {

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}

	}

	game->clean();
	
	return 0;

}