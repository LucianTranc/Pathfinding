#include "Pathfinder.h"

Pathfinder::Pathfinder(Grid * g)
{
    grid = g;
}

void Pathfinder::findPath(int x, int y, bool animate)
{
    addNeighboursToQueue({{x, y},{-x, -y}});

    if (animate)
    {
        pathFound = false;
    }
    else
    {
        while (deque.size() > 0)
        {
            pair<pair<int,int>,pair<int,int>> popped = deque.front();
            deque.pop_front();           

            addNeighboursToQueue(popped);

            searched.push_back(popped);

        }
        pathFound = true;
    }
}

void Pathfinder::update()
{
    if (!pathFound)
    {
        for (int i = 0; i < 5; i++)
        {
            if (deque.size() > 0)
            {
                pair<pair<int,int>,pair<int,int>> popped = deque.front();
                deque.pop_front();

                grid->setPositionToState(popped.first.first, popped.first.second, Grid::searched);

                if (endFound(popped))
                {
                    pathFound = true;
                    retracePath(popped);
                }

                addNeighboursToQueue(popped);

                searched.push_back(popped);
            }
            else
            {
                pathFound = true;
            }
        }
    }
}

void Pathfinder::retracePath(pair<pair<int,int>,pair<int,int>> cell)
{
    grid->setPositionToState(cell.first.first, cell.first.second, Grid::path);

    pair<int,int> nextCell = cell.second;
    pair<pair<int,int>,pair<int,int>> next = cell;

    while (!(nextCell.first == 0 && nextCell.second == 0))
    {
        for (int i = 0; i < searched.size(); i++)
        {
            if (searched[i].first == nextCell)
            {
                next = searched[i];
                grid->setPositionToState(next.first.first, next.first.second, Grid::path);

                break;
            }
        }

        nextCell = next.second;
        std::cout<<"nextCell: {"<<nextCell.first<<", "<<nextCell.second<<"}"<<std::endl;

    }
    

}

bool Pathfinder::endFound(pair<pair<int,int>,pair<int,int>> cell)
{
    if (grid->isStateAtPosition(cell.first.first - 1, cell.first.second, Grid::end))
    {
        return true;
    }
    if (grid->isStateAtPosition(cell.first.first, cell.first.second - 1, Grid::end))
    {
        return true;
    }
    if (grid->isStateAtPosition(cell.first.first + 1, cell.first.second, Grid::end))
    {
        return true;
    }
    if (grid->isStateAtPosition(cell.first.first, cell.first.second + 1, Grid::end))
    {
        return true;
    }
    return false;
}


void Pathfinder::addNeighboursToQueue(pair<pair<int,int>,pair<int,int>> cell)
{

    if (grid->isStateAtPosition(cell.first.first - 1, cell.first.second, Grid::passage) && grid->setPositionToState(cell.first.first - 1, cell.first.second, Grid::inQueue))
    {
        deque.push_back({{cell.first.first - 1, cell.first.second}, cell.first});
    }

    if (grid->isStateAtPosition(cell.first.first, cell.first.second - 1, Grid::passage) && grid->setPositionToState(cell.first.first, cell.first.second - 1, Grid::inQueue))
    {
        deque.push_back({{cell.first.first, cell.first.second - 1}, cell.first});
    }

    if (grid->isStateAtPosition(cell.first.first + 1, cell.first.second, Grid::passage) && grid->setPositionToState(cell.first.first + 1, cell.first.second, Grid::inQueue))
    {
        deque.push_back({{cell.first.first + 1, cell.first.second}, cell.first});
    }

    if (grid->isStateAtPosition(cell.first.first, cell.first.second + 1, Grid::passage) && grid->setPositionToState(cell.first.first, cell.first.second + 1, Grid::inQueue))
    {
        deque.push_back({{cell.first.first, cell.first.second + 1}, cell.first});
    }

    //std::cout<<"frontier cells: "<<frontierCells.size()<<std::endl;

}
