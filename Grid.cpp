#include "Grid.h"


Grid::Grid(int x, int y, int w, int h, int grid_x, int grid_y) : gridArray(grid_x, vector<int> (grid_y, 0))
{
    position = vec2(x, y);
    size = vec2(w, h);
    gridSize = vec2(grid_x, grid_y);

    srand(time(0));

}

void Grid::zeroGrid()
{
    for (int i = 0; i < gridArray.size(); i++)
    {
        for (int j = 0; j < gridArray[i].size(); j++)
        {
            gridArray[i][j] = 0;
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

void Grid::setRandomPositionToColour(Colour colour)
{
    gridArray[rand() % (int)(gridSize.x)][rand() % (int)(gridSize.y)] = colour;
}


void Grid::draw(SDL_Renderer * renderer)
{
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
            
            vec4 colour = colourMap[(Colour)gridArray[i][j]];

            SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
            
            SDL_RenderFillRect(renderer, &r );

        }
    }


}