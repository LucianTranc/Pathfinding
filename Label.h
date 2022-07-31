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

using std::string;
using std::vector;
using std::pair;

#define GLM_ENABLE_EXPERIMENTAL
using glm::vec2;
using glm::vec3;
using glm::vec4;

class Label {

public:

    Label(int x, int y, int w, int h, string t, SDL_Color c);
    void draw(SDL_Renderer * renderer);
    void update();

private:

    vec2 position;
    vec2 size;
    SDL_Color colour;
    string text;

    SDL_Rect rect;
    SDL_Surface * textSurface;

};