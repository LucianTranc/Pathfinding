#include "Game.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
	
bool Game::isRunning = false;



Game::Game() {}

Game::~Game() {
	delete gridManager;
	delete uiManager;
}

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

void Game::createGameObjects()
{
	gridManager = new GridManager();
	uiManager = new UIManager();

	uiManager->addButton(650, 0, 100, 40, {150,0,0,255}, {0,150,0,255}, {0,0,150,255}, gridManager, &GridManager::generateMaze);
	uiManager->addLabel(650, 0, 100, 40, "generate maze", {255,0,255});

	uiManager->addButton(650, 50, 100, 40, {150,0,0,255}, {0,150,0,255}, {0,0,150,255}, gridManager, &GridManager::triggerDijkstra);
	uiManager->addLabel(650, 50, 100, 40, "Dijkstra", {255,0,255});
	
	uiManager->addButton(650, 100, 100, 40, {150,0,0,255}, {0,150,0,255}, {0,0,150,255}, gridManager, &GridManager::triggerAStar);
	uiManager->addLabel(650, 100, 100, 40, "AStar", {255,0,255});
	
	uiManager->addButton(650, 150, 100, 40, {150,0,0,255}, {0,150,0,255}, {0,0,150,255}, gridManager, &GridManager::triggerBFS);
	uiManager->addLabel(650, 150, 100, 40, "BFS", {255,0,255});

	uiManager->addButton(650, 200, 100, 40, {150,0,0,255}, {0,150,0,255}, {0,0,150,255}, gridManager, &GridManager::triggerDFS);
	uiManager->addLabel(650, 200, 100, 40, "DFS", {255,0,255});

	uiManager->addButton(650, 250, 100, 40, {150,0,0,255}, {0,150,0,255}, {0,0,150,255}, gridManager, &GridManager::resetPassages);
	uiManager->addLabel(650, 250, 100, 40, "reset", {255,0,255});

	uiManager->addButton(650, 300, 100, 40, {150,0,0,255}, {0,150,0,255}, {0,0,150,255}, gridManager, &GridManager::clearGrid);
	uiManager->addLabel(650, 300, 100, 40, "clear", {255,0,255});

	uiManager->addButton(650, 400, 100, 40, {150,0,0,255}, {0,150,0,255}, {0,0,150,255}, gridManager, &GridManager::drawStateBlocked);
	uiManager->addLabel(650, 400, 100, 40, "draw blocked", {255,0,255});

	uiManager->addButton(650, 450, 100, 40, {150,0,0,255}, {0,150,0,255}, {0,0,150,255}, gridManager, &GridManager::drawStatePassage);
	uiManager->addLabel(650, 450, 100, 40, "draw passage", {255,0,255});

	uiManager->addButton(650, 500, 100, 40, {150,0,0,255}, {0,150,0,255}, {0,0,150,255}, gridManager, &GridManager::drawStateStart);
	uiManager->addLabel(650, 500, 100, 40, "draw start", {255,0,255});

	uiManager->addButton(650, 550, 100, 40, {150,0,0,255}, {0,150,0,255}, {0,0,150,255}, gridManager, &GridManager::drawStateEnd);
	uiManager->addLabel(650, 550, 100, 40, "draw end", {255,0,255});
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

