#ifndef ASTEROIDS_ROCK_H
#define ASTEROIDS_ROCK_H

#include "../../graphics/screen.hpp"
#include "../../graphics/spriteSheet.hpp"
#include "../../shapes/circle.hpp"
#include "../../utils/vec2d.hpp"

enum RockSize
{
    SMALL_ROCK = 22,
    MEDIUM_ROCK = 33,
    LARGE_ROCK = 51
};

class Rock
{
public:
    Rock();
    void Init(RockSize rockSize, const SpriteSheet &spriteSheet);
    void Draw(Screen &screen);
    void Update(uint32_t dt);
    bool CheckForCollision(const Circle &circle);
    void UpdateSize();
    void SetStartLocation(const Vec2D &pos);
    const inline RockSize GetRockSize() { return mSize; }

private:
    void SetVelocity();
    void SetRockSpriteName();
    void SetAngle();
    void CheckBoundaryCollision();

    const std::string mLargeRock = "big_rock";
    const std::string mMediumRock = "medium_rock";
    const std::string mSmallRock = "small_rock";
    const float mBaseVelocity = 0.10f;
    const float mBaseAngle = 0.01745f;

    float mAngle;
    Circle mCircle;
    float mRotationSpeed;

    Vec2D mVelocity;
    RockSize mSize;

    bool mIsDestroyed;
    bool mShouldCheckBoundary;
    SpriteSheet mSpriteSheet;
    DrawTransform mTransform;

    std::string mCurRockName;
};

#endif /* ASTEROIDS_ROCK_H */