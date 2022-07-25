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

class AStar : public PathfindingAlgorithm{

public:

    struct AStarCell {
        int distanceToStart;
        int distanceToEnd;
        vec2 position;
        vec2 parentCellPosition;
    } typedef AStarCell;

    AStar(Grid * g);
    void initializeAlgorithm(int x, int y, bool animate);
    void update();
    ~AStar() {};


private:

    int distanceBetweenCells(vec2 start, vec2 end);
    int findCellInOpenWithLowestCost();
    bool isInClosedList(vec2 cell);
    bool isInOpenList(vec2 cell, int * index = nullptr);

    vec2 startCell;
    vec2 endCell;
    vector<AStarCell> open;
    vector<AStarCell> closed;

};