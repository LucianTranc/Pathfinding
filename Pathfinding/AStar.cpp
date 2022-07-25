#include "AStar.h"


AStar::AStar(Grid * g)
{
    grid = g;
}

void AStar::initializeAlgorithm(int x, int y, bool animate)
{

    std::cout<<"A*"<<std::endl;

    active = true;

    if (!grid->getCellWithState(&startCell, Grid::start))
    {
        std::cout<<"No start cell found"<<std::endl;
    }

    if (!grid->getCellWithState(&endCell, Grid::end))
    {
        std::cout<<"No end cell found"<<std::endl;
    }


    //  open -> the set of nodes to be evaluated
    //  closed -> the set of nodes already evaluated
    //  add the start node to open
    open.push_back({0, distanceBetweenCells(startCell, endCell), startCell, startCell});
    //
    //  loop <- using a for loop temprarily 
    for (int i = 0; i < 10; i++)
    {

    //      current = node in open with lowest cost
        int lowestCostIndex = findCellInOpenWithLowestCost();
        AStarCell current = open[lowestCostIndex];
    //      remove current from open
        open.erase(open.begin() + lowestCostIndex);
    //      add current to closed
        closed.push_back(current);
        grid->setPositionToState(current.position.x, current.position.y, Grid::closed);


    //      if current is the target node
    //          return

        if (current.position == endCell)
        {
            std::cout<<"End Found Using A*"<<std::endl;
            return;
        }

        vector<vec2> directions = { { 1,  1}, { 1,  0},
                                    { 1, -1}, { 0, -1},
                                    {-1, -1}, {-1,  0},
                                    {-1,  1}, { 0,  1}};

        for (int i = 0; i < directions.size(); i++)
        {
            vec2 currentNeighbour = {current.position.x + directions[i].x, current.position.y + directions[i].y};

            if (!grid->isStateAtPosition(currentNeighbour.x, currentNeighbour.y, Grid::passage) ||
                isInClosedList(currentNeighbour))
            {
                continue;
            }

            // If it isn’t on the open list, add it to the open list.
            // Make the current square the parent of this square.
            // Record the cost of the square.
            int indexInOpenList;

            if (!isInOpenList(currentNeighbour, &indexInOpenList))
            {
                open.push_back({distanceBetweenCells(currentNeighbour, startCell), distanceBetweenCells(currentNeighbour, endCell), currentNeighbour, current.position});
            }
            else
            {
            }

            // Child is already in openList
            // if child.position is in the openList's nodes positions
            //     if the child.g is higher than the openList node's g
            //         continue to beginning of for loop
            // Add the child to the openList
            // add the child to the openList

            // if the child is already in the open list then recalculate it's value

            
        }

    }

    //
        
    //
    //      for each neighbour of the current node
    //          if neighbour is not traversable or neighbour is in closed list
    //              skip to the next neighbour
    //
    //          if new path to neighbour is shorter or neighbour is not in open
    //              set cost of neighbour
    //              set parent of neighbour to current node
    //              if neighbour is not in open
    //                  add neighbour to open
}

void AStar::update()
{
    if (active && !pathFound)
    {
   
    }
}

bool AStar::isInClosedList(vec2 cell)
{
    for (int i = 0; i < closed.size(); i++)
    {
        if (closed[i].position == cell)
        {
            return true;
        }
    }
    return false;
}

bool AStar::isInOpenList(vec2 cell, int * index)
{
    for (int i = 0; i < open.size(); i++)
    {
        if (open[i].position == cell)
        {
            return true;
        }
    }
    return false;
}

int AStar::findCellInOpenWithLowestCost()
{
    int lowestCost = INT_MAX;
    int lowestCostIndex = 0;
    for (int i = 0; i < open.size(); i++)
    {
        int tempCost = open[i].distanceToEnd + open[i].distanceToStart;
        if (tempCost < lowestCost)
        {
            lowestCost = tempCost;
            lowestCostIndex = i;
        }
    }
    return lowestCostIndex;
}

int AStar::distanceBetweenCells(vec2 start, vec2 end)
{

    int x = abs(end.x - start.x);
    int y = abs(end.y - start.y);
    
    /*
    std::cout<<"start: {"<<start.x<<", "<<start.y<<"}, end: {"<<end.x<<", "<<end.y<<"}"<<std::endl;
    std::cout<<"x: "<<x<<", y: "<<y<<std::endl;
    std::cout<<"x^2: "<<(x*x)<<std::endl;
    std::cout<<"y^2: "<<(y*y)<<std::endl;
    std::cout<<"x^2 + y^2: "<<(x*x + y*y)<<std::endl;
    std::cout<<"sqrt(x^2 + y^2): "<<sqrt(x*x + y*y)<<std::endl;
    */

    return x*x + y*y;
}

