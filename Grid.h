#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "glm/glm.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using std::string;
using std::vector;
using std::pair;

#define GLM_ENABLE_EXPERIMENTAL
using glm::vec2;
using glm::vec4;

class Grid {

public:

    enum State {passage, blocked, frontier, start, end, inQueue, searched, path, open, closed} ;

    Grid(int x, int y, int w, int h, int grid_x, int grid_y, int boarder);
    void setGridArray(vector<vector<int>> array);
	void setGridToState(State state);
    void resetPassages();
	void randomizeGrid();
	bool setPositionToState(int x, int y, State state);
	pair<int, int> setRandomPositionToState(State state);
    bool isStateAtPosition(int x, int y, State state);
	void draw(SDL_Renderer * renderer);
    void printGrid();
    bool getCellWithState(vec2 * outCell, State state);
    vector<vector<int>> gridArray;
    vec2 screenToGridPosition(int x, int y);


private:

    vec2 position;
    vec2 size;
    vec2 gridSize;
    float scale;
    int boarderWidth;

    SDL_Rect boarderRect;

    std::map<State, vec4> colourMap = {
        { passage   , {255, 255, 255, 255} },
        { blocked   , {  0,   0,   0, 255} },
        { frontier  , {255, 255,   0, 255} },
        { start     , {  0, 255,   0, 255} },
        { end       , {255,   0,   0, 255} },
        { inQueue   , {131, 162, 247, 255} },
        { searched  , {110, 200, 255, 255} },
        { path      , {255, 145,   0, 255} },
        { open      , {131, 162, 247, 255} },
        { closed    , {110, 200, 255, 255} }
    } ;

};