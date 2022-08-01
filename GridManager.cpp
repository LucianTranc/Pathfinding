#include "GridManager.h"

GridManager::GridManager()
{
    grid = new Grid(15, 15, 570, 570, 57, 57, 5);
    mazeGenerator = new MazeGenerator(grid);
    pathfindingManager = new PathfindingManager(grid);
    drawingController = new DrawingController(grid);
}

GridManager::~GridManager()
{
    delete grid;
    delete mazeGenerator;
    delete pathfindingManager;
    delete drawingController;
}

void GridManager::start()
{

}

void GridManager::generateMaze()
{
    mazeGenerator->generateMaze(0, 0, true);
}

void GridManager::triggerAStar()
{
    vec2 startCell, endCell;

    if (grid->getCellWithState(&startCell, Grid::start) && grid->getCellWithState(&endCell, Grid::end))
    {
        pathfindingManager->findPath(startCell.x, startCell.y , PathfindingManager::aStar, true);
    }
}

void GridManager::triggerDijkstra()
{
    vec2 startCell, endCell;

    if (grid->getCellWithState(&startCell, Grid::start) && grid->getCellWithState(&endCell, Grid::end))
    {
        pathfindingManager->findPath(startCell.x, startCell.y , PathfindingManager::Dijkstra, true);
    }
}

void GridManager::triggerDFS()
{
    vec2 startCell, endCell;

    if (grid->getCellWithState(&startCell, Grid::start) && grid->getCellWithState(&endCell, Grid::end))
    {
        pathfindingManager->findPath(startCell.x, startCell.y , PathfindingManager::DFS, true);
    }
}

void GridManager::triggerBFS()
{
    vec2 startCell, endCell;

    if (grid->getCellWithState(&startCell, Grid::start) && grid->getCellWithState(&endCell, Grid::end))
    {
        pathfindingManager->findPath(startCell.x, startCell.y , PathfindingManager::BFS, true);
    }
}

void GridManager::drawingOn()
{
    drawingController->active = true;
}

void GridManager::drawingOff()
{
    drawingController->active = false;
}

void GridManager::drawStateBlocked()
{
    drawingController->setDrawState(Grid::blocked);
}

void GridManager::drawStatePassage()
{
    drawingController->setDrawState(Grid::passage);
}

void GridManager::drawStateStart()
{
    drawingController->setDrawState(Grid::start);
}

void GridManager::drawStateEnd()
{
    drawingController->setDrawState(Grid::end);
}

void GridManager::update()
{
    if (mazeGenerator->active)
    {
        drawingController->active = false;

        mazeGenerator->update();

        if (!mazeGenerator->active)
        {
            drawingController->active = true;
        }
    }
    else
    {
        drawingController->active = true;
    }
    
    if (pathfindingManager->active)
    {
        drawingController->active = false;

        pathfindingManager->update();

        if (!pathfindingManager->active)
        {
            drawingController->active = true;
        }
    }
    else
    {
        drawingController->active = true;
    }

    if (drawingController->active)
    {
        drawingController->update();
    }
}

void GridManager::draw(SDL_Renderer * renderer)
{
    grid->draw(renderer);
}

void GridManager::resetPassages()
{
    pathfindingManager->active = false;
    grid->resetPassages();
}

void GridManager::clearGrid()
{
    pathfindingManager->active = false;
    grid->setGridToState(Grid::passage);
}
