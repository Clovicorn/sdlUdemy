#include "breakOut.hpp"

void BreakOut::Init(GameController &controller)
{
    mScreenWidth = App::Singleton().Width();
    mScreenHeight = App::Singleton().Height();
    ResetGame();
    mBall.SetRadius(3.0f);
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
    GetCurrentLevel().Update(dt, mBall);
    // This should update 3 times a Second!
    if (cleanup == 20)
    {
        cleanup = 0;
        if (GetCurrentLevel().IsLevelComplete())
        {
            NextLevel();
        }
    }
    else
    {
        cleanup++;
    }
}

void BreakOut::Draw(Screen &screen)
{
    mPaddle.Draw(screen);
    GetCurrentLevel().Draw(screen);
    mBall.Draw(screen);
    AARectangle boundary = mLevelBoundary.GetRectangle();
    screen.Draw(boundary, Color::White());
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
    mGameState = IN_SERVE;
    mLives = 3;
    mLevels = BreakOutLevel::LoadLevelsFromFile(App::GetBasePath() + "assets/BreakoutLevels.txt", mScreenWidth, mScreenHeight);
    mCurrentLevel = 0;
    mLevelBoundary = {AARectangle(Vec2D::Zero, mScreenWidth, mScreenHeight)};
    AARectangle rect(Vec2D(mScreenWidth / 2 - Paddle::PADDLE_WIDTH / 2, mScreenHeight - 4 * Paddle::PADDLE_HEIGHT), Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT);
    mLevels[mCurrentLevel].Init(mLevelBoundary.GetRectangle());
    mPaddle.Init(rect, mScreenWidth, mScreenHeight);
    mBall.MoveTo(Vec2D(mPaddle.GetTopLeft().GetX() + (mPaddle.GetAARectangle().GetWidth() / 2), mPaddle.GetTopLeft().GetY() - (mBall.GetRadius() * 2)));
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
        mGameState = IN_GAME_OVER;
        mPaddle.UnsetMovementDirection(PaddleDirection::LEFT_MOVE);
        mPaddle.UnsetMovementDirection(PaddleDirection::RIGHT_MOVE);
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
        else if (mGameState == IN_GAME_OVER)
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
    controller.AddInputActionForKey(spaceKeyAction);
    controller.AddInputActionForKey(LeftKeyAction);
    controller.AddInputActionForKey(RightKeyAction);
}