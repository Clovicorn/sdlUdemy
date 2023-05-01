#pragma once

#include <stdint.h>
#include "excluder.hpp"
#include "boundaryEdge.hpp"
#include "../../graphics/screen.hpp"
#include "../../utils/utils.hpp"

enum PaddleDirection
{
    LEFT_MOVE = 1 << 0,
    RIGHT_MOVE = 1 << 1
};

class Paddle : public Excluder
{
public:
    static const int PADDLE_WIDTH = 50;
    static const int PADDLE_HEIGHT = 10;

    void Init(AARectangle &rect);
    void Update(uint32_t dt);
    void Draw(Screen &screen);

    inline void SetMovementDirection(PaddleDirection dir) { mDirection |= dir; }
    inline void UnsetMovementDirection(PaddleDirection dir) { mDirection &= ~dir; }
    inline void StopMovement() { mDirection = 0; }
    inline bool IsMovingLeft() { return mDirection == PaddleDirection::LEFT_MOVE; }
    inline bool IsMovingRight() { return mDirection == PaddleDirection::RIGHT_MOVE; }
    inline void SetScreenWidth(int width) { mScreenWidth = width; }
    inline void SetScreenHeight(int height) { mScreenHeight = height; }

private:
    int mScreenWidth = 0;
    int mScreenHeight = 0;
    uint32_t mDirection = 0;
    const float VELOCITY = 100.0f;
};