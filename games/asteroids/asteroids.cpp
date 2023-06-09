// TODO Make missile class, missile vector, FireMissile()

#include "asteroids.hpp"
#include "../../app/app.hpp"
#include "../../shapes/aaRectangle.hpp"
#include "../../shapes/line2D.hpp"
#include <cmath>

Asteroids::Asteroids() : mScreenWidth(0), mScreenHeight(0), mCountDown(3), mStartGame(false), mTimeElapsed(0), mLives(0)
{
}

void Asteroids::Init(GameController &controller)
{
    mFont = App::Singleton().GetFont();

    mScreenWidth = App::Singleton().Width();
    mScreenHeight = App::Singleton().Height();

    mTitleScreen.Init(mGameName);
    mHighScores.Init(App::Singleton().GetBasePath() + mHighScoresFile);

    mSpriteSheet.Load(mSpriteSheetFile);
    mGameState = ASTEROIDS_TITLE;
    CreateControls(controller);

    mShip.Init(App::Singleton().GetBasePath() + mAnimationsFile, mSpriteSheet);
    Rock rock;
    mRocks.push_back(rock);
    mRocks.back().Init(LARGE_ROCK, mSpriteSheet);
    mAnimationPlayer.Init(mAnimationsFile);
}

void Asteroids::Draw(Screen &screen)
{
    if (mGameState == ASTEROIDS_TITLE)
    {
        mTitleScreen.Draw(screen);
    }
    else if (mGameState == ASTEROIDS_SCORE)
    {
        mHighScores.Draw(screen);
    }
    else if (mGameState == ASTEROIDS_COUNTDOWN)
    {
        DrawTransform transform;
        transform.magnification = 3.0f;
        Color color = Color::White();
        color.SetAlpha(255 - (mTimeElapsed * COUNTDOWN_FADE));
        screen.Draw(mFont, to_string(mCountDown), mFont.GetDrawPosition(to_string(mCountDown), AARectangle(Vec2D::Zero, mScreenWidth, mScreenHeight / 4), BFXA_CENTER, BFYA_CENTER), color, transform);
        mShip.Draw(screen);
        if (mRocks.size() > 0)
        {
            for (auto &rock : mRocks)
            {
                rock.Draw(screen);
            }
        }
    }
    else if (mGameState == ASTEROIDS_PLAYING)
    {
        if (mShowShip)
        {
            mShip.Draw(screen);
        }
        if (mShowExplosion)
        {
            Vec2D shipLoc(mShip.GetCircle().GetCenterPoint().GetX() - mShip.GetCircle().GetRadius(), mShip.GetCircle().GetCenterPoint().GetY() - mShip.GetCircle().GetRadius());
            AnimationFrame frame = mAnimationPlayer.GetCurrentAnimationFrame();
            screen.Draw(mSpriteSheet, frame.frame, shipLoc);
        }

        if (mRocks.size() > 0)
        {
            for (auto &rock : mRocks)
            {
                rock.Draw(screen);
            }
        }
    }
    else if (mGameState == ASTEROIDS_GAMEOVER)
    {
    }
}

void Asteroids::Update(uint32_t dt)
{

    if (mGameState == ASTEROIDS_TITLE)
    {
        bool showTitle = mTitleScreen.Update(dt);
        if (!showTitle)
        {
            SwapState();
        }
    }
    else if (mGameState == ASTEROIDS_COUNTDOWN)
    {
        if (mTimeElapsed > 60)
        {
            --mCountDown;
            mTimeElapsed = 0;
            if (mCountDown == 0)
            {
                SwapState();
            }
        }
        else
        {
            ++mTimeElapsed;
        }
    }
    else if (mGameState == ASTEROIDS_PLAYING)
    {
        if (mShowShip)
        {
            mShip.Update(dt);
        }

        if (mRocks.size() > 0)
        {
            for (auto &rock : mRocks)
            {
                rock.Update(dt);
                if (rock.CheckForCollision(mShip.GetCircle()))
                {
                    LostLife();
                }
            }
        }
        if (mShowExplosion)
        {
            mAnimationPlayer.Update(dt);
            if (mAnimationPlayer.IsFinishedPlaying())
            {
                mShowExplosion = false;
                if (mLives <= 0)
                {
                    SwapState();
                }
                else
                {
                    ResetCurrentGame();
                }
            }
        }
    }
    else if (mGameState == ASTEROIDS_GAMEOVER)
    {
        SwapState();
    }
    else if (mGameState == ASTEROIDS_SCORE)
    {

        bool showScore = mHighScores.Update(dt);
        if (!showScore)
        {
            mGameState = ASTEROIDS_TITLE;
        }
    }
}

