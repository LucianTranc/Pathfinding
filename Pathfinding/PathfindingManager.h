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
#include "PathfindingAlgorithm.h"
#include "DepthFirstSearch.h"
#include "BreadthFirstSearch.h"
#include "AStar.h"


using std::string;
using std::vector;
using std::pair;
using std::deque;

#define GLM_ENABLE_EXPERIMENTAL
using glm::vec2;
using glm::vec4;

class Grid;

class PathfindingManager {

public:

    enum Algorithm {BFS, DFS, Dijkstra, aStar} ;

    PathfindingManager(Grid * g);
    void update();
    void findPath(int x, int y, Algorithm algorithmName, bool animate);

    bool pathFound;
    bool active;

    PathfindingAlgorithm * activeAlgorithm;
    Algorithm algorithm;

private:
    Grid * grid;
};