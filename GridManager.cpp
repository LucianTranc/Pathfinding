#include "GridManager.h"

GridManager::GridManager()
{
    grid = new Grid(0, 0, 600, 600, 60, 60);
    mazeGenerator = new MazeGenerator(grid);
    pathfindingManager = new PathfindingManager(grid);
}

void GridManager::start()
{
    mazeGenerator->generateMaze(0, 0, false);
}

void GridManager::update()
{
    if (mazeGenerator->active)
    {
        mazeGenerator->update();

        if (mazeGenerator->generationComplete)
        {
            pair<vec2, vec2> startAndEnd = setStartAndEndCells();
            pathfindingManager->findPath(startAndEnd.first.x, startAndEnd.first.y, PathfindingManager::aStar, true);
        }
    }
    
    if (pathfindingManager->active)
    {
        pathfindingManager->update();
    }
}

std::pair<vec2, vec2> GridManager::setStartAndEndCells()
{
    std::pair<vec2, vec2> startAndEndCells;
    bool foundSuitableStart = false;
    while (!foundSuitableStart)
    {
        int x = 0;
        int y = 0;
        if (grid->isStateAtPosition(x, y, Grid::passage))
        {
            grid->setPositionToState(x, y, Grid::start);
            startAndEndCells.first = {x,y};
            foundSuitableStart = true;
        }
    }

    bool foundSuitableEnd = false;
    while (!foundSuitableEnd)
    {
        int x = rand() % 15 + 44;
        int y = rand() % 15 + 44;
        //int x = rand() % 20;
        //int y = rand() % 15;
        if (grid->isStateAtPosition(x, y, Grid::passage))
        {
            grid->setPositionToState(x, y, Grid::end);
            startAndEndCells.second = {x,y};
            foundSuitableEnd = true;
        }
    }
    return startAndEndCells;
}

void GridManager::draw(SDL_Renderer * renderer)
{
    grid->draw(renderer);
}


