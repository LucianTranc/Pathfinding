#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "glm/glm.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "UIManager.h"
#include "Game.h"

using std::string;
using std::vector;
using std::pair;

#define GLM_ENABLE_EXPERIMENTAL
using glm::vec2;
using glm::vec3;
using glm::vec4;

class GridManager;

class Button {

public:

    enum State {normal, hover, pressed};

    Button(int x, int y, int w, int h, int b, vec4 c_1, vec4 c_2, vec4 c_3, GridManager * gridManager, void (GridManager::*f)());
    void draw(SDL_Renderer * renderer);
    void update();

private:

    vec2 position;
    vec2 size;

    vec4 defaultColour;
    vec4 hoverColour;
    vec4 pushedColour;
    vec4 activeColour;

    int boarderWidth;

    SDL_Rect rect;
    SDL_Rect boarderRect;

    State state = normal;

    GridManager * gridManagerReference;

    void (GridManager::*onClick)();

};