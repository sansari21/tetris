#pragma once
#include "grid.h"
#include "blocks.cpp"
class Game
{
public:
    Game();
    void Draw();
    void handleInput();
    void MoveBlockDown();
    int score;
    ~Game();
    bool gameOver;
    bool isPaused;
    Music music;

private:
    vector<Block> blocks;
    void rotateBlock();
    void lockBlock();
    bool blockFits();
    void Reset();
    void updateScore(int linescleared, int moveDown);

    Block GetRandomBlock();
    vector<Block> GetAllBlocks();
    void MoveBlockLeft();
    void MoveBlockRight();
    bool IsBlockOutside();
    Grid grid;
    Block currentBlock;
    Block nextBlock;
    Sound rotateSound;
    Sound clearSound;
};