std::string Asteroids::GetName()
{
    return mGameName;
}

void Asteroids::CreateControls(GameController &controller)
{
    controller.ClearAll();
    ButtonAction upAction;
    upAction.Key = GameController::Up();
    upAction.Action = [this](uint32_t dt, InputState state)
    {
        if (GameController::IsPressed(state))
        {
            if (mGameState == ASTEROIDS_PLAYING)
            {
                mShip.MoveForward();
            }
        }
        else
        {
            if (mGameState == ASTEROIDS_PLAYING)
            {
                mShip.SetShowThrusters(false);
            }
        }
    };

    ButtonAction downAction;
    downAction.Key = GameController::Down();
    downAction.Action = [this](uint32_t dt, InputState state)
    {
        if (GameController::IsPressed(state))
        {
        }
    };

    ButtonAction leftAction;
    leftAction.Key = GameController::Left();
    leftAction.Action = [this](uint32_t dt, InputState state)
    {
        if (GameController::IsPressed(state))
        {
            if (mGameState == ASTEROIDS_PLAYING)
            {
                mShip.RotateLeft();
            }
        }
    };

    ButtonAction rightAction;
    rightAction.Key = GameController::Right();
    rightAction.Action = [this](uint32_t dt, InputState state)
    {
        if (GameController::IsPressed(state))
        {
            if (mGameState == ASTEROIDS_PLAYING)
            {
                mShip.RotateRight();
            }
        }
    };

    ButtonAction actionAction;
    actionAction.Key = GameController::Action();
    actionAction.Action = [this](uint32_t dt, InputState state)
    {
        if (GameController::IsPressed(state))
        {
            if (mGameState == ASTEROIDS_TITLE)
            {
                mStartGame = true;
                mCountDown = 3;
                mLives = 3;
                SwapState();
            }
            else if (mGameState == ASTEROIDS_PLAYING)
            {
                // if(mMissiles.size() == 3){
                //     return;
                // }
                // else{
                //     FireMissile();
                // }
            }
        }
    };

    ButtonAction cancelAction;
    cancelAction.Key = GameController::Cancel();
    cancelAction.Action = [this](uint32_t dt, InputState state)
    {
        if (GameController::IsPressed(state))
        {
            if (mGameState == ASTEROIDS_TITLE || (mGameState == ASTEROIDS_SCORE && mHighScores.GetScoreState() == SCORE_SHOW))
            {
                App::Singleton().PopScene();
            }
        }
    };

    controller.AddInputActionForKey(upAction);
    controller.AddInputActionForKey(downAction);
    controller.AddInputActionForKey(leftAction);
    controller.AddInputActionForKey(rightAction);
    controller.AddInputActionForKey(actionAction);
    controller.AddInputActionForKey(cancelAction);
}

void Asteroids::SwapState()
{
    if (mGameState == ASTEROIDS_TITLE && mStartGame)
    {
        mGameState = ASTEROIDS_COUNTDOWN;
    }
    else
    {
        if (mGameState == ASTEROIDS_TITLE)
        {
            mGameState = ASTEROIDS_SCORE;
        }
        else if (mGameState == ASTEROIDS_COUNTDOWN)
        {
            mGameState = ASTEROIDS_PLAYING;
            mShowShip = true;
            mShowExplosion = false;
        }
        else if (mGameState == ASTEROIDS_PLAYING)
        {
            mGameState = ASTEROIDS_GAMEOVER;
        }
        else if (mGameState == ASTEROIDS_GAMEOVER)
        {
            mGameState = ASTEROIDS_SCORE;
        }
        else if (mGameState == ASTEROIDS_SCORE)
        {
            mGameState = ASTEROIDS_TITLE;
        }
    }
}

void Asteroids::ResetCurrentGame()
{
    mShip.ResetPosition();
    mShowShip = true;
    mGameState = ASTEROIDS_COUNTDOWN;
    mCountDown = 3;
    mTimeElapsed = 0;
    mExplosionShown = false;
}

void Asteroids::LostLife()
{
    if (!mShowExplosion)
    {

        mShowShip = false;
        mShowExplosion = true;
        --mLives;
        mAnimationPlayer.Play("explosion", false);
    }
}