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
#include "Pathfinder.h"

using std::string;
using std::vector;
using std::pair;

#define GLM_ENABLE_EXPERIMENTAL
using glm::vec2;
using glm::vec4;

class Grid;
class MazeGenerator;
class Pathfinder;

class GridManager {

public:

    GridManager();
    void start();
    void update();
    void draw(SDL_Renderer * renderer);
    void setStartAndEndCells();

private:
    Grid * grid;
    MazeGenerator * mazeGenerator;
    Pathfinder * pathfinder;
};