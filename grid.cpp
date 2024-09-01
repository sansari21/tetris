#include "grid.h"
#include <iostream>
#include <vector>
#include "colors.h"
using namespace std;

Grid::Grid()
{
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    Initialize();
    colors = GetCellColors();
}

void Grid::Initialize()
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
            grid[i][j] = 0;
    }
}

bool Grid::IsCellOutside(int row, int col)
{
    if (row >= 0 && row < numRows && col >= 0 && col < numCols)
        return false;

    return true;
}

bool Grid::IsCellEmpty(int row, int col)
{
    if (grid[row][col] == 0)
        return true;
    return false;
}

void Grid::Print()
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
            cout << grid[i][j] << " ";
        cout << "\n";
    }
}

void Grid::Draw()
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            int cellValue = grid[i][j];
            DrawRectangle(j * cellSize+11, i * cellSize+11, cellSize-1, cellSize-1, colors[cellValue]);
        }
    }
}

int Grid::clearFullRows()
{
    int completed = 0;
    for (int row = numRows - 1; row >= 0; row--)
    {
        if (IsRowFull(row))
        {
            clearRow(row);
            completed++;
        }
        else if (completed > 0)
        {
            moveRowDown(row, completed);
        }
    }
    return completed;
}

bool Grid::IsRowFull(int row)
{

    for (int col = 0; col < numCols; col++)
    {
        if (grid[row][col] == 0)
            return false;
    }
    return true;
}

void Grid::clearRow(int row)
{
    for (int col = 0; col < numCols; col++)
    {
        grid[row][col] = 0;
    }
}

void Grid::moveRowDown(int row, int numRows)
{
    for (int col = 0; col < numCols; col++)
    {
        grid[row + numRows][col] = grid[row][col];
        grid[row][col] = 0;
    }
}
