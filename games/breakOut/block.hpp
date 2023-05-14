#ifndef BLOCK_H
#define BLOCK_H

#include "excluder.hpp"
#include "../../graphics/color.hpp"

class Screen;
class AARectangle;
class Ball;

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

#endif /* BLOCK_H */