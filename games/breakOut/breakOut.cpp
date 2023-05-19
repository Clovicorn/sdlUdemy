#include "breakOut.hpp"

#include "../../app/app.hpp"
#include "../../input/gameController.hpp"

// TODO Setup GameOver to check if score is good enough to
// add to the high score list.  If so then run highScore system
// to allow adding intials to list.  Then show high score list

void BreakOut::Init(GameController &controller)
{

    mGameState = IN_GAME_TITLE;
    mScreenWidth = App::Singleton().Width();
    mScreenHeight = App::Singleton().Height();
    mFont = App::Singleton().GetFont();
    mBall.SetRadius(3.0f);
    mBall.ResetScore();
    mHighScores.Init(App::GetBasePath() + mHighScoreFile);
    controller.ClearAll();
    CreateControls(controller);
}

void BreakOut::Update(uint32_t dt)
{
    if (mGameState == IN_SERVE)
    {
        mBall.MoveTo(Vec2D(mPaddle.GetTopLeft().GetX() + (mPaddle.GetAARectangle().GetWidth() / 2), mPaddle.GetTopLeft().GetY() - (mBall.GetRadius() * 2)));
    }

    mBall.Update(dt);
    mPaddle.Update(dt, mBall);

    if (mGameState == IN_PLAY)
    {
        if (mPaddle.Bounce(mBall))
        {
            return;
        }
        BoundaryEdge edge;
        if (mLevelBoundary.HasCollided(mBall, edge))
        {
            if (edge.normal != UP_DIR)
            {
                mBall.Bounce(edge);
                return;
            }
            else
            {
                SetToServe();
                return;
            }
        }
    }
    if (mGameState == IN_SERVE || mGameState == IN_PLAY)
    {
        GetCurrentLevel().Update(dt, mBall);
        // This should update 3 times a Second!
        if (mCleanup == 20)
        {
            mCleanup = 0;
            if (GetCurrentLevel().IsLevelComplete())
            {
                NextLevel();
            }
        }
        else
        {
            mCleanup++;
        }
    }
    if (mGameState == IN_GAME_OVER)
    {
        if (mTimeElapsed == 120)
        {
            mGameState = IN_GAME_TITLE;
            mTimeElapsed = 0;
        }
        else
        {
            mTimeElapsed += 1;
        }
    }
    if (mGameState == IN_GAME_TITLE)
    {
        if (mTimeElapsed == 45 && !mMsgPaused)
        {
            mShowQuitMsg = !mShowQuitMsg;
            mMsgPaused = true;
            mTimeElapsed = 0;
            if (mShowMsgLoop == 4)
            {
                mGameState = IN_GAME_SCORES;
                mShowMsgLoop = 0;
            }
            else
            {
                mShowMsgLoop++;
            }
        }
        else if (mTimeElapsed == 20 && mMsgPaused)
        {
            mMsgPaused = false;
            mTimeElapsed = 0;
        }
        else
        {
            mTimeElapsed += 1;
        }
    }
    if (mGameState == IN_GAME_SCORES)
    {
        if (mHighScores.GetScoreState() == SCORE_SHOW)
        {
            if (mTimeElapsed == 300)
            {
                mGameState = IN_GAME_TITLE;
                mTimeElapsed = 0;
            }
            else
            {
                mTimeElapsed += 1;
            }
        }
        else
        {
        }
    }
}

void BreakOut::Draw(Screen &screen)
{
    if (mGameState == IN_PLAY || mGameState == IN_SERVE)
    {
        mPaddle.Draw(screen);

        std::string lives = "Lives " + to_string(mLives);
        Vec2D livesPos(5, mScreenHeight - 15);
        screen.Draw(mFont, lives, livesPos);

        std::string scoreText = "Score " + to_string(mBall.GetScore());
        Vec2D scorePos((mScreenWidth / 2) + 10, mScreenHeight - 15);
        screen.Draw(mFont, scoreText, scorePos);
        GetCurrentLevel().Draw(screen);
        mBall.Draw(screen);
        AARectangle boundary = mLevelBoundary.GetRectangle();
        screen.Draw(boundary, Color::White());
    }
    if (mGameState == IN_GAME_OVER)
    {
        AARectangle rect(Vec2D::Zero, mScreenWidth, mScreenHeight);
        std::string gameOver = "Game Over!";
        Vec2D pos(mFont.GetDrawPosition(gameOver, rect, BFXA_CENTER, BFYA_CENTER));
        screen.Draw(mFont, gameOver, pos);
    }
    if (mGameState == IN_GAME_TITLE)
    {
        AARectangle rect(Vec2D::Zero, mScreenWidth, mScreenHeight / 2);
        std::string breakoutText = "BreakOut!";
        Vec2D pos(mFont.GetDrawPosition(breakoutText, rect, BFXA_CENTER, BFYA_CENTER));
        screen.Draw(mFont, breakoutText, pos, Color::Red());
        if (!mMsgPaused)
        {
            AARectangle rect2(Vec2D(0, mScreenHeight / 2), mScreenWidth, mScreenHeight / 2);
            if (mShowQuitMsg)
            {
                std::string quitText = "Press Escape to quit.";
                Vec2D quitPos(mFont.GetDrawPosition(quitText, rect2, BFXA_CENTER, BFYA_CENTER));
                screen.Draw(mFont, quitText, quitPos);
            }
            else
            {
                std::string spaceText = "Press Space to play.";
                Vec2D playPos(mFont.GetDrawPosition(spaceText, rect2, BFXA_CENTER, BFYA_CENTER));
                screen.Draw(mFont, spaceText, playPos);
            }
        }
    }
    if (mGameState == IN_GAME_SCORES)
    {
        mHighScores.Draw(screen);
    }
}

