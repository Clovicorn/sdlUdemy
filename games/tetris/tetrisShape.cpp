#include "tetrisShape.hpp"

void TetrisShape::Init(ShapeType shape, int blockSize, int startX, int startY)
{
    mShapeType = shape;
    mSize = blockSize;
    if (mBlocks.size() > 0)
    {
        mBlocks.clear();
    }
    switch (shape)
    {
    case LINE_SHAPE:
        CreateLine(startX, startY);
        break;
    case SQUARE_SHAPE:
        CreateSquare(startX, startY);
        break;
    case T_SHAPE:
        CreateT(startX, startY);
        break;
    case J_SHAPE:
        CreateJ(startX, startY);
        break;
    case L_SHAPE:
        CreateL(startX, startY);
        break;
    case S_SHAPE:
        CreateS(startX, startY);
        break;
    case Z_SHAPE:
        CreateZ(startX, startY);
        break;
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
    Vec2D offset(-mSize - 1, 0);
    for (auto &block : mBlocks)
    {
        block.MoveBy(offset);
    }
}

void TetrisShape::MoveRight()
{
    Vec2D offset(mSize + 1, 0);
    for (auto &block : mBlocks)
    {
        block.MoveBy(offset);
    }
}

void TetrisShape::MoveBy(Vec2D &distance)
{
    for (auto &block : mBlocks)
    {
        block.MoveBy(distance);
    }
}

void TetrisShape::Rotate()
{
    if (mShapeType == SQUARE_SHAPE)
    {
        return;
    }
    Vec2D blockCenter;
    int rotationBlock = 0;
    if (mShapeType == T_SHAPE)
    {
        blockCenter = mBlocks[1].GetAARectangle().GetCenterPoint();
        rotationBlock = 1;
    }
    else
    {
        blockCenter = mBlocks[2].GetAARectangle().GetCenterPoint();
        rotationBlock = 2;
    }

    for (int i = 0; i < mBlocks.size(); i++)
    {
        if (i == rotationBlock)
        {
            continue;
        }
        mBlocks[i].Rotate(blockCenter);
    }
}

void TetrisShape::CreateLine(int startX, int startY)
{
    AARectangle rect(Vec2D(startX, startY), Vec2D(startX + mSize - 1, startY + mSize - 1));
    for (int i = 0; i < 4; ++i)
    {
        mBlocks.push_back(TetrisBlock(rect, Color::Cyan(), Color::Blue()));
        rect.MoveBy(Vec2D(mSize + 1, 0));
    }
}

void TetrisShape::CreateSquare(int startX, int startY)
{
    AARectangle rect(Vec2D(startX, startY), Vec2D(startX + mSize - 1, startY + mSize - 1));
    for (int i = 0; i < 4; ++i)
    {
        mBlocks.push_back(TetrisBlock(rect, Color::Cyan(), Color::Green()));
        if (i % 2 == 0)
        {
            rect.MoveBy(Vec2D(mSize + 1, 0));
        }
        else
        {
            rect.MoveTo(Vec2D(startX, startY + mSize + 1));
        }
    }
}
void TetrisShape::CreateT(int startX, int startY)
{
    AARectangle rect(Vec2D(startX, startY), Vec2D(startX + mSize - 1, startY + mSize - 1));
    for (int i = 0; i < 3; ++i)
    {
        mBlocks.push_back(TetrisBlock(rect, Color::Cyan(), Color::Blue()));
        if (i != 2)
        {
            rect.MoveBy(Vec2D(mSize + 1, 0));
        }
    }
    rect.MoveBy(Vec2D(-mSize - 1, mSize + 1));
    mBlocks.push_back(TetrisBlock(rect, Color::Cyan(), Color::Blue()));
}
void TetrisShape::CreateJ(int startX, int startY)
{
    AARectangle rect(Vec2D(startX, startY), Vec2D(startX + mSize - 1, startY + mSize - 1));
    for (int i = 0; i < 3; ++i)
    {
        mBlocks.push_back(TetrisBlock(rect, Color::Cyan(), Color::Blue()));
        if (i != 2)
        {
            rect.MoveBy(Vec2D(mSize + 1, 0));
        }
    }
    rect.MoveBy(Vec2D(0, mSize + 1));
    mBlocks.push_back(TetrisBlock(rect, Color::Cyan(), Color::Blue()));
}
void TetrisShape::CreateL(int startX, int startY)
{
    AARectangle rect(Vec2D(startX, startY), Vec2D(startX + mSize - 1, startY + mSize - 1));
    for (int i = 0; i < 3; ++i)
    {
        mBlocks.push_back(TetrisBlock(rect, Color::Cyan(), Color::Blue()));
        if (i != 2)
        {
            rect.MoveBy(Vec2D(mSize + 1, 0));
        }
    }

    rect.MoveTo(Vec2D(startX, startY + mSize + 1));
    mBlocks.push_back(TetrisBlock(rect, Color::Cyan(), Color::Blue()));
}
void TetrisShape::CreateS(int startX, int startY)
{
    AARectangle rect(Vec2D(startX, startY), Vec2D(startX + mSize - 1, startY + mSize - 1));
    mBlocks.push_back(TetrisBlock(rect, Color::Cyan(), Color::Blue()));
    rect.MoveBy(Vec2D(mSize + 1, 0));
    mBlocks.push_back(TetrisBlock(rect, Color::Cyan(), Color::Blue()));
    rect.MoveTo(Vec2D(startX, startY + mSize + 1));
    mBlocks.push_back(TetrisBlock(rect, Color::Cyan(), Color::Blue()));
    rect.MoveBy(Vec2D(-mSize - 1, 0));
    mBlocks.push_back(TetrisBlock(rect, Color::Cyan(), Color::Blue()));
    MoveRight();
}
void TetrisShape::CreateZ(int startX, int startY)
{
    AARectangle rect(Vec2D(startX, startY), Vec2D(startX + mSize - 1, startY + mSize - 1));
    mBlocks.push_back(TetrisBlock(rect, Color::Cyan(), Color::Blue()));
    rect.MoveBy(Vec2D(mSize + 1, 0));
    mBlocks.push_back(TetrisBlock(rect, Color::Cyan(), Color::Blue()));
    rect.MoveBy(Vec2D(0, mSize + 1));
    mBlocks.push_back(TetrisBlock(rect, Color::Cyan(), Color::Blue()));
    rect.MoveBy(Vec2D(mSize + 1, 0));
    mBlocks.push_back(TetrisBlock(rect, Color::Cyan(), Color::Blue()));
}

int TetrisShape::GetWidth()
{
    int minX = mBlocks[0].GetAARectangle().GetTopLeft().GetX();
    int maxX = mBlocks[0].GetAARectangle().GetBottomRight().GetX();
    for (int i = 1; i < mBlocks.size(); i++)
    {
        if (mBlocks[i].GetAARectangle().GetTopLeft().GetX() < minX)
        {
            minX = mBlocks[i].GetAARectangle().GetTopLeft().GetX();
        }
        if (mBlocks[i].GetAARectangle().GetBottomRight().GetX() > maxX)
        {
            maxX = mBlocks[i].GetAARectangle().GetBottomRight().GetX();
        }
    }
    return maxX - minX;
}

int TetrisShape::GetHeight()
{
    int minY = mBlocks[0].GetAARectangle().GetTopLeft().GetY();
    int maxY = mBlocks[0].GetAARectangle().GetBottomRight().GetY();
    for (int i = 1; i < mBlocks.size(); i++)
    {
        if (mBlocks[i].GetAARectangle().GetTopLeft().GetY() < minY)
        {
            minY = mBlocks[i].GetAARectangle().GetTopLeft().GetY();
        }
        if (mBlocks[i].GetAARectangle().GetBottomRight().GetY() > maxY)
        {
            maxY = mBlocks[i].GetAARectangle().GetBottomRight().GetY();
        }
    }
    return maxY - minY;
}