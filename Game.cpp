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

	int d = 80;
	int p = 250;

	uiManager->addButton(600, 12, 190, 40, {42,99,46,255}, {50,120,55,255}, {26,64,29,255}, gridManager, &GridManager::generateMaze);
	uiManager->addLabel(610, 12, 170, 40, "Generate Maze", {255,255,255});

	uiManager->addLabel(600, d, 170, 30, "Drawing Options:", {0, 0, 0});

	uiManager->addButton(600, d + 40, 90, 40, {0,0,0,255}, {25,25,25,255}, {0,0,0,255}, gridManager, &GridManager::drawStateBlocked);

	uiManager->addButton(700, d + 40, 90, 40, {255,255,255,255}, {230,230,230,255}, {255,255,255,255}, gridManager, &GridManager::drawStatePassage);

	uiManager->addButton(600, d + 90, 90, 40, {0,255,0,255}, {75,255,75,255}, {0,235,0,255}, gridManager, &GridManager::drawStateStart);

	uiManager->addButton(700, d + 90, 90, 40, {255,0,0,255}, {255,75,75,255}, {235,0,0,255}, gridManager, &GridManager::drawStateEnd);

	uiManager->addLabel(600, p, 130, 30, "Pathfinding:", {0, 0, 0});

	uiManager->addButton(600, p + 40, 190, 40, {42,99,46,255}, {50,120,55,255}, {26,64,29,255}, gridManager, &GridManager::triggerDijkstra);
	uiManager->addLabel(610, p + 40, 100, 40, "Dijkstra", {255,255,255});
	
	uiManager->addButton(600, p + 90, 190, 40, {42,99,46,255}, {50,120,55,255}, {26,64,29,255}, gridManager, &GridManager::triggerAStar);
	uiManager->addLabel(610, p + 90, 70, 40, "AStar", {255,255,255});
	
	uiManager->addButton(600, p + 140, 190, 40, {42,99,46,255}, {50,120,55,255}, {26,64,29,255}, gridManager, &GridManager::triggerBFS);
	uiManager->addLabel(610, p + 140, 50, 40, "BFS", {255,255,255});

	uiManager->addButton(600, p + 190, 190, 40, {42,99,46,255}, {50,120,55,255}, {26,64,29,255}, gridManager, &GridManager::triggerDFS);
	uiManager->addLabel(610, p + 190, 50, 40, "DFS", {255,255,255});

	uiManager->addButton(600, 548, 90, 40, {42,99,46,255}, {50,120,55,255}, {26,64,29,255}, gridManager, &GridManager::resetPassages);
	uiManager->addLabel(610, 548, 70, 40, "Reset", {255,255,255});

	uiManager->addButton(700, 548, 90, 40, {42,99,46,255}, {50,120,55,255}, {26,64,29,255}, gridManager, &GridManager::clearGrid);
	uiManager->addLabel(710, 548, 70, 40, "Clear", {255,255,255});

	
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
	// updating 4 times to speed up algorithm while still only rendering 30 fps
	gridManager->update();
	gridManager->update();
	gridManager->update();
	gridManager->update();

	uiManager->update();
}


void Game::render() 
{
    SDL_SetRenderDrawColor( Game::renderer, 219, 219, 219, 255 );

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

