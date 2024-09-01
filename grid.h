#pragma once
#include <vector>
#include <raylib.h>
using namespace std;
class Grid
{
public:
    Grid();
    int grid[20][10];
    void Initialize();
    bool IsCellOutside(int row,int col);
    bool IsCellEmpty(int row,int col);
    void Print();
    void Draw();
    int clearFullRows();

private:
    vector<Color> colors;
    bool IsRowFull(int row);
    int numRows;
    void clearRow(int row);
    void moveRowDown(int row,int numRows);
    int numCols;
    int cellSize;
};
