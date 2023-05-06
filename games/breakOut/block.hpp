#pragma once

#include <algorithm>

#include "ball.hpp"
#include "excluder.hpp"
#include "../../graphics/color.hpp"
#include "../../graphics/screen.hpp"

class Block : public Excluder
{
public:
    static const int UBREAKABLE = -1;
    void Init(const AARectangle &rect, int hp, const Color &outline, const Color &fill);
    void Draw(Screen &screen);
    void Bounce(Ball &ball, const BoundaryEdge &edge);
    void ReduceHP();

    inline int GetHP() { return mHP; }
    inline bool IsDestroyed() const { return mHP == 0; }
    inline const Color &GetOutlineColor() const { return mOutline; }
    inline const Color &GetFillColor() const { return mFill; }

private:
    Color mOutline;
    Color mFill;
    int mHP;
};