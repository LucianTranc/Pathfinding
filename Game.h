#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include <sstream>
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include "MazeManager.h"

class MazeManager;

class Game

{

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void loadAssets();
	void handleEvents();
	void start();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	MazeManager * mazeManager;

	static SDL_Renderer *renderer;
	static SDL_Event event;
	static bool isRunning;

private:

	SDL_Window* window;

};

