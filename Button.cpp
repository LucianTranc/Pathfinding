#include "Button.h"

Button::Button(int x, int y, int w, int h, int b, vec4 c_1, vec4 c_2, vec4 c_3, GridManager * gridManager, void (GridManager::*f)())
{
    position = vec2(x, y);
    size = vec2(w, h);
    defaultColour = c_1;
    activeColour = c_1;
    hoverColour = c_2;
    pushedColour = c_3;

    rect.x = position.x;
    rect.y = position.y;
    rect.w = size.x;
    rect.h = size.y;

    boarderWidth = b;

    boarderRect.x = position.x - boarderWidth;
    boarderRect.y = position.y - boarderWidth;
    boarderRect.w = size.x + (2 * boarderWidth);
    boarderRect.h = size.y + (2 * boarderWidth);
    
    gridManagerReference = gridManager;

    onClick = f;
}

void Button::draw(SDL_Renderer * renderer)
{    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderFillRect(renderer, &boarderRect );

    SDL_SetRenderDrawColor(renderer, activeColour.r, activeColour.g, activeColour.b, activeColour.a);
    SDL_RenderFillRect(renderer, &rect );
}

void Button::update()
{
    if (UIManager::pressedButton == this)
    {
        if (UIManager::event.type == SDL_MOUSEBUTTONUP)
        {
            (gridManagerReference->*onClick)();

            UIManager::pressedButton = nullptr;

            if (UIManager::mousex > position.x && UIManager::mousex < (position.x + size.x) &&
                UIManager::mousey > position.y && UIManager::mousey < (position.y + size.y))
            {
                activeColour = hoverColour;
                state = hover;
            }
            else
            {
                activeColour = defaultColour;
                state = normal;
            }
        }
    }
    else if (UIManager::pressedButton == nullptr)
    {
        if (UIManager::mousex > position.x && UIManager::mousex < (position.x + size.x) &&
            UIManager::mousey > position.y && UIManager::mousey < (position.y + size.y))
        {

            if (state == normal)
            {
                activeColour = hoverColour;
                state = hover;
            }

            if (UIManager::event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (state != pressed)
                {
                    activeColour = pushedColour;
                    state = pressed;
                    UIManager::pressedButton = this;
                }
            }
        }
        else
        {
            if (state == hover)
            {
                activeColour = defaultColour;
                state = normal;
            }
        }
    }


/*
    if (UIManager::keystates[SDL_SCANCODE_SPACE])
    {   
        for (auto& b : balls)
        {
            if (abs(UIManager::mousex - b->position.x) < b->radius && abs(UIManager::mousey - b->position.y) < b->radius)
            {
                selectedDragBall = b;
                selectedDragBall->velocity.x = 0;
                selectedDragBall->velocity.y = 0;
                break;
            }
        }
    }

    //if the player presses the spacebar while the mouse is over a ball then mark it is a the drag ball
    if (UIManager::event.type == SDL_KEYDOWN && UIManager::event.key.keysym.sym == SDLK_SPACE) {   
        for (auto& b : balls) {
            if (abs(mousex - b->position.x) < b->radius && abs(mousey - b->position.y) < b->radius) {
                selectedDragBall = b;
                break;
            }
        }
    }

    //if the player releases the spacebar then deselect the ball
    if (UIManager::event.type == SDL_KEYUP && UIManager::event.key.keysym.sym == SDLK_SPACE) {
        selectedDragBall = nullptr; 
    }

    //if the mousebutton is pressed while no balls are moving then mark the cueball as the ball to hit
    if ((UIManager::event.type == SDL_MOUSEBUTTONDOWN && selectedHitBall == nullptr) && !BallsAreMoving()) {
        mousedown = true;
        selectedHitBall = cueBall;
    }
    else if (mousedown && selectedHitBall) {
        //if the mouse is being held down then add to the power of the hit and drag the cue backwards
        hitPower += 4;
        cue->ballSeparation = hitPower/2 + 5;

    }
    //if the mousebutton is released then reset the cue, add the the balls velocity and reset variables
    if (UIManager::event.type == SDL_MOUSEBUTTONUP) {
        cue->ballSeparation = 5;
        if (selectedHitBall) {
            selectedHitBall->velocity.x = -glm::sin(mouseangle) * hitPower / 50;
            selectedHitBall->velocity.y = -glm::cos(mouseangle) * hitPower / 50;
            hitPower = 0;
        }
        selectedHitBall = nullptr;
        mousedown = false;
    }
    */
}