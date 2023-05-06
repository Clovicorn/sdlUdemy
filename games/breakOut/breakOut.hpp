#pragma once

#include <iostream>
#include <vector>
#include "../../app/app.hpp"
#include "../game.hpp"
#include "../../input/gameController.hpp"

#include "ball.hpp"
#include "levelBoundary.hpp"
#include "paddle.hpp"
#include "breakOutLevel.hpp"
#include "highScores.hpp"

enum BreakOutGameStates
{
    IN_PLAY = 0,
    IN_SERVE,
    IN_GAME,
    IN_GAME_OVER
};

class BreakOut : public Game
{
public:
    virtual void Init(GameController &controller) override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw(Screen &screen) override;
    virtual std::string GetName() override;

private:
    void ResetGame();
    void SetToServe();
    void NextLevel();
    void CreateControls(GameController &controller);
    BreakOutLevel &GetCurrentLevel() { return mLevels[mCurrentLevel]; }
    Ball mBall;
    HighScores mHighScores;
    std::string mHighScoreFile = "assets/HighScores.txt";
    const float INITIAL_BALL_SPEED = 100.0f;
    LevelBoundary mLevelBoundary;
    Paddle mPaddle;
    int cleanup = 0;
    int mScreenWidth = 0;
    int mScreenHeight = 0;
    size_t mCurrentLevel = 0;
    std::vector<BreakOutLevel> mLevels;
    BreakOutGameStates mGameState;
    int mLives = 3;
};