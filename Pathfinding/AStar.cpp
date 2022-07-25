#include "AStar.h"


AStar::AStar(Grid * g)
{
    grid = g;
}

void AStar::initializeAlgorithm(int x, int y, bool animate)
{

    std::cout<<"A*"<<std::endl;

    distanceBetweenCells({1,1}, {2,2});


    //active = true;

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
    //open.push_back({0, distanceBetweenCells(startCell, endCell), startCell, startCell});

    AStarCell tempCell = {0, 0, 0, startCell, startCell};

    open.push_back(createNewCell(&tempCell, {0,0}));

    std::cout<<"Added start cell to list"<<std::endl;

    printOpenList();

    // loop <- using a for loop temprarily 
    for (int i = 0; i < 10000000; i++)
    {
        std::cout<<"_______________________________________"<<std::endl;
        std::cout<<"A* iteration: "<<i<<std::endl;
        std::cout<<"_______________________________________"<<std::endl;

        int lowestCostIndex;

        AStarCell current = findCellInOpenWithLowestCost(&lowestCostIndex);

        std::cout<<"Cell with lowest cost: "<<std::endl;
        printAStarCell(current);

        open.erase(open.begin() + lowestCostIndex);

        closed.push_back(current);

        grid->setPositionToState(current.position.x, current.position.y, Grid::closed);

        if (current.position == endCell)
        {
            std::cout<<"End Found Using A*"<<std::endl;
            //retracePath(current);
            return;
        }

        vector<vec2> directions = { { 1,  1}, { 1,  0},
                                    { 1, -1}, { 0, -1},
                                    {-1, -1}, {-1,  0},
                                    {-1,  1}, { 0,  1}};

        for (int i = 0; i < directions.size(); i++)
        {
            vec2 neighbourPosition = {current.position.x + directions[i].x, current.position.y + directions[i].y};

            std::cout<<"checking neighbour: {"<<neighbourPosition.x<<", "<<neighbourPosition.y<<"}"<<std::endl;

            if (grid->isStateAtPosition(neighbourPosition.x, neighbourPosition.y, Grid::blocked) ||
                isInClosedList(neighbourPosition))
            {
                std::cout<<"neighbour is blocked or is already closed"<<std::endl;
                continue;
            }

            int neighbourIndexInOpenList;

            if (!isInOpenList(neighbourPosition, &neighbourIndexInOpenList))
            {

                std::cout<<"neighbour isn't in the open list yet, adding to open"<<std::endl;
                open.push_back(createNewCell(&current, directions[i]));
                printOpenList();
            }
            else
            {
                std::cout<<"neighbour is already in the open list, recalculating"<<std::endl;

                int stepValue = 14;
                if (directions[i].x == 0 || directions[i].y == 0) stepValue = 10;

                int newPath = current.g_lengthOfPath + stepValue;

                if (newPath < open[neighbourIndexInOpenList].g_lengthOfPath)
                {
                    open[neighbourIndexInOpenList].g_lengthOfPath = newPath;
                    open[neighbourIndexInOpenList].parentCellPosition = current.position;
                    open[neighbourIndexInOpenList].f_totalCost = open[neighbourIndexInOpenList].g_lengthOfPath + open[neighbourIndexInOpenList].h_distanceToEnd;
                }
                printOpenList();
            }        
        }
    }
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

AStar::AStarCell AStar::findCellInOpenWithLowestCost(int * outIndex)
{
    int lowestCost = INT_MAX;
    int lowestDistanceToEnd = INT_MAX;
    int lowestCostIndex = 0;
    for (int i = 0; i < open.size(); i++)
    {
        if (open[i].f_totalCost <= lowestCost && open[i].h_distanceToEnd < lowestDistanceToEnd)
        {
            lowestDistanceToEnd = open[i].h_distanceToEnd;
            lowestCost = open[i].f_totalCost;
            lowestCostIndex = i;
        }
    }
    *outIndex = lowestCostIndex;
    return open.at(lowestCostIndex);
}

AStar::AStarCell AStar::findCellInOpen(vec2 position)
{
    for (int i = 0; i < open.size(); i++)
    {
        if (open[i].position == position)
        {
            return open.at(i);
        }
    }
    // unhandled excpetion here
}

int AStar::distanceBetweenCells(vec2 start, vec2 end)
{

    int x = abs(end.x - start.x);
    int y = abs(end.y - start.y);
    
    /*
    std::cout<<"distanceBetweenCells():"<<std::endl;
    std::cout<<"start: {"<<start.x<<", "<<start.y<<"}, end: {"<<end.x<<", "<<end.y<<"}"<<std::endl;
    std::cout<<"x: "<<x<<", y: "<<y<<std::endl;
    std::cout<<"x^2: "<<(x*x)<<std::endl;
    std::cout<<"y^2: "<<(y*y)<<std::endl;
    std::cout<<"x^2 + y^2: "<<(x*x + y*y)<<std::endl;
    std::cout<<"sqrt(x^2 + y^2)*10 as int: "<<(int)(sqrt(x*x + y*y)*10)<<std::endl;
    */

    return sqrt(x*x + y*y)*10;
}



void AStar::printOpenList()
{
    std::cout<<"Open Cells:"<<std::endl;
    for (int i = 0; i < open.size(); i++)
    {
        AStarCell cell = open[i];
        printAStarCell(cell);
    }
    if (open.size() == 0)
    {
        std::cout<<"Open List is empty"<<std::endl;
    }
}

void AStar::printClosedList()
{
    std::cout<<"Closed Cells:"<<std::endl;
    for (int i = 0; i < closed.size(); i++)
    {
        AStarCell cell = closed[i];
        printAStarCell(cell);
    }
    if (closed.size() == 0)
    {
        std::cout<<"Open List is empty"<<std::endl;
    }
}

void AStar::printAStarCell(AStarCell cell)
{
    std::cout<<"position: {"<<cell.position.x<<", "<<cell.position.y<<"}, total distance: "<<cell.f_totalCost<<", distance from start: "<<cell.g_lengthOfPath<<", distance to end: "<<cell.h_distanceToEnd<<", parent position: {"<<cell.parentCellPosition.x<<", "<<cell.parentCellPosition.y<<"}"<<std::endl;
}
AStar::AStarCell AStar::createNewCell(AStarCell * parent, vec2 direction)
{

    //std::cout<<"creating new cell"<<std::endl;

    AStarCell newCell;

    newCell.position = {parent->position.x + direction.x, parent->position.y + direction.y};
    newCell.h_distanceToEnd = distanceBetweenCells(newCell.position, endCell);
    newCell.parentCellPosition = parent->position;

    int stepCost = 14;
    if (direction.x == 0 && direction.y == 0) stepCost = 0;
    else if (direction.x == 0 || direction.y == 0) stepCost = 10;

    //std::cout<<"stepCost: "<<stepCost<<std::endl;

    newCell.g_lengthOfPath = parent->g_lengthOfPath + stepCost;
    newCell.f_totalCost = newCell.h_distanceToEnd + newCell.g_lengthOfPath;

    return newCell;

}

void AStar::retracePath(AStarCell cell)
{
    std::cout<<"Retracing steps"<<std::endl;
    grid->setPositionToState(cell.position.x, cell.position.y, Grid::path);

    vec2 parentCellPosition = cell.parentCellPosition;
    AStarCell currentCell = cell;

    while (parentCellPosition != startCell)
    {
        for (int i = 0; i < closed.size(); i++)
        {
            if (closed[i].position == parentCellPosition)
            {
                std::cout<<"{"<<parentCellPosition.x<<", "<<parentCellPosition.y<<"}"<<std::endl;
                grid->setPositionToState(parentCellPosition.x, parentCellPosition.y, Grid::path);
                currentCell = closed[i];
                break;
            }
        }
        parentCellPosition = currentCell.parentCellPosition;
    }
}
