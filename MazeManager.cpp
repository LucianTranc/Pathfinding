#include "MazeManager.h"

MazeManager::MazeManager()
{
    grid = new Grid(0, 0, 800, 600, 80, 60);;
}

void MazeManager::draw(SDL_Renderer * renderer)
{
    grid->draw(renderer);
}

void MazeManager::update()
{
    grid->setRandomPositionToColour(Grid::red);
}
