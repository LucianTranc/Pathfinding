#include "Grid.h"


Grid::Grid(int x, int y, int w, int h, int grid_x, int grid_y) : gridArray(grid_x, vector<int> (grid_y, 0))
{
    position = vec2(x, y);
    size = vec2(w, h);
    gridSize = vec2(grid_x, grid_y);

    addColour("white", vec4(255, 255, 255, 255));
    addColour("black", vec4(0, 0, 0, 0));
    addColour("red", vec4(255, 0, 0, 0));
    addColour("green", vec4(0, 255, 0, 0));
    addColour("yellow", vec4(255, 255, 0, 0));
    addColour("cyan", vec4(0, 255, 255, 0));
    addColour("pink", vec4(255, 0, 255, 0));
    addColour("blue", vec4(0, 0, 255, 0));

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

void Grid::addColour(string name, vec4 rgba)
{
    Colour colour = {name, rgba};
    colourMap.insert({(int)colourMap.size(), colour});
}

void Grid::draw()
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
            
            Colour colour = colourMap[gridArray[i][j]];

            SDL_SetRenderDrawColor( Game::renderer, colour.rgba.r, colour.rgba.g, colour.rgba.b, colour.rgba.a);
            
            SDL_RenderFillRect(Game::renderer, &r );

        }
    }


}