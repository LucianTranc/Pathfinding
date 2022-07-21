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
    if (mazeGenerator != nullptr)
    {
        mazeGenerator->update();

        if (mazeGenerator->generationComplete)
        {
            free(mazeGenerator);
            mazeGenerator = nullptr;
            std::cout<<"Maze Generator Freed"<<std::endl;
            setStartAndEndCells();
            std::cout<<"Set start and end cells"<<std::endl;
            pathfinder->findPath(0, 0, true);
            std::cout<<"envoked find path"<<std::endl;

        }
    }
    else if (pathfinder != nullptr)
    {
        pathfinder->update();
        if (pathfinder->pathFound)
        {
            std::cout<<"path found"<<std::endl;

            free(pathfinder);
            pathfinder = nullptr;
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

void GridManager::generateMaze()
{

}


