#include "breakOut.hpp"

void BreakOut::Init(GameController &controller)
{
    mScreenWidth = App::Singleton().Width();
    mScreenHeight = App::Singleton().Height();
    ResetGame();
    mBall.SetRadius(3.0f);
    controller.ClearAll();
    ButtonAction LeftKeyAction;
    LeftKeyAction.Key = GameController::Left();
    LeftKeyAction.Action = [this](uint32_t dt, InputState state)
    {
        if (GameController::IsPressed(state))
        {
            mPaddle.SetMovementDirection(PaddleDirection::LEFT_MOVE);
        }
        else
        {
            mPaddle.UnsetMovementDirection(PaddleDirection::LEFT_MOVE);
        }
    };

    ButtonAction RightKeyAction;
    RightKeyAction.Key = GameController::Right();
    RightKeyAction.Action = [this](uint32_t dt, InputState state)
    {
        if (GameController::IsPressed(state))
        {
            mPaddle.SetMovementDirection(PaddleDirection::RIGHT_MOVE);
        }
        else
        {
            mPaddle.UnsetMovementDirection(PaddleDirection::RIGHT_MOVE);
        }
    };
    controller.AddInputActionForKey(LeftKeyAction);
    controller.AddInputActionForKey(RightKeyAction);
}

void BreakOut::Update(uint32_t dt)
{
    mBall.Update(dt);
    mPaddle.Update(dt, mBall);

    bool didBounce = mPaddle.Bounce(mBall);
    if (!didBounce)
    {
        BoundaryEdge edge;
        if (mLevelBoundary.HasCollided(mBall, edge))
        {
            mBall.Bounce(edge);
        }
    }
}

void BreakOut::Draw(Screen &screen)
{
    mPaddle.Draw(screen);
    mBall.Draw(screen);
    AARectangle boundary = mLevelBoundary.GetRectangle();
    screen.Draw(boundary, Color::White());
}

std::string BreakOut::GetName()
{
    std::string name = "Break Out";
    return name;
}

void BreakOut::ResetGame()
{
    mLevelBoundary = {AARectangle(Vec2D::Zero, mScreenWidth, mScreenHeight)};
    AARectangle rect(Vec2D(mScreenWidth / 2 - Paddle::PADDLE_WIDTH / 2, mScreenHeight - 4 * Paddle::PADDLE_HEIGHT), Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT);

    mPaddle.Init(rect, mScreenWidth, mScreenHeight);
    mBall.MoveTo(Vec2D(mScreenWidth / 2, mScreenHeight / 2));
    mBall.SetVelocity(Vec2D(100, -100));
}