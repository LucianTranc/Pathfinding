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

            activeAlgorithm = new AStar(grid, true);

            activeAlgorithm->initializeAlgorithm(x, y, animate);
            
            break;
        }
        case Dijkstra:
        {
            active = true;

            activeAlgorithm = new AStar(grid, false);

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
    if (activeAlgorithm->isActive())
    {
        activeAlgorithm->update();

        if (activeAlgorithm->isPathFound())
        {
        }
    }
    else if (!activeAlgorithm->isActive())
    {
        delete activeAlgorithm;
        active = false;
    }
}