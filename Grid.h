#pragma once
#include "Game.h"


using std::string;
using std::vector;

#define GLM_ENABLE_EXPERIMENTAL
using glm::vec2;
using glm::vec4;

struct Colour
{
    string name;
    vec4 rgba;
} typedef Colour;

class Grid {

public:

    Grid(int x, int y, int w, int h, int grid_x, int grid_y);
    void setGridArray(vector<vector<int>> array);
	void zeroGrid();
	void randomizeGrid();
	void setGridColourOfPosition(int x, int y, string colour);
	void addColour(string name, vec4 rgba);
	void draw();
    void printGrid();

private:
    vec2 position;
    vec2 size;
    vec2 gridSize;
    float scale;
    vector<vector<int>> gridArray;
    std::map <int, Colour> colourMap;
};