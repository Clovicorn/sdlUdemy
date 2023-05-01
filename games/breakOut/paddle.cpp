#include "paddle.hpp"

void Paddle::Init(AARectangle &rect)
{
    Excluder::Init(rect);
}

void Paddle::Update(uint32_t dt)
{

    if (mDirection != 0)
    {
        float dtToSeconds = MillisecondsToSeconds(dt);
        Vec2D dir = mDirection == PaddleDirection::LEFT_MOVE ? LEFT_DIR : RIGHT_DIR;
        if (mDirection == PaddleDirection::LEFT_MOVE + PaddleDirection::RIGHT_MOVE)
        {
            dir = Vec2D::Zero;
        }
        Vec2D dX = dir * VELOCITY * dtToSeconds;

        MoveBY(dX);
    }
    switch (mDirection)
    {
    case PaddleDirection::LEFT_MOVE:
    {
        if (GetTopLeft().GetX() < 0)
        {
            MoveTo(Vec2D(0, GetTopLeft().GetY()));
        }
    }
    break;
    case PaddleDirection::RIGHT_MOVE:
    {
        if (GetBottomRight().GetX() > mScreenWidth)
        {
            MoveTo(Vec2D(mScreenWidth - Paddle::PADDLE_WIDTH, GetTopLeft().GetY()));
        }
    }
    break;
    }
}

void Paddle::Draw(Screen &screen)
{
    AARectangle rect = GetAARectangle();
    screen.Draw(rect, Color::Blue(), true, Color::Blue());
}
