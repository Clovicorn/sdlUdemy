#include "tetrisBlock.hpp"
#include "../../graphics/screen.hpp"

TetrisBlock::TetrisBlock() : mRect(Vec2D::Zero, 0, 0), mOutline(Color::Black()), mFill(Color::Black())
{
}

TetrisBlock::TetrisBlock(AARectangle &rect, const Color &outline, const Color &fill)
{
    mRect = rect;
    mOutline = outline;
    mFill = fill;
    mSize = rect.GetWidth();
}

void TetrisBlock::Draw(Screen &screen)
{
    screen.Draw(mRect, mOutline, true, mFill);
}

void TetrisBlock::Update(uint32_t dt)
{
    mRect.MoveBy(Vec2D(0, mSize + 1));
}

void TetrisBlock::MoveBy(Vec2D &offset)
{
    mRect.MoveBy(offset);
}

void TetrisBlock::Rotate(const Vec2D &aroundPoint)
{
    Vec2D topLeft(aroundPoint.GetX() - (mSize / 2.0f), aroundPoint.GetY() - (mSize / 2.0f));
    Vec2D unitTopLeft(mRect.GetTopLeft().GetX() - topLeft.GetX(), mRect.GetTopLeft().GetY() - topLeft.GetY());

    mRect.SetTopLeft(Vec2D(unitTopLeft.GetY(), -unitTopLeft.GetX()));
    mRect.SetTopLeft(Vec2D(mRect.GetTopLeft().GetX() + topLeft.GetX(), mRect.GetTopLeft().GetY() + topLeft.GetY()));
    mRect.SetBottomRight(Vec2D(mRect.GetTopLeft().GetX() + mSize - 1, mRect.GetTopLeft().GetY() + mSize - 1));
}

bool TetrisBlock::CheckForCollision(const AARectangle &rect, BlockSide side)
{
    switch (side)
    {
    case RIGHT_SIDE:
    {
        if (mRect.GetBottomRight().GetX() > rect.GetTopLeft().GetX())
        {
            int distance = mRect.GetCenterPoint().Distance(rect.GetCenterPoint());
            if (distance < mSize)
            {
                return true;
            }
        }
    }
    break;

    case BOTTOM_SIDE:
    {
        if ((mRect.GetBottomRight().GetY() + mSize) >= rect.GetTopLeft().GetY())
        {
            return true;
        }
    }
    break;

    case LEFT_SIDE:
    {
        if (mRect.GetTopLeft().GetX() < rect.GetBottomRight().GetX())
        {
            int distance = mRect.GetCenterPoint().Distance(rect.GetCenterPoint());
            if (distance < mSize)
            {
                return true;
            }
        }
    }
    break;
    }

    return false;
}