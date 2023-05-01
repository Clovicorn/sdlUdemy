#include "breakOut.hpp"

void BreakOut::Init(GameController &controller)
{
    mScreenWidth = App::Singleton().Width();
    mScreenHeight = App::Singleton().Height();
    mPaddle.SetScreenWidth(mScreenWidth);
    mPaddle.SetScreenHeight(mScreenHeight);
    ResetGame();
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
    mPaddle.Update(dt);
}

void BreakOut::Draw(Screen &screen)
{
    mPaddle.Draw(screen);
}

std::string BreakOut::GetName()
{
    std::string name = "Break Out";
    return name;
}

void BreakOut::ResetGame()
{
    AARectangle rect(Vec2D(mScreenWidth / 2 - Paddle::PADDLE_WIDTH / 2, mScreenHeight - 4 * Paddle::PADDLE_HEIGHT), Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT);
    mPaddle.Init(rect);
}