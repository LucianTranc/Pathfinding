#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "glm/glm.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Grid.h"


using std::string;
using std::vector;
using std::pair;

#define GLM_ENABLE_EXPERIMENTAL
using glm::vec2;
using glm::vec4;

class Grid;

class MazeGenerator {

public:

    MazeGenerator(Grid * g);
    void update();
    void computeFrontierCells(pair<int, int> cell);
    bool popRandomFrontierCell(pair<int, int> * outCell);
    void makePassage(pair<int, int> frontierCell);
    void generateMaze(int x, int y, bool animate);
    bool generationComplete;

private:
    Grid * grid;
    vector<pair<int, int>> frontierCells;
};