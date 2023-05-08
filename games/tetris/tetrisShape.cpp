#include "tetrisShape.hpp"

void TetrisShape::Init(ShapeType shape, int blockSize, int startX, int startY)
{
    mShapeType = shape;
    mSize = blockSize;
    if (shape == LINE_SHAPE)
    {
        CreateLine(startX, startY);
    }
    if (shape == SQUARE_SHAPE)
    {
        CreateSquare(startX, startY);
    }
}

void TetrisShape::Draw(Screen &screen)
{
    for (auto &block : mBlocks)
    {
        block.Draw(screen);
    }
}

void TetrisShape::Update(uint32_t dt)
{
    for (auto &block : mBlocks)
    {
        block.Update(dt);
    }
}

void TetrisShape::MoveLeft()
{
    Vec2D offset(-mSize, 0);
    for (auto &block : mBlocks)
    {
        block.MoveBy(offset);
    }
}

void TetrisShape::MoveRight()
{
    Vec2D offset(mSize, 0);
    for (auto &block : mBlocks)
    {
        block.MoveBy(offset);
    }
}

void TetrisShape::Rotate()
{
    if (mShapeType == SQUARE_SHAPE)
    {
        return;
    }
    Vec2D blockCenter;
    if (mShapeType == T_SHAPE)
    {
        blockCenter = mBlocks[1].GetAARectangle().GetCenterPoint();
    }
    else
    {
        blockCenter = mBlocks[2].GetAARectangle().GetCenterPoint();
    }

    for (int i = 0; i < mBlocks.size(); i++)
    {
        if (i == 2)
        {
            continue;
        }

        mBlocks[i].Rotate(blockCenter);
    }
}

void TetrisShape::CreateLine(int startX, int startY)
{
    AARectangle rect(Vec2D(startX, startY), Vec2D(startX + mSize, startY + mSize));
    for (int i = 0; i < 4; ++i)
    {
        mBlocks.push_back(TetrisBlock(rect, Color::Blue(), Color::Cyan()));
        rect.MoveBy(Vec2D(mSize, 0));
    }
}

void TetrisShape::CreateSquare(int startX, int startY)
{
    AARectangle rect(Vec2D(startX, startY), Vec2D(startX + mSize, startY + mSize));
    for (int i = 0; i < 4; ++i)
    {
        mBlocks.push_back(TetrisBlock(rect, Color::Blue(), Color::Cyan()));
        if (i % 2 == 0)
        {
            rect.MoveBy(Vec2D(mSize, 0));
        }
        else
        {
            rect.MoveBy(Vec2D(-mSize, mSize));
        }
    }
}
void TetrisShape::CreateT(int startX, int startY)
{
}
void TetrisShape::CreateJ(int startX, int startY)
{
}
void TetrisShape::CreateL(int startX, int startY)
{
}
void TetrisShape::CreateS(int startX, int startY)
{
}
void TetrisShape::CreateZ(int startX, int startY)
{
}