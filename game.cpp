#include "game.h"
#include <random>
Game::Game()
{

    gameOver = false;
    grid = Grid();
    score = 0;
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    InitAudioDevice();
    music = LoadMusicStream("Sounds/music.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound = LoadSound("Sounds/clear.mp3");
}

Game::~Game()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
};
Block Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}
vector<Block> Game::GetAllBlocks()
{
    return {LBlock(), JBlock(), IBlock(), OBlock(), SBlock(), ZBlock(), TBlock()};
}

void Game::handleInput()
{

    int keyPressed = GetKeyPressed();
    if (keyPressed == KEY_P)
    {
        isPaused = !isPaused;
        return;
    }
    if (gameOver && keyPressed != 0)
    {
        gameOver = false;
        Reset();
    }
    if (isPaused)
    {
        return;
    }
    switch (keyPressed)
    {
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    case KEY_RIGHT:
        MoveBlockRight();
        break;
    case KEY_DOWN:
        MoveBlockDown();
        updateScore(0, 1);
        break;
    case KEY_UP:
        rotateBlock();
        break;
    }
}

void Game::MoveBlockLeft()
{
    if (!gameOver)
    {
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || blockFits() == false)
        {
            currentBlock.Move(0, 1);
        }
    }
}
void Game::MoveBlockRight()
{
    if (!gameOver)
    {
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || blockFits() == false)
        {
            currentBlock.Move(0, -1);
        }
    }
}
void Game::MoveBlockDown()
{
    if (!gameOver)
    {
        currentBlock.Move(1, 0);
        if (IsBlockOutside() || blockFits() == false)
        {

            currentBlock.Move(-1, 0);
            lockBlock();
        }
    }
}
bool Game::IsBlockOutside()
{
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position tile : tiles)
    {
        if (grid.IsCellOutside(tile.row, tile.col))
            return true;
    }
    return false;
}
void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11, 11);
    switch (nextBlock.id)
    {
    case 3:
        nextBlock.Draw(255, 290);
        break;
    case 4:
        nextBlock.Draw(255, 280);
        break;
    default:
        nextBlock.Draw(270, 270);
        break;
    }
}

void Game::rotateBlock()
{
    if (!gameOver)
    {
        currentBlock.rotate();
        if (IsBlockOutside() || blockFits() == false)
        {
            currentBlock.undoRotation();
        }
        else
        {
            PlaySound(rotateSound);
        }
    }
}

void Game::lockBlock()
{

    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position tile : tiles)
    {
        grid.grid[tile.row][tile.col] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if (blockFits() == false)
    {
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.clearFullRows();
    if (rowsCleared > 0)
    {
        PlaySound(clearSound);
        updateScore(rowsCleared, 0);
    }
}

bool Game::blockFits()
{

    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position tile : tiles)
    {
        if (grid.IsCellEmpty(tile.row, tile.col) == false)
        {
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::updateScore(int linesCleared, int moveDown)
{
    switch (linesCleared)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    default:
        break;
    }
    score += moveDown;
}
