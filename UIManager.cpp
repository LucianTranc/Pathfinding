#include "UIManager.h"

int UIManager::mousex = 0;
int UIManager::mousey = 0;
bool UIManager::mousedown = false;
const Uint8* UIManager::keystates = nullptr;
SDL_Event UIManager::event;
Button * UIManager::pressedButton = nullptr;
TTF_Font * UIManager::ariel = nullptr;



UIManager::UIManager()
{
    ariel = TTF_OpenFont("assets/arial.ttf", 100);
    if (ariel == nullptr)
    {
        std::cout<<"ariel not found"<<std::endl;
    }
}

UIManager::~UIManager()
{
    for (auto & b : buttons)
    {
    	delete b;
	}

    for (auto & l : labels)
    {
    	delete l;
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
        case SDL_MOUSEBUTTONDOWN:
            mousedown = true;
            break;
        case SDL_MOUSEBUTTONUP:
            mousedown = false;
            break;
        default:
            break;
    }

    SDL_GetMouseState(&mousex, &mousey);
    SDL_PumpEvents();
    keystates = SDL_GetKeyboardState(NULL); 
    SDL_GetMouseState(&mousex, &mousey);
}

void UIManager::addButton(int x, int y, int w, int h, vec4 c_1, vec4 c_2, vec4 c_3,  GridManager * gridManager, void (GridManager::*onClick)())
{
    buttons.push_back(new Button(x, y, w, h, 2, c_1, c_2, c_3, gridManager, onClick));
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


