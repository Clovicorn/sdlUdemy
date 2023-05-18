#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <iostream>
#include <vector>

#include "../game.hpp"
#include "ball.hpp"
#include "levelBoundary.hpp"
#include "paddle.hpp"
#include "breakOutLevel.hpp"
#include "highScores.hpp"
#include "../../graphics/bitmapFont.hpp"

class GameController;
class App;

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

    std::string mHighScoreFile = "assets/HighScores.txt";

    const float INITIAL_BALL_SPEED = 100.0f;
    int mCleanup = 0;
    size_t mCurrentLevel = 0;
    int mLives = 3;
    int score = 0;
    int mScreenWidth = 0;
    int mScreenHeight = 0;

    Ball mBall;
    BitmapFont mFont;
    BreakOutGameStates mGameState;
    BreakOutLevel &GetCurrentLevel() { return mLevels[mCurrentLevel]; }
    HighScores mHighScores;
    LevelBoundary mLevelBoundary;
    std::vector<BreakOutLevel> mLevels;
    Paddle mPaddle;
};

#endif /* BREAKOUT_H */