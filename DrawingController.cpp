#include "DrawingController.h"

DrawingController::DrawingController(Grid * g)
{
    grid = g;
    active = true;
    state = Grid::blocked;
}

vec2 DrawingController::screenToGridPosition()
{
    return grid->screenToGridPosition(UIManager::mousex, UIManager::mousey);
}

void DrawingController::setDrawState(Grid::State s)
{
    state = s;
}

void DrawingController::update()
{
    if (active)
    {
        vec2 position = screenToGridPosition();
        if (position.x != -1 && UIManager::mousedown)
        {
            grid->setPositionToState(position.x, position.y, state);
        }
    }
}