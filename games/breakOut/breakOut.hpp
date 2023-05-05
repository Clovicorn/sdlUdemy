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

class BreakOut : public Game
{
public:
    virtual void Init(GameController &controller) override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw(Screen &screen) override;
    virtual std::string GetName() override;

private:
    void ResetGame();
    Ball mBall;
    LevelBoundary mLevelBoundary;
    Paddle mPaddle;
    int mScreenWidth = 0;
    int mScreenHeight = 0;
    size_t mCurrentLevel = 0;
    std::vector<BreakOutLevel> mLevels;
    BreakOutLevel &GetCurrentLevel() { return mLevels[mCurrentLevel]; }
};