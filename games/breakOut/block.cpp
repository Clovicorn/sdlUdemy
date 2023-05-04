#include "block.hpp"

void Block::Init(const AARectangle &rect, int hp, const Color &outline, const Color &fill)
{
    Excluder::Init(rect);
    mHP = hp;
    mOutline = outline;
    mFill = fill;
}

void Block::Draw(Screen &screen)
{
    AARectangle rect = GetAARectangle();
    screen.Draw(rect, mOutline, true, mFill);
}

void Block::Bounce(Ball &ball, const BoundaryEdge &edge)
{
    ball.Bounce(edge);
}

void Block::ReduceHP()
{
    if (mHP > 0)
    {
        --mHP;
    }
}