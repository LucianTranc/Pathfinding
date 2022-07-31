#include "Game.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
	
bool Game::isRunning = false;



Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{

	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		std::cout << "Subsystems initialized!...\n";
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window Created\n";
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer Created\n";
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	if (TTF_Init() == -1)
	{
		std::cout << "Error : SDL_TTF" << std::endl;
	}

}

void Game::ButtonOneCallback()
{
	std::cout<<"button one"<<std::endl;
	gridManager->resetPassages();
}

void Game::ButtonTwoCallback()
{
	std::cout<<"button two"<<std::endl;
}

void Game::ButtonThreeCallback()
{
	std::cout<<"button three"<<std::endl;
}

void Game::createGameObjects()
{
	gridManager = new GridManager();
	uiManager = new UIManager();

	uiManager->addButton(650, 100, 100, 50, {150,0,0,255}, {0,150,0,255}, {0,0,150,255}, this, &Game::ButtonOneCallback);
	uiManager->addButton(650, 200, 100, 50, {150,0,0,255}, {0,150,0,255}, {0,0,150,255}, this, &Game::ButtonTwoCallback);
	uiManager->addButton(650, 300, 100, 50, {150,0,0,255}, {0,150,0,255}, {0,0,150,255}, this, &Game::ButtonThreeCallback);
	uiManager->addLabel(650, 300, 100, 50, "example", {255,0,255});
}

void Game::start()
{
	gridManager->start();
	uiManager->start();
}

void Game::handleEvents()
{
	if (uiManager == nullptr)
	{
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
		}
	}
	else if (!uiManager->isRunning)
	{
		isRunning = false;
	}
	
}

void Game::update()
{
	gridManager->update();
	uiManager->update();
}


void Game::render() 
{
    SDL_SetRenderDrawColor( Game::renderer, 255, 255, 255, 255 );

	SDL_RenderClear(renderer);

	gridManager->draw(renderer);

	uiManager->draw(renderer);

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned\n";
}

