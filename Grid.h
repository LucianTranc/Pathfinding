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

#define GLM_ENABLE_EXPERIMENTAL
using glm::vec2;
using glm::vec4;

class Grid {

public:

    enum Colour { white, black, red, green, blue } ;

    Grid(int x, int y, int w, int h, int grid_x, int grid_y);
    void setGridArray(vector<vector<int>> array);
	void zeroGrid();
	void randomizeGrid();
	void setPositionToColour(int x, int y, Colour colour);
	void setRandomPositionToColour(Colour colour);
	void draw(SDL_Renderer * renderer);
    void printGrid();

private:

    vec2 position;
    vec2 size;
    vec2 gridSize;
    float scale;
    vector<vector<int>> gridArray;

    std::map<Colour, vec4> colourMap = {
        { white, {255, 255, 255, 255} },
        { black, {  0,   0,   0, 255} },
        { red  , {255,   0,   0, 255} },
        { green, {  0, 255,   0, 255} },
        { blue , {  0,   0, 255, 255} }
    } ;

};