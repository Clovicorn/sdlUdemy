#pragma once

#include "../../shapes/aaRectangle.hpp"
#include "../../graphics/screen.hpp"

class Ball
{
public:
    Ball();
    Ball(const Vec2D &pos, float radius);

    void Update(uint32_t dt);
    void Draw(Screen &screen);

private:
    AARectangle mBBox;
    Vec2D mVelocity;
};
