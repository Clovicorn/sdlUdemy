#pragma once

#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "../../app/app.hpp"
#include "../game.hpp"
#include "../../input/gameController.hpp"
#include "../../shapes/aaRectangle.hpp"
#include "tetrisBlock.hpp"
#include "tetrisShape.hpp"

enum BoardSides
{
    LEFT_BORDER = 0,
    RIGHT_BORDER,
    BOTTOM_BORDER
};

enum TetrisGameState
{
    TETRIS_NOT_STARTED = 0,
    TETRIS_PLAYING,
    TETRIS_GAME_OVER,
    TETRIS_PAUSED,
};

class Tetris : public Game
{
public:
    virtual void Init(GameController &controller) override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw(Screen &screen) override;
    virtual std::string GetName() override;

    inline void SetScreenWidth(int width) { mScreenWidth = width; }
    inline void SetScreenHeight(int height) { mScreenHeight = height; }

private:
    void CreateControls(GameController &controller);
    void ResetCurrentShape();
    void UpdateBoard(AARectangle &rect, int row, int column);
    bool CheckForCollision(BoardSides side);
    void DeleteCompleteRows();
    void UpdateScore(int amount);
    int mScore = 0;
    int mSpeed = 60;
    int mAmountBetweenUpdate = 0;
    unsigned int mBlockSize = 12;
    unsigned int mPlayingHeightSquares = 20;
    unsigned int mPlayingWidthSquares = 10;
    unsigned int mScreenWidth;
    unsigned int mScreenHeight;
    const int BORDER_WIDTH = 10;
    std::vector<TetrisBlock> mBlocks;
    TetrisBlock mBoard[20][10];
    TetrisGameState mGameState = TETRIS_NOT_STARTED;
    TetrisShape mCurrentShape;
    AARectangle mBorder;
};