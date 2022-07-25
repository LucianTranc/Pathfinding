#include "GridManager.h"

GridManager::GridManager()
{
    grid = new Grid(0, 0, 800, 600, 80, 60);
    mazeGenerator = new MazeGenerator(grid);
    pathfindingManager = new PathfindingManager(grid);
}

void GridManager::start()
{
    //mazeGenerator->generateMaze(0, 59, true);
    grid->setPositionToState(1, 1, Grid::start);
    grid->setPositionToState(14, 15, Grid::end);
    pair<vec2, vec2> startAndEnd = {{1,1},{14,15}};
    pathfindingManager->findPath(startAndEnd.first.x, startAndEnd.first.y, PathfindingManager::aStar, true);

}

void GridManager::update()
{
    if (mazeGenerator->active)
    {
        //std::cout<<"maze active"<<std::endl;

        mazeGenerator->update();

        if (mazeGenerator->generationComplete)
        {
            pair<vec2, vec2> startAndEnd = setStartAndEndCells();
            pathfindingManager->findPath(startAndEnd.first.x, startAndEnd.first.y, PathfindingManager::aStar, true);
        }
    }
    else
    {
        //std::cout<<"maze inactive"<<std::endl;

    }
    
    if (pathfindingManager->active)
    {
        //std::cout<<"path active"<<std::endl;

        pathfindingManager->update();

        if (pathfindingManager->pathFound)
        {
            // return a list containing the path
        }
    }
    else
    {
        //std::cout<<"path inactive"<<std::endl;
    }
    
}

std::pair<vec2, vec2> GridManager::setStartAndEndCells()
{
    std::pair<vec2, vec2> startAndEndCells;
    bool foundSuitableStart = false;
    while (!foundSuitableStart)
    {
        int x = rand() % 20;
        int y = rand() % 15;
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
        int x = rand() % 20 + 59;
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