std::string BreakOut::GetName()
{
    std::string name = "Break Out";
    return name;
}

/**
 * private methods below
 *
 */
void BreakOut::ResetGame()
{
    if (mGameState == IN_GAME_TITLE)
    {
        mGameState = IN_SERVE;
        mLives = 3;
        mBall.ResetScore();
        mCurrentLevel = 0;
        mLevels = BreakOutLevel::LoadLevelsFromFile(App::GetBasePath() + "assets/BreakoutLevels.txt", mScreenWidth, mScreenHeight);
        mLevelBoundary = {AARectangle(Vec2D::Zero, mScreenWidth, mScreenHeight - 20)};
        AARectangle rect(Vec2D(mScreenWidth / 2 - Paddle::PADDLE_WIDTH / 2, mScreenHeight - 4 * Paddle::PADDLE_HEIGHT), Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT);
        mLevels[mCurrentLevel].Init(mLevelBoundary.GetRectangle());
        mPaddle.Init(rect, mScreenWidth, mScreenHeight);
        mBall.MoveTo(Vec2D(mPaddle.GetTopLeft().GetX() + (mPaddle.GetAARectangle().GetWidth() / 2), mPaddle.GetTopLeft().GetY() - (mBall.GetRadius() * 2)));
    }
}

void BreakOut::SetToServe()
{
    --mLives;
    mBall.Stop();
    if (mLives > 0)
    {
        mGameState = IN_SERVE;
        mBall.MoveTo(Vec2D(mPaddle.GetTopLeft().GetX() + (mPaddle.GetAARectangle().GetWidth() / 2), mPaddle.GetTopLeft().GetY() - (mBall.GetRadius() * 2)));
    }
    else
    {
        GameOver();
    }
}

void BreakOut::GameOver()
{
    mGameState = IN_GAME_OVER;
    mPaddle.UnsetMovementDirection(PaddleDirection::LEFT_MOVE);
    mPaddle.UnsetMovementDirection(PaddleDirection::RIGHT_MOVE);
    bool madeHighScoreList = mHighScores.CheckScore(mBall.GetScore());
    if (madeHighScoreList)
    {
        // mHighScores.SetScoreState(SCORE_UPDATE);
        // mGameState = IN_GAME_SCORES;
    }
}

void BreakOut::NextLevel()
{
    mGameState = IN_SERVE;
    mCurrentLevel++;
    if (mCurrentLevel >= mLevels.size())
    {
        mCurrentLevel = 0;
    }
    mLevels[mCurrentLevel].Init(mLevelBoundary.GetRectangle());
}

void BreakOut::CreateControls(GameController &controller)
{
    ButtonAction escapeKeyAction;
    escapeKeyAction.Key = GameController::Cancel();
    escapeKeyAction.Action = [this](uint32_t dt, InputState state)
    {
        if (GameController::IsPressed(state))
        {
            if (mGameState == IN_GAME_TITLE)
            {
                App::Singleton().PopScene();
            }
        }
    };

    ButtonAction spaceKeyAction;
    spaceKeyAction.Key = GameController::Action();
    spaceKeyAction.Action = [this](uint32_t dt, InputState state)
    {
        if (mGameState == IN_SERVE)
        {

            if (GameController::IsPressed(state))
            {
                mGameState = IN_PLAY;
                if (mPaddle.IsMovingLeft())
                {
                    mBall.SetVelocity(Vec2D(-INITIAL_BALL_SPEED, -INITIAL_BALL_SPEED));
                }
                else
                {
                    mBall.SetVelocity(Vec2D(INITIAL_BALL_SPEED, -INITIAL_BALL_SPEED));
                }
            }
        }
        else if (mGameState == IN_GAME_TITLE)
        {
            if (GameController::IsPressed(state))
            {
                ResetGame();
            }
        }
    };

    ButtonAction LeftKeyAction;
    LeftKeyAction.Key = GameController::Left();
    LeftKeyAction.Action = [this](uint32_t dt, InputState state)
    {
        if (mGameState == IN_PLAY || mGameState == IN_SERVE)
        {
            if (GameController::IsPressed(state))
            {
                mPaddle.SetMovementDirection(PaddleDirection::LEFT_MOVE);
            }
            else
            {
                mPaddle.UnsetMovementDirection(PaddleDirection::LEFT_MOVE);
            }
        }
    };

    ButtonAction RightKeyAction;
    RightKeyAction.Key = GameController::Right();
    RightKeyAction.Action = [this](uint32_t dt, InputState state)
    {
        if (mGameState == IN_PLAY || mGameState == IN_SERVE)
        {
            if (GameController::IsPressed(state))
            {
                mPaddle.SetMovementDirection(PaddleDirection::RIGHT_MOVE);
            }
            else
            {
                mPaddle.UnsetMovementDirection(PaddleDirection::RIGHT_MOVE);
            }
        }
    };
    controller.AddInputActionForKey(escapeKeyAction);
    controller.AddInputActionForKey(spaceKeyAction);
    controller.AddInputActionForKey(LeftKeyAction);
    controller.AddInputActionForKey(RightKeyAction);
}
