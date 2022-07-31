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
#include "MazeGenerator.h"
#include "Pathfinding/PathfindingManager.h"

using std::string;
using std::vector;
using std::pair;

#define GLM_ENABLE_EXPERIMENTAL
using glm::vec2;
using glm::vec4;

class Grid;
class MazeGenerator;
class PathfindingManager;

class GridManager {

public:

    GridManager();
    void start();
    void update();
    void draw(SDL_Renderer * renderer);
    std::pair<vec2, vec2> setStartAndEndCells();
    void resetPassages();

private:
    Grid * grid;
    MazeGenerator * mazeGenerator;
    PathfindingManager * pathfindingManager;
};