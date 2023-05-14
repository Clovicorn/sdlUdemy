#ifndef TETRIS_BLOCK_H
#define TETRIS_BLOCK_H

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

class Screen;

class TetrisBlock
{
public:
    TetrisBlock();
    TetrisBlock(AARectangle &rect, const Color &outline, const Color &fill);
    void Rotate(const Vec2D &aroundPoint);
    void Draw(Screen &screen);
    void Update(uint32_t dt);
    bool CheckForCollision(const AARectangle &rect, BlockSide side);
    void MoveBy(Vec2D &offset);
    inline AARectangle &GetAARectangle() { return mRect; }
    inline bool GetCanMove() { return mCanMove; }
    inline void SetCanMove(bool move) { mCanMove = move; }
    inline bool GetShouldDraw() { return mShouldDraw; }
    inline void SetShouldDraw(bool draw) { mShouldDraw = draw; }
    inline const Color &GetOutlineColor() { return mOutline; }
    inline const Color &GetFillColor() { return mFill; }
    inline void SetOutlineColor(Color &color) { mOutline = color; }
    inline void SetFillColor(Color &color) { mFill = color; }

private:
    bool mCanMove = false;
    bool mShouldDraw = false;
    unsigned int mSize;
    AARectangle mRect;
    Color mOutline;
    Color mFill;
};

#endif /* TETRIS_BLOCK_H */