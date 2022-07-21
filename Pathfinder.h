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

    Pathfinder(Grid * g);
    void update();
    void findPath(int x, int y, bool animate);
    void addNeighboursToQueue(pair<pair<int,int>,pair<int,int>> cell);
    bool endFound(pair<pair<int,int>,pair<int,int>> cell);
    void retracePath(pair<pair<int,int>,pair<int,int>> cell);

    bool pathFound;

private:
    Grid * grid;
    vector<pair<pair<int,int>, pair<int,int>>> searched;
    deque<pair<pair<int,int>, pair<int,int>>> deque;
};