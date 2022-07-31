#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include "../glm/glm.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "../Grid.h"

using std::string;
using std::vector;
using std::pair;
using std::deque;

#define GLM_ENABLE_EXPERIMENTAL
using glm::vec2;
using glm::vec4;

class Grid;

class PathfindingAlgorithm {

public:


    virtual void initializeAlgorithm(int x, int y, bool animate) = 0;
    virtual void update() = 0;
    virtual ~PathfindingAlgorithm() {};


    bool isPathFound();
    bool isActive();

protected:

    bool pathFound;
    bool active;
    Grid * grid;
    vector<vec2> path;
};