#include "BreadthFirstSearch.h"


BreadthFirstSearch::BreadthFirstSearch(Grid * g)
{
    grid = g;
}

void BreadthFirstSearch::initializeAlgorithm(int x, int y, bool animate)
{

    active = true;

    if (!grid->getCellWithState(&startCell, Grid::start))
    {
        std::cout<<"No start cell found"<<std::endl;
    }

    addNeighboursToQueue({{x, y},{x, y}});

    if (animate)
    {
        pathFound = false;
    }
    else
    {
        while (deque.size() > 0)
        {
            Cell popped = deque.front();
            deque.pop_front();           

            grid->setPositionToState(popped.position.x, popped.position.y, Grid::searched);

            if (endFound(popped))
            {
                retracePath(popped);
                pathFound = true;
                active = false;
                return;
            }

            addNeighboursToQueue(popped);

            searched.push_back(popped);

        }
        pathFound = false;
        active = false;
    }   
}

void BreadthFirstSearch::update()
{
    if (active && !pathFound)
    {
        if (deque.size() > 0)
        {
            Cell popped = deque.front();
            deque.pop_front();           

            grid->setPositionToState(popped.position.x, popped.position.y, Grid::searched);

            if (endFound(popped))
            {
                path = retracePath(popped);
                pathFound = true;
                return;
            }

            addNeighboursToQueue(popped);

            searched.push_back(popped);
        }
        else
        {
            pathFound = false;
            active = false;
        }   
    }
    if (active && pathFound)
    {
        if (path.size() == 0)
        {
            active = false;
            return;
        }
        vec2 nextPathStep = path[path.size()-1];
        path.pop_back();
        grid->setPositionToState(nextPathStep.x, nextPathStep.y, Grid::path);
    }
}

vector<vec2> BreadthFirstSearch::retracePath(Cell cell)
{
    //grid->setPositionToState(cell.position.x, cell.position.y, Grid::path);

    vec2 parentCellPosition = cell.parentCellPosition;
    Cell currentCell = cell;
    vector<vec2> path;

    path.push_back(currentCell.position);
    path.push_back(parentCellPosition);

    while (parentCellPosition != startCell)
    {
        for (int i = 0; i < searched.size(); i++)
        {
            if (searched[i].position == parentCellPosition)
            {
                //grid->setPositionToState(parentCellPosition.x, parentCellPosition.y, Grid::path);
                currentCell = searched[i];
                path.push_back(currentCell.parentCellPosition);
                break;
            }
        }
        parentCellPosition = currentCell.parentCellPosition;
    }

    path.pop_back();
    
    return path;
}

bool BreadthFirstSearch::endFound(Cell cell)
{
    vector<vec2> directions = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

    for (int i = 0; i < directions.size(); i++)
    {
        if (grid->isStateAtPosition(cell.position.x + directions[i].x, cell.position.y + directions[i].y, Grid::end))
        {
            return true;
        }
    }
    return false;
}


void BreadthFirstSearch::addNeighboursToQueue(Cell cell)
{
    vector<vec2> directions = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

    for (int i = 0; i < directions.size(); i++)
    {
        if (grid->isStateAtPosition(cell.position.x + directions[i].x, cell.position.y + directions[i].y, Grid::passage) &&
            grid->setPositionToState(cell.position.x + directions[i].x, cell.position.y + directions[i].y, Grid::inQueue))
        {
            deque.push_back({{cell.position.x + directions[i].x, cell.position.y + directions[i].y}, cell.position});
        }
    }
}
