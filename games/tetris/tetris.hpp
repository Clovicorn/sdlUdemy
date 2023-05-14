#ifndef TETRIS_H
#define TETRIS_H

#include <vector>

#include "../game.hpp"
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

class GameController;
class Screen;

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
    void IsGameOver();
    void StartGame();
    void ResetCurrentShape();
    void UpdateBoard(unsigned int dt);
    bool CheckForCollision(BoardSides side);
    void DeleteCompleteRows();
    void UpdateScore(int amount);

    static const int STARTSPEED = 30;
    static const unsigned int mPlayingHeightSquares = 20;
    static const unsigned int mPlayingWidthSquares = 10;
    const int BORDER_WIDTH = 10;

    unsigned int mScreenWidth;
    unsigned int mScreenHeight;

    int mScore = 0;

    int mSpeed = 0;
    int mSpeedUp = 50;
    int mMaxSpeed = 2;
    int mTotalRowsCompleted = 0;
    int mAmountBetweenUpdate = 0;
    unsigned int mBlockSize = 12;
    std::vector<TetrisBlock> mBlocks;
    int rows[20] = {0};
    int columns[10] = {0};

    TetrisGameState mGameState = TETRIS_NOT_STARTED;
    TetrisShape mNextShape;
    TetrisShape mCurrentShape;
    AARectangle mBorder;
    AARectangle mNextShapeBorder;
};

#endif /* TETRIS_H */