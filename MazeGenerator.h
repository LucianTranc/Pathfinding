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
    void computeFrontierCells(vec2 cell);
    bool popRandomFrontierCell(vec2 * outCell);
    void makePassage(vec2 frontierCell);
    void generateMaze(int x, int y, bool animate);
    bool generationComplete;
    bool active;

private:
    Grid * grid;
    vector<vec2> frontierCells;
};