#include "PathfindingManager.h"

PathfindingManager::PathfindingManager(Grid * g)
{
    grid = g;
}

void PathfindingManager::findPath(int x, int y, Algorithm algorithmName, bool animate)
{
    algorithm = algorithmName;

    switch (algorithm)
    {
        case BFS:
        {
            active = true;

            activeAlgorithm = new BreadthFirstSearch(grid);

            activeAlgorithm->initializeAlgorithm(x, y, animate);
            
            break;
        }
        case DFS:
        {
            active = true;

            activeAlgorithm = new DepthFirstSearch(grid);

            activeAlgorithm->initializeAlgorithm(x, y, animate);
            
            break;
        }
        case aStar:
        {
            active = true;

            activeAlgorithm = new AStar(grid);

            activeAlgorithm->initializeAlgorithm(x, y, animate);
            
            break;
        }
        default:
        {
            std::cout<<"Algorithm not supported!"<<std::endl;
            return;
        }
    }

}

void PathfindingManager::update()
{
    if (activeAlgorithm->isActive() && !activeAlgorithm->isPathFound())
    {
        activeAlgorithm->update();
    }
    else if (!activeAlgorithm->isActive())
    {
        active = false;
    }
}