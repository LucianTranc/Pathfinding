#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "glm/glm.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Button.h"
#include "Label.h"
#include "GridManager.h"

using std::string;
using std::vector;
using std::pair;

#define GLM_ENABLE_EXPERIMENTAL
using glm::vec2;
using glm::vec3;
using glm::vec4;

class Button;
class Label;
class GridManager;

class UIManager {

public:

    UIManager();
    ~UIManager();
    void start();
    void update();
    void draw(SDL_Renderer * renderer);
    void addButton(int x, int y, int w, int h, vec4 c_1, vec4 c_2, vec4 c_3, GridManager * gridManager, void (GridManager::*onClick)());
    void addLabel(int x, int y, int w, int h, string t, SDL_Color c);
	void getInputState();

    static int mousex;
	static int mousey;
    static bool mousedown;
	static const Uint8* keystates;
    static SDL_Event event;
    bool isRunning = true;
    static Button * pressedButton;
    static TTF_Font * ariel;

private:

    vector<Button*> buttons;
    vector<Label*> labels;

};