#include "rock.hpp"
#include "../../app/app.hpp"

#include <SDL2/SDL.h>
#include <cstdlib>

Rock::Rock() : mSize(RockSize::LARGE_ROCK), mRotationSpeed(0.0f), mVelocity(Vec2D::Zero), mIsDestroyed(false), mAngle(0.0f), mCurRockName(""), mShouldCheckBoundary(true)
{
}

void Rock::Init(RockSize rockSize, const SpriteSheet &spriteSheet)
{
    mSpriteSheet = spriteSheet;
    mCircle.SetRadius(rockSize / 2.0f);
    mSize = rockSize;
    mCircle.MoveTo(Vec2D(150, 100));
    SetVelocity();
    SetAngle();
    SetRockSpriteName();
}

void Rock::Draw(Screen &screen)
{
    float x = mCircle.GetCenterPoint().GetX() - mCircle.GetRadius();
    float y = mCircle.GetCenterPoint().GetY() - mCircle.GetRadius();

    std::cout << mTransform.angle << std::endl;
    screen.Draw(mSpriteSheet, mCurRockName, Vec2D(x, y), Color::White(), mTransform);
}

void Rock::Update(uint32_t dt)
{
    mCircle.MoveBy(mVelocity);
    if (mShouldCheckBoundary)
    {
        CheckBoundaryCollision();
    }

    mTransform.angle += mAngle;

    if (mTransform.angle <= -(TWO_PI))
    {
        mTransform.angle += (TWO_PI);
    }
    else if (mTransform.angle >= (TWO_PI))
    {
        mTransform.angle -= TWO_PI;
    }
}

void Rock::CheckBoundaryCollision()
{
    uint32_t screenWidth = App::Singleton().Width();
    uint32_t screenHeight = App::Singleton().Height();
    if (mCircle.GetCenterPoint().GetY() - mCircle.GetRadius() < 0)
    {
        mCircle.MoveTo(Vec2D(mCircle.GetCenterPoint().GetX(), mCircle.GetRadius()));
        mVelocity.SetY(-(mVelocity.GetY()));
    }
    if (mCircle.GetCenterPoint().GetX() + mCircle.GetRadius() > screenWidth)
    {
        mCircle.MoveTo(Vec2D(screenWidth - mCircle.GetRadius(), mCircle.GetCenterPoint().GetY()));
        mVelocity.SetX(-(mVelocity.GetX()));
    }
    if (mCircle.GetCenterPoint().GetY() + mCircle.GetRadius() > screenHeight)
    {
        mCircle.MoveTo(Vec2D(mCircle.GetCenterPoint().GetX(), screenHeight - mCircle.GetRadius()));
        mVelocity.SetY(-(mVelocity.GetY()));
    }
    if (mCircle.GetCenterPoint().GetX() - mCircle.GetRadius() < 0)
    {
        mCircle.MoveTo(Vec2D(mCircle.GetRadius(), mCircle.GetCenterPoint().GetY()));
        mVelocity.SetX(-(mVelocity.GetX()));
    }
}

bool Rock::CheckForCollision(const Circle &circle)
{
    if (mCircle.Intersects(circle))
    {
        return true;
    }
    return false;
}

void Rock::UpdateSize()
{
    if (mSize == LARGE_ROCK)
    {
        mSize = MEDIUM_ROCK;
        mCircle.SetRadius(MEDIUM_ROCK / 2.0f);
    }
    else if (mSize == MEDIUM_ROCK)
    {
        mSize = SMALL_ROCK;
        mCircle.SetRadius(SMALL_ROCK / 2.0f);
    }
    else
    {
        mIsDestroyed = true;
    }
}

void Rock::SetVelocity()
{
    uint32_t ticks = SDL_GetTicks();
    std::srand(ticks);
    uint32_t velocityMultiplier = (std::rand() % 10) + 1;
    if (ticks >= RAND_MAX / 2)
    {
        mVelocity.SetX(-(mBaseVelocity * velocityMultiplier));
    }
    else
    {
        mVelocity.SetX(mBaseVelocity * velocityMultiplier);
    }

    ticks = SDL_GetTicks();
    std::srand(ticks);
    velocityMultiplier = (std::rand() % 10) + 1;
    if (ticks <= RAND_MAX)
    {
        mVelocity.SetY(mBaseVelocity * velocityMultiplier);
    }
    else
    {
        mVelocity.SetY(-(mBaseVelocity * velocityMultiplier));
    }
}

void Rock::SetAngle()
{
    uint32_t ticks = SDL_GetTicks();
    std::srand(ticks);
    uint32_t angleMultiplier = (std::rand() % 5) + 1;
    mAngle = mBaseAngle * angleMultiplier;

    if (ticks >= RAND_MAX / 2.0f)
    {
        mAngle = -(mAngle);
    }
}

void Rock::SetRockSpriteName()
{
    if (mSize == LARGE_ROCK)
    {
        mCurRockName = "big_rock";
    }
    else if (mSize == MEDIUM_ROCK)
    {
        mCurRockName = "medium_rock";
    }
    else
    {
        mCurRockName = "small_rock";
    }
}

void Rock::SetStartLocation(const Vec2D &pos)
{
    mCircle.MoveTo(pos);
}