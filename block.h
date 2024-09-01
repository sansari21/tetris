#pragma once
#include<vector>
#include<map>
#include "position.h"
#include "colors.h"
using namespace std;
class Block
{
public:
    Block();
    void rotate();
    void Draw(int offsetX,int offsetY);
    void Move(int rows,int cols);
    void undoRotation();
    vector<Position> GetCellPositions(); 
    int id;
    map<int,vector<Position>> cells;
private:
    int cellSize;
    int rotationState;
    vector< Color> colors;
    int rowOffset;
    int colOffset;
};