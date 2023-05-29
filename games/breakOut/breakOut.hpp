// TODO add titleScreen and update HighScore

#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <iostream>
#include <vector>

#include "../game.hpp"
#include "ball.hpp"
#include "levelBoundary.hpp"
#include "paddle.hpp"
#include "breakOutLevel.hpp"
#include "../highScores.hpp"
#include "../titleScreen.hpp"
#include "../../graphics/bitmapFont.hpp"

class GameController;
class App;

enum BreakOutGameStates
{
    IN_PLAY = 0,
    IN_SERVE,
    IN_GAME_TITLE,
    IN_GAME_OVER,
    IN_GAME_SCORES,
    IN_GAME_ADD_SCORE
};

class BreakOut : public Game
{
public:
    ~BreakOut();
    virtual void Init(GameController &controller) override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw(Screen &screen) override;
    virtual std::string GetName() override;

private:
    void ResetGame();
    void SetToServe();
    void GameOver();
    void NextLevel();
    void CreateControls(GameController &controller);

    std::string mHighScoreFile = "assets/BreakOut/BreakoutHighScores.txt";
    std::string mGameName = "Breakout";

    const float INITIAL_BALL_SPEED = 100.0f;
    int mCleanup = 0;
    size_t mCurrentLevel = 0;
    int mLives = 3;
    int mScreenWidth = 0;
    int mScreenHeight = 0;

    int mTimeElapsed = 0;
    int mShowMsgLoop = 0;
    bool mShowQuitMsg = false;
    bool mShowHighScore = false;
    bool mMsgPaused = false;

    Ball mBall;
    BitmapFont mFont;
    BreakOutGameStates mGameState;
    BreakOutLevel &GetCurrentLevel() { return mLevels[mCurrentLevel]; }
    HighScores mHighScores;
    TitleScreen mTitleScreen;
    LevelBoundary mLevelBoundary;
    std::vector<BreakOutLevel> mLevels;
    Paddle mPaddle;
};

#endif /* BREAKOUT_H */