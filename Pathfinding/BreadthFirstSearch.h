#pragma once
#include "PathfindingAlgorithm.h"


using std::string;
using std::vector;
using std::pair;
using std::deque;

#define GLM_ENABLE_EXPERIMENTAL
using glm::vec2;
using glm::vec4;

class Grid;
class PathfindingAlgorithm;

class BreadthFirstSearch : public PathfindingAlgorithm{

public:

    struct Cell {
        vec2 position;
        vec2 parentCellPosition;
    } typedef Cell;

    BreadthFirstSearch(Grid * g);
    void initializeAlgorithm(int x, int y, bool animate);
    void update();
    ~BreadthFirstSearch() {};


private:

    void addNeighboursToQueue(Cell cell);
    bool endFound(Cell cell);
    vector<vec2> retracePath(Cell cell);

    vector<Cell> searched;
    deque<Cell> deque;
    vec2 startCell;

};