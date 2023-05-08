#pragma once

#include "../../graphics/screen.hpp"
#include "../../shapes/aaRectangle.hpp"
#include "../../graphics/color.hpp"

struct sidesForCollision
{
    bool topSide = false;
    bool rightSide = false;
    bool bottomSide = false;
    bool leftSide = false;
};
enum BlockSide
{
    TOP_SIDE = 0,
    RIGHT_SIDE,
    BOTTOM_SIDE,
    LEFT_SIDE
};

class TetrisBlock
{
public:
    TetrisBlock();
    TetrisBlock(AARectangle &rect, const Color &outline, const Color &fill);
    void Rotate(const Vec2D &aroundPoint);
    void Draw(Screen &screen);
    void Update(uint32_t dt);
    bool CheckForCollision();
    void MoveBy(Vec2D &offset);
    inline const AARectangle &GetAARectangle() { return mRect; }

private:
    unsigned int mSize;
    AARectangle mRect;
    Color mOutline;
    Color mFill;
};