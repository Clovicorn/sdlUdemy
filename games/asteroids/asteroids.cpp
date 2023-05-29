// TODO Make missile class, missile vector, FireMissile()

#include "asteroids.hpp"
#include "../../app/app.hpp"

void Asteroids::Init(GameController &controller)
{
    mTitleScreen.Init(mGameName);
    mHighScores.Init(App::Singleton().GetBasePath() + mHighScoresFile);
    mSpriteSheet.Load(mSpriteSheetFile);
    mAnimationPlayer.Init(App::Singleton().GetBasePath() + mAnimationsFile);
    CreateControls(controller);
    std::cout << "end of Init" << std::endl;
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
    }
    else if (mGameState == ASTEROIDS_PLAYING)
    {
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
            mGameState = ASTEROIDS_SCORE;
        }
    }
    else if (mGameState == ASTEROIDS_COUNTDOWN)
    {
    }
    else if (mGameState == ASTEROIDS_PLAYING)
    {
    }
    else if (mGameState == ASTEROIDS_GAMEOVER)
    {
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
            if (mGameState == ASTEROIDS_TITLE)
            {
                App::Singleton().PopScene();
            }
        }
    };

    ButtonAction downAction;
    downAction.Key = GameController::Down();
    downAction.Action = [this](uint32_t dt, InputState state)
    {
        if (GameController::IsPressed(state))
        {
            if (mGameState == ASTEROIDS_TITLE)
            {
                App::Singleton().PopScene();
            }
        }
    };

    ButtonAction leftAction;
    leftAction.Key = GameController::Left();
    leftAction.Action = [this](uint32_t dt, InputState state)
    {
        if (GameController::IsPressed(state))
        {
            if (mGameState == ASTEROIDS_TITLE)
            {
                App::Singleton().PopScene();
            }
        }
    };

    ButtonAction rightAction;
    rightAction.Key = GameController::Right();
    rightAction.Action = [this](uint32_t dt, InputState state)
    {
        if (GameController::IsPressed(state))
        {
            if (mGameState == ASTEROIDS_TITLE)
            {
                App::Singleton().PopScene();
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
                mGameState = ASTEROIDS_COUNTDOWN;
                mCountDown = 3;
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
            if (mGameState == ASTEROIDS_TITLE)
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
