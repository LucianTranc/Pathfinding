#include "MazeGenerator.h"

MazeGenerator::MazeGenerator(Grid * g)
{
    grid = g;
}

void MazeGenerator::generateMaze(int x, int y, bool animate)
{
    
    grid->setGridToState(Grid::blocked);

    if (grid->setPositionToState(x, y, Grid::passage))
    {
        computeFrontierCells({x, y});
    }

    if (animate)
    {
        generationComplete = false;
    }
    else
    {
        while (frontierCells.size() > 0)
        {
            std::pair<int,int> poppedFrontierCell;

            if (popRandomFrontierCell(&poppedFrontierCell))
            {
                computeFrontierCells(poppedFrontierCell);
                makePassage(poppedFrontierCell);
            }
        }
        generationComplete = true;
    }
}

void MazeGenerator::update()
{
    if (!generationComplete)
    {
        for (int i = 0; i < 5; i++)
        {
            if (frontierCells.size() > 0)
            {
                std::pair<int,int> poppedFrontierCell;

                if (popRandomFrontierCell(&poppedFrontierCell))
                {
                    computeFrontierCells(poppedFrontierCell);
                    makePassage(poppedFrontierCell);
                }
            }
            else
            {
                generationComplete = true;
            }
        }
    }
}

void MazeGenerator::makePassage(std::pair<int, int> frontierCell)
{
    vector<std::pair<int,int>> neighbourPassages;

    if (grid->isStateAtPosition(frontierCell.first - 2, frontierCell.second, Grid::passage))
    {
        neighbourPassages.emplace_back(-2, 0);
    }

    if (grid->isStateAtPosition(frontierCell.first + 2, frontierCell.second, Grid::passage))
    {
        neighbourPassages.emplace_back(2, 0);
    }

    if (grid->isStateAtPosition(frontierCell.first, frontierCell.second - 2, Grid::passage))
    {
        neighbourPassages.emplace_back(0, -2);
    }

    if (grid->isStateAtPosition(frontierCell.first, frontierCell.second + 2, Grid::passage))
    {
        neighbourPassages.emplace_back(0, 2);
    }

    if (neighbourPassages.size() > 0)
    {
        std::pair<int,int> neighbourChosen = neighbourPassages[rand() % neighbourPassages.size()];

        if (neighbourChosen.first == -2)
        {
            grid->setPositionToState(frontierCell.first - 1, frontierCell.second, Grid::passage);
            grid->setPositionToState(frontierCell.first - 2, frontierCell.second, Grid::passage);
        }
        else if (neighbourChosen.first == 2)
        {
            grid->setPositionToState(frontierCell.first + 1, frontierCell.second, Grid::passage);
            grid->setPositionToState(frontierCell.first + 2, frontierCell.second, Grid::passage);
        }
        else if (neighbourChosen.second == -2)
        {
            grid->setPositionToState(frontierCell.first, frontierCell.second - 1, Grid::passage);
            grid->setPositionToState(frontierCell.first, frontierCell.second - 2, Grid::passage);
        }
        else if (neighbourChosen.second == 2)
        {
            grid->setPositionToState(frontierCell.first, frontierCell.second + 1, Grid::passage);
            grid->setPositionToState(frontierCell.first, frontierCell.second + 2, Grid::passage);
        }
    }

    grid->setPositionToState(frontierCell.first, frontierCell.second, Grid::passage);


}

bool MazeGenerator::popRandomFrontierCell(std::pair<int, int> * outCell)
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

void MazeGenerator::computeFrontierCells(std::pair<int, int> cell)
{

    if (grid->isStateAtPosition(cell.first - 2, cell.second, Grid::blocked) && grid->setPositionToState(cell.first - 2, cell.second, Grid::frontier))
    {
        frontierCells.emplace_back(cell.first - 2, cell.second);
    }

    if (grid->isStateAtPosition(cell.first, cell.second - 2, Grid::blocked) && grid->setPositionToState(cell.first, cell.second - 2, Grid::frontier))
    {
        frontierCells.emplace_back(cell.first, cell.second - 2);
    }

    if (grid->isStateAtPosition(cell.first + 2, cell.second, Grid::blocked) && grid->setPositionToState(cell.first + 2, cell.second, Grid::frontier))
    {
        frontierCells.emplace_back(cell.first + 2, cell.second);
    }

    if (grid->isStateAtPosition(cell.first, cell.second + 2, Grid::blocked) && grid->setPositionToState(cell.first, cell.second + 2, Grid::frontier))
    {
        frontierCells.emplace_back(cell.first, cell.second + 2);
    }

    //std::cout<<"frontier cells: "<<frontierCells.size()<<std::endl;

}
