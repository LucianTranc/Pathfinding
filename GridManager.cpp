#include "GridManager.h"

GridManager::GridManager()
{
    grid = new Grid(0, 0, 800, 600, 80, 60);
    mazeGenerator = new MazeGenerator(grid);
    pathfinder = new Pathfinder(grid);
}

void GridManager::start()
{
    mazeGenerator->generateMaze(0, 0, true);
}

void GridManager::update()
{
    if (mazeGenerator->active)
    {
        mazeGenerator->update();

        if (mazeGenerator->generationComplete)
        {
            setStartAndEndCells();
            pathfinder->findPath(0, 0, true);
        }
    }
    
    if (pathfinder->active)
    {
        pathfinder->update();

        if (pathfinder->pathFound)
        {
            // return a list containing the path
        }
    }
    
}

void GridManager::setStartAndEndCells()
{
    grid->setPositionToState(0, 0, Grid::start);
    bool foundSuitableEnd = false;
    while (!foundSuitableEnd)
    {
        int x = rand() % 40 + 40;
        int y = rand() % 30 + 30;
        if (grid->isStateAtPosition(x, y, Grid::passage))
        {
            grid->setPositionToState(x, y, Grid::end);
            foundSuitableEnd = true;
            return;
        }
    }
}

void GridManager::draw(SDL_Renderer * renderer)
{
    grid->draw(renderer);
}


