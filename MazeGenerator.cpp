#include "MazeGenerator.h"

MazeGenerator::MazeGenerator(Grid * g)
{
    grid = g;
}

void MazeGenerator::generateMaze(int x, int y, bool animate)
{
    active = true;

    grid->setGridToState(Grid::blocked);

    // set the starting point to a passage and compute its frontier cells
    if (grid->setPositionToState(x, y, Grid::passage))
    {
        computeFrontierCells({x, y});
    }

    // continue with maze generation, either animated or not
    if (animate)
    {
        generationComplete = false;
    }
    else
    {
        while (frontierCells.size() > 0)
        {
            vec2 poppedFrontierCell;

            if (popRandomFrontierCell(&poppedFrontierCell))
            {
                computeFrontierCells(poppedFrontierCell);
                makePassage(poppedFrontierCell);
            }
        }
        generationComplete = true;
        active = false;
    }
}

void MazeGenerator::update()
{
    if (active && !generationComplete)
    {
        for (int i = 0; i < 5; i++)
        {
            if (frontierCells.size() > 0)
            {
                vec2 poppedFrontierCell;

                if (popRandomFrontierCell(&poppedFrontierCell))
                {
                    computeFrontierCells(poppedFrontierCell);
                    makePassage(poppedFrontierCell);
                }
            }
            else
            {
                generationComplete = true;
                active = false;
            }
        }
    }
}

void MazeGenerator::makePassage(vec2 frontierCell)
{
    vector<vec2> availableDirections;

    vector<vec2> directions = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

    for (int i = 0; i < directions.size(); i++)
    {
        if (grid->isStateAtPosition(frontierCell.x + (directions[i].x * 2), frontierCell.y + (directions[i].y * 2), Grid::passage))
        {
            availableDirections.emplace_back(directions[i]);
        }
    }

    if (availableDirections.size() > 0)
    {
        vec2 directionChosen = availableDirections[rand() % availableDirections.size()];

        grid->setPositionToState(frontierCell.x + directionChosen.x, frontierCell.y + directionChosen.y, Grid::passage);
        grid->setPositionToState(frontierCell.x + (directionChosen.x * 2), frontierCell.y + (directionChosen.y * 2), Grid::passage);
    }

    grid->setPositionToState(frontierCell.x, frontierCell.y, Grid::passage);

}

bool MazeGenerator::popRandomFrontierCell(vec2 * outCell)
{
    if (frontierCells.size() > 0)
    {
        int randomIndex = rand() % frontierCells.size();
        *outCell = frontierCells[randomIndex];
        frontierCells.erase(frontierCells.begin() + randomIndex);
        return true;
    }
    else
    {
        return false;
    }
    
}

void MazeGenerator::computeFrontierCells(vec2 cell)
{
    vector<vec2> directions = {{-2, 0}, {0, -2}, {2, 0}, {0, 2}};

    for (int i = 0; i < directions.size(); i++)
    {
        if (grid->isStateAtPosition(cell.x + directions[i].x, cell.y + directions[i].y, Grid::blocked) &&
            grid->setPositionToState(cell.x + directions[i].x, cell.y + directions[i].y, Grid::frontier))
        {
            frontierCells.emplace_back(cell.x + directions[i].x, cell.y + directions[i].y);
        }
    }
}
