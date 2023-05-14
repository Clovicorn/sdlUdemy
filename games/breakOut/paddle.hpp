#ifndef PADDLE_H
#define PADDLE_H

#include <stdint.h>
#include "excluder.hpp"

class Screen;
class BoundaryEdge;
class Ball;

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

    void Init(AARectangle &rect, int screenWidth, int screenHeight);
    void Update(uint32_t dt, Ball &ball);
    void Draw(Screen &screen);
    bool Bounce(Ball &ball);

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
    const float CORNER_EDGE_AMOUNT = 0.03f;
};

#endif /* PADDLE_H */