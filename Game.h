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
#include "Grid.h"


class ColliderComponent;
class AssetManager;
//class UIStatistics;
class Grid;

class Game

{

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void loadAssets();
	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	Grid * grid;

	static SDL_Renderer *renderer;
	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;
	static AssetManager *assets;
	//static UIStatistics *statManager;
	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles,
		groupUILables
	};
private:
	//int cnt;
	SDL_Window* window;

};

