#include "UIManager.h"

int UIManager::mousex = 0;
int UIManager::mousey = 0;
const Uint8* UIManager::keystates = nullptr;
SDL_Event UIManager::event;
Button * UIManager::pressedButton = nullptr;
TTF_Font * UIManager::ariel = nullptr;



UIManager::UIManager()
{
    ariel = TTF_OpenFont("assets/arial.ttf", 60);
    if (ariel == nullptr)
    {
        std::cout<<"ariel not found"<<std::endl;
    }
}

void UIManager::start()
{
}

void UIManager::update()
{
    getInputState();
    for (auto & b : buttons)
    {
    	b->update();
	}
}

void UIManager::getInputState()
{
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }

    SDL_GetMouseState(&mousex, &mousey);
    SDL_PumpEvents();
    keystates = SDL_GetKeyboardState(NULL); 
    SDL_GetMouseState(&mousex, &mousey);
}

void UIManager::addButton(int x, int y, int w, int h, vec4 c_1, vec4 c_2, vec4 c_3, Game * game, void (Game::*onClick)())
{
    buttons.push_back(new Button(x, y, w, h, c_1, c_2, c_3, game, onClick));
}

void UIManager::addLabel(int x, int y, int w, int h, string t, SDL_Color c)
{
    labels.push_back(new Label(x, y, w, h, t, c));
}

void UIManager::draw(SDL_Renderer * renderer)
{
    for (auto & b : buttons)
    {
    	b->draw(renderer);
	}

    for (auto & l : labels)
    {
    	l->draw(renderer);
	}

}


