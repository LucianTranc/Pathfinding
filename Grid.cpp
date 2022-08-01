#include "Grid.h"


Grid::Grid(int x, int y, int w, int h, int grid_x, int grid_y, int boarder) : gridArray(grid_x, vector<int> (grid_y, 0))
{
    position = vec2(x, y);
    size = vec2(w, h);
    gridSize = vec2(grid_x, grid_y);
    boarderWidth = boarder;

    boarderRect.x = position.x - boarderWidth;
    boarderRect.y = position.y - boarderWidth;
    boarderRect.w = size.x + (2 * boarderWidth);
    boarderRect.h = size.y + (2 * boarderWidth);

    srand(time(0));

}

void Grid::setGridToState(State state)
{
    for (int i = 0; i < gridArray.size(); i++)
    {
        for (int j = 0; j < gridArray[i].size(); j++)
        {
            gridArray[i][j] = state;
        }
    }
}

void Grid::resetPassages()
{
    for (int i = 0; i < gridArray.size(); i++)
    {
        for (int j = 0; j < gridArray[i].size(); j++)
        {
            if (gridArray[i][j] != blocked && gridArray[i][j] != start && gridArray[i][j] != end)
            {
                gridArray[i][j] = passage;
            }
        }
    }
}

void Grid::randomizeGrid()
{
    std::cout<<"randomizing grid"<<std::endl;
    std::cout<<"gridArray.size(): "<<gridArray.size()<<std::endl;

    for (int i = 0; i < gridArray.size(); i++)
    {
        for (int j = 0; j < gridArray[i].size(); j++)
        {
            gridArray[i][j] = rand() % colourMap.size();
        }
    }
    std::cout<<"finished randomizing grid"<<std::endl;

}

void Grid::printGrid()
{
    std::cout<<"printing grid"<<std::endl;

    for (int i = 0; i < gridArray.size(); i++)
    {
        for (int j = 0; j < gridArray[i].size(); j++)
        {
            std::cout<<gridArray[i][j];
        }
        std::cout<<std::endl;
    }
    std::cout<<"finished printing grid"<<std::endl;

}

std::pair<int, int> Grid::setRandomPositionToState(State state)
{
    int x = rand() % (int)(gridSize.x);
    int y = rand() % (int)(gridSize.y);
    gridArray[x][y] = state;
    return {x, y};
}


bool Grid::setPositionToState(int x, int y, State state)
{
    if (state == start || state == end)
    {
        for (int i = 0; i < gridArray.size(); i++)
        {
            for (int j = 0; j < gridArray[i].size(); j++)
            {
                if (gridArray[i][j] == state)
                {
                    gridArray[i][j] = passage;
                }
            }
        }
    }

    if ((x >= 0 && x < gridSize.x) && (y >= 0 && y < gridSize.y))
    {
        gridArray[x][y] = state;
        return true;
    }
    return false;
}

bool Grid::isStateAtPosition(int x, int y, State state)
{
    if ((x >= 0 && x < gridSize.x) && (y >= 0 && y < gridSize.y))
    {
        if (gridArray[x][y] == state)
        {
            return true;
        }
    }
    return false;
}


vec2 Grid::screenToGridPosition(int x, int y)
{
    vec2 gridPosition;
    vec2 cellSize = vec2(size.x/gridSize.x, size.y/gridSize.y);

    if ((x >= position.x && x <= (position.x + size.x)) &&
        (y >= position.y && y <= (position.y + size.y)))
    {
        gridPosition = {(int)((x - position.x)/cellSize.x), (int)((y - position.y)/cellSize.y)};
    }
    else
    {
        gridPosition = {-1, -1};
    }

    return gridPosition;
}


void Grid::draw(SDL_Renderer * renderer)
{

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            
    SDL_RenderFillRect(renderer, &boarderRect );

    vec2 cellSize = vec2(size.x/gridSize.x, size.y/gridSize.y);

    //std::cout<<"draw"<<std::endl;
    for (int i = 0; i < gridArray.size(); i++)
    {
        for (int j = 0; j < gridArray[i].size(); j++)
        {
            SDL_Rect r;
            r.x = position.x + i * cellSize.x;
            r.y = position.y + j * cellSize.y;
            r.w = cellSize.x;
            r.h = cellSize.y;

            //std::cout<<"x: "<<r.x<<", y: "<<r.y<<", w: "<<r.w<<", h: "<<r.h<<std::endl;
            
            vec4 colour = colourMap[(State)gridArray[i][j]];

            SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
            
            SDL_RenderFillRect(renderer, &r );

        }
    }
}

bool Grid::getCellWithState(vec2 * outCell, Grid::State state)
{
    for (int i = 0; i < gridSize.x; i++)
    {
        for (int j = 0; j < gridSize.y; j++)
        {
            if (gridArray[i][j] == state)
            {
                *outCell = {i, j};
                return true;
            }
        }
    }
    return false;
}