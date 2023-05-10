#pragma once

#include <vector>

#include "../../shapes/aaRectangle.hpp"
#include "tetrisBlock.hpp"

enum ShapeType
{
    LINE_SHAPE,
    SQUARE_SHAPE,
    T_SHAPE,
    L_SHAPE,
    J_SHAPE,
    S_SHAPE,
    Z_SHAPE,
    NUM_SHAPES
};

class TetrisShape
{
public:
    void Init(ShapeType shape, int blockSize, int startX, int startY);
    void Draw(Screen &screen);
    void Update(uint32_t dt);
    void MoveLeft();
    void MoveRight();
    void Rotate();
    void MoveBy(Vec2D &distance);
    inline void SetCanMove(bool move) { mCanMove = move; }
    inline bool GetCanMove() { return mCanMove; }
    inline std::vector<TetrisBlock> &GetBlocks() { return mBlocks; }
    int GetWidth();
    int GetHeight();

private:
    void CreateLine(int startX, int startY);
    void CreateSquare(int startX, int startY);
    void CreateT(int startX, int startY);
    void CreateJ(int startX, int startY);
    void CreateL(int startX, int startY);
    void CreateS(int startX, int startY);
    void CreateZ(int startX, int startY);
    // End TODO
    bool mCanMove = true;
    ShapeType mShapeType;
    int mSize = 0;
    std::vector<TetrisBlock> mBlocks;
};