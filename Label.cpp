#include "Label.h"

Label::Label(int x, int y, int w, int h, string t, SDL_Color c)
{
    position = vec2(x, y);
    size = vec2(w, h);
    text = t;
    colour = c;

    rect.x = position.x;
    rect.y = position.y;
    rect.w = size.x;
    rect.h = size.y;

    textSurface = TTF_RenderText_Solid(UIManager::ariel, text.c_str(), colour); 
}

void Label::draw(SDL_Renderer * renderer)
{    
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
