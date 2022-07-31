#include "AStar.h"


AStar::AStar(Grid * g, bool h)
{
    grid = g;
    heuristic = h;
}

void AStar::initializeAlgorithm(int x, int y, bool animate)
{
    active = true;
    pathFound = false;

    if (!grid->getCellWithState(&startCell, Grid::start))
    {
        std::cout<<"No start cell found"<<std::endl;
    }

    if (!grid->getCellWithState(&endCell, Grid::end))
    {
        std::cout<<"No end cell found"<<std::endl;
    }

    AStarCell tempCell = {0, 0, 0, startCell, startCell};

    open.push_back(createNewCell(&tempCell, {0,0}));

}

void AStar::update()
{
    if (active && !pathFound && open.size() > 0)
    {
        int lowestCostIndex;

        AStarCell current = findCellInOpenWithLowestCost(&lowestCostIndex);

        closed.insert(closed.end(), open.at(lowestCostIndex));
        open.erase(open.begin() + lowestCostIndex);

        if (current.position == endCell)
        {
            grid->setPositionToState(current.position.x, current.position.y, Grid::end);
            retrace(current);
            pathFound = true;
            active = false;
            return;
        }
        if (grid->isStateAtPosition(current.position.x, current.position.y, Grid::open))
        {
            grid->setPositionToState(current.position.x, current.position.y, Grid::closed);
        }

        vector<vec2> directions = { { 1,  1}, { 1,  0},
                                    { 1, -1}, { 0, -1},
                                    {-1, -1}, {-1,  0},
                                    {-1,  1}, { 0,  1}};

        for (int i = 0; i < directions.size(); i++)
        {
            vec2 neighbourPosition = {current.position.x + directions[i].x, current.position.y + directions[i].y};

            if (grid->isStateAtPosition(neighbourPosition.x, neighbourPosition.y, Grid::blocked) ||
                isInClosedList(neighbourPosition) ||
                (neighbourPosition.x < 0 || neighbourPosition.y < 0) ||
                (neighbourPosition.x > 79 || neighbourPosition.y > 59))
            {
                continue;
            }

            int neighbourIndexInOpenList;

            if (!isInOpenList(neighbourPosition, &neighbourIndexInOpenList))
            {
                open.push_back(createNewCell(&current, directions[i]));
                grid->setPositionToState(neighbourPosition.x, neighbourPosition.y, Grid::open);
            }
            else
            {
                int stepValue = 14;
                if (directions[i].x == 0 || directions[i].y == 0) stepValue = 10;

                int newPath = current.g_lengthOfPath + stepValue;

                if (newPath < open[neighbourIndexInOpenList].g_lengthOfPath)
                {
                    open[neighbourIndexInOpenList].g_lengthOfPath = newPath;
                    open[neighbourIndexInOpenList].parentCellPosition = current.position;
                    open[neighbourIndexInOpenList].f_totalCost = open[neighbourIndexInOpenList].g_lengthOfPath + open[neighbourIndexInOpenList].h_distanceToEnd;
                }
            }        
        }
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
            if (index != nullptr) *index = i;
            return true;
        }
    }
    return false;
}

AStar::AStarCell AStar::findCellInOpenWithLowestCost(int * outIndex)
{
    int lowestCost = INT_MAX;
    int lowestLength = INT_MAX;
    int lowestCostIndex = 0;
    for (int i = 0; i < open.size(); i++)
    {
        if (open[i].f_totalCost < lowestCost)
        {
            lowestLength = open[i].g_lengthOfPath;
            lowestCost = open[i].f_totalCost;
            lowestCostIndex = i;
        }
        else if (open[i].f_totalCost == lowestCost && open[i].g_lengthOfPath <= lowestLength)
        {
            lowestLength = open[i].g_lengthOfPath;
            lowestCost = open[i].f_totalCost;
            lowestCostIndex = i;
        }
    }
    *outIndex = lowestCostIndex;

    AStarCell returnValue = open.at(lowestCostIndex);

    return returnValue;
}


int AStar::manhattenDistanceBetweenCells(vec2 start, vec2 end)
{

    int x = abs(end.x - start.x);
    int y = abs(end.y - start.y);
    return (x + y) * 10;
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
        std::cout<<"Closed List is empty"<<std::endl;
    }
}

void AStar::printAStarCell(AStarCell cell)
{
    std::cout<<"position: {"<<cell.position.x<<", "<<cell.position.y<<"}, total distance: "<<cell.f_totalCost<<", distance from start: "<<cell.g_lengthOfPath<<", distance to end: "<<cell.h_distanceToEnd<<", parent position: {"<<cell.parentCellPosition.x<<", "<<cell.parentCellPosition.y<<"}"<<std::endl;
}

AStar::AStarCell AStar::createNewCell(AStarCell * parent, vec2 direction)
{

    AStarCell newCell;

    newCell.position = {parent->position.x + direction.x, parent->position.y + direction.y};

    if (heuristic)
    {
        newCell.h_distanceToEnd = manhattenDistanceBetweenCells(newCell.position, endCell);
    }
    else
    {
        newCell.h_distanceToEnd = 0;
    }
    
    newCell.parentCellPosition = parent->position;

    int stepCost = 14;
    if (direction.x == 0 && direction.y == 0) stepCost = 0;
    else if (direction.x == 0 || direction.y == 0) stepCost = 10;

    newCell.g_lengthOfPath = parent->g_lengthOfPath + stepCost;
    newCell.f_totalCost = newCell.h_distanceToEnd + newCell.g_lengthOfPath;

    return newCell;

}

void AStar::retrace(AStarCell cell)
{
    vec2 parentCellPosition = cell.parentCellPosition;
    AStarCell currentCell = cell;

    while (parentCellPosition != startCell)
    {
        for (int i = 0; i < closed.size(); i++)
        {
            if (closed[i].position == parentCellPosition)
            {
                grid->setPositionToState(parentCellPosition.x, parentCellPosition.y, Grid::path);
                currentCell = closed[i];
                break;
            }
        }
        parentCellPosition = currentCell.parentCellPosition;
    }
}
