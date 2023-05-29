#ifndef TETRIS_H
#define TETRIS_H

#include <vector>

#include "../game.hpp"
#include "../highScores.hpp"
#include "../titleScreen.hpp"
#include "../../shapes/aaRectangle.hpp"
#include "../../graphics/bitmapFont.hpp"
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
    TETRIS_TITLE = 0,
    TETRIS_PLAYING,
    TETRIS_GAME_OVER,
    TETRIS_SCORES,
    TETRIS_PAUSED,
};

class GameController;
class Screen;

class Tetris : public Game
{
public:
    ~Tetris();
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

    std::string mHighScoresFile = "assets/Tetris/TetrisHighScores.txt";
    std::string mGameName = "Tetris";
    TitleScreen mTitleScreen;

    int mTimeElapsed = 0;
    int mSpeed = 0;
    int mSpeedUp = 60;
    int mMaxSpeed = 7;
    int mTotalRowsCompleted = 0;
    int mAmountBetweenUpdate = 0;
    unsigned int mBlockSize = 12;
    std::vector<TetrisBlock> mBlocks;
    int rows[20] = {0};
    int columns[10] = {0};

    TetrisGameState mGameState = TETRIS_TITLE;
    TetrisShape mNextShape;
    TetrisShape mCurrentShape;
    AARectangle mBorder;
    AARectangle mNextShapeBorder;
    BitmapFont mFont;
    HighScores mHighScores;
};

#endif /* TETRIS_H */