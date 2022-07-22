#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include "glm/glm.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Grid.h"


using std::string;
using std::vector;
using std::pair;
using std::deque;

#define GLM_ENABLE_EXPERIMENTAL
using glm::vec2;
using glm::vec4;

class Grid;

class Pathfinder {

public:

    struct Cell {
        vec2 position;
        vec2 parentCellPosition;
    } typedef Cell;

    Pathfinder(Grid * g);
    void update();
    void findPath(int x, int y, bool animate);
    void addNeighboursToQueue(Cell cell);
    bool endFound(Cell cell);
    void retracePath(Cell cell);

    bool pathFound;
    bool active;

private:
    Grid * grid;
    vector<Cell> searched;
    deque<Cell> deque;
};