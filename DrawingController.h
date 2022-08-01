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
#include "UIManager.h"


using std::string;
using std::vector;
using std::pair;

#define GLM_ENABLE_EXPERIMENTAL
using glm::vec2;
using glm::vec4;

class Grid;
class UIManager;

class DrawingController {

public:

    DrawingController(Grid * g);
    void update();
    void setActive();
    void setInactive();
    void setDrawState(Grid::State s);
    vec2 screenToGridPosition();

    bool active;
private:
    Grid * grid;

    Grid::State state;
};