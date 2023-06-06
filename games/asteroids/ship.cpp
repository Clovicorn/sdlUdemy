#include "ship.hpp"
#include "../../graphics/screen.hpp"
#include "../../app/app.hpp"
#include "../../utils/utils.hpp"
#include <cmath>

Ship::Ship() : mCurSpeed(Vec2D::Zero), mRotationChanged(false)
{
}

bool Ship::Init(const std::string &animationFilePath, const SpriteSheet &spriteSheet)
{
    bool didLoad = false;
    mCircle.SetRadius(21.0f / 2.0f);
    mCircle.MoveTo(Vec2D(App::Singleton().Width() / 2, App::Singleton().Height() / 2));
    mSpriteSheet = spriteSheet;
    didLoad = mShipAnimPlayer.Init(animationFilePath);
    if (!didLoad)
    {
        return false;
    }
    didLoad = mShipAnimPlayer.Play("ship", true);
    if (!didLoad)
    {
        std::cout << "failed with thrusters animation" << std::endl;
    }

    didLoad = mThrusterAnimPlayer.Init(animationFilePath);
    if (!didLoad)
    {
        return false;
    }
    didLoad = mThrusterAnimPlayer.Play("thrusters", true);
    if (!didLoad)
    {
        std::cout << "failed with thrusters animation" << std::endl;
    }
    mShipTransform.rotate = true;
    mShipTransform.wrapWorld = true;
    return true;
}

void Ship::Draw(Screen &screen)
{

    Vec2D circleCenter = mCircle.GetCenterPoint();

    AnimationFrame shipFrame = mShipAnimPlayer.GetCurrentAnimationFrame();
    Vec2D shipTopLeft = Vec2D(circleCenter.GetX() - shipFrame.size.GetX() / 2, circleCenter.GetY() - shipFrame.size.GetY() / 2);

    if (mShowThrusters)
    {
        Vec2D thrustersPos(shipTopLeft.GetX() + (shipFrame.size.GetX() / 4) + 1, circleCenter.GetY() + shipFrame.size.GetY() / 2);
        AnimationFrame thrustersFrame = mThrusterAnimPlayer.GetCurrentAnimationFrame();
        screen.Draw(mSpriteSheet, thrustersFrame.frame, thrustersPos, Color::White(), mShipTransform);
    }
    screen.Draw(mSpriteSheet, shipFrame.frame, shipTopLeft, Color::White(), mShipTransform);
}

void Ship::Update(uint32_t dt)
{
    mThrusterAnimPlayer.Update(dt);
    mCircle.MoveBy(mCurSpeed);
    mShipTransform.point = mCircle.GetCenterPoint();

    WrapWorld();
}

void Ship::MoveForward()
{
    // TODO Close but still not right because not not taking into account
    // we might be facing down and not having fullly rotated around a circle

    float angle = mShipTransform.angle - HALF_PI;

    if (angle < 0)
    {
        mCurSpeed = MoveFromNegAngle(angle);
    }
    else
    {
        mCurSpeed = MoveFromPosAngle(angle);
    }

    SetShowThrusters(true);
}

void Ship::RotateLeft()
{

    mShipTransform.angle -= mAngle;
    if (mShipTransform.angle <= -(TWO_PI) + HALF_PI)
    {
        mShipTransform.angle += TWO_PI;
    }
}

void Ship::RotateRight()
{
    mShipTransform.angle += mAngle;
    if (mShipTransform.angle >= TWO_PI - HALF_PI)
    {
        mShipTransform.angle -= TWO_PI;
    }
}

void Ship::WrapWorld()
{
    if (mCircle.GetCenterPoint().GetX() < 0)
    {
        mCircle.MoveTo(Vec2D(App::Singleton().Width() + mCircle.GetCenterPoint().GetX(), mCircle.GetCenterPoint().GetY()));
    }
    else if (mCircle.GetCenterPoint().GetX() > App::Singleton().Width())
    {
        int x = mCircle.GetCenterPoint().GetX() - App::Singleton().Width();
        mCircle.MoveTo(Vec2D(x, mCircle.GetCenterPoint().GetY()));
    }

    if (mCircle.GetCenterPoint().GetY() < 0)
    {
        mCircle.MoveTo(Vec2D(mCircle.GetCenterPoint().GetX(), App::Singleton().Height() + mCircle.GetCenterPoint().GetY()));
    }
    else if (mCircle.GetCenterPoint().GetY() > App::Singleton().Height())
    {
        int y = mCircle.GetCenterPoint().GetY() - App::Singleton().Height();
        mCircle.MoveTo(Vec2D(mCircle.GetCenterPoint().GetX(), y));
    }
}

Vec2D Ship::MoveFromNegAngle(float angle)
{
    float x = 0;
    float y = 0;
    if (IsEqual(angle, -(0.0f)) || IsEqual(angle, -(TWO_PI)))
    {
        x = mVelocity;
    }
    else if (IsEqual(angle, -(HALF_PI)))
    {
        y = -(mVelocity);
    }
    else if (IsEqual(angle, -(PI)))
    {
        x = -(mVelocity);
    }
    else if (IsEqual(angle, -(PI_3_4TH)))
    {
        y = mVelocity;
    }
    else if ((angle < -(0.0f) && angle > -(HALF_PI)))
    {
        x = mVelocity;
        y = -(mVelocity);
    }
    else if ((angle < -(HALF_PI) && angle > -(PI)))
    {
        x = -(mVelocity);
        y = -(mVelocity);
    }
    else if (angle < -(PI) && angle > -(PI_3_4TH))
    {
        x = -(mVelocity);
        y = mVelocity;
    }
    else if ((angle < -(PI_3_4TH) && angle > -(TWO_PI)))
    {
        x = mVelocity;
        y = mVelocity;
    }

    return Vec2D(x, y);
}

Vec2D Ship::MoveFromPosAngle(float angle)
{
    float x = 0;
    float y = 0;
    if (IsEqual(angle, 0))
    {
        x = mVelocity;
    }
    else if (IsEqual(angle, HALF_PI))
    {
        y = mVelocity;
    }
    else if (IsEqual(angle, PI))
    {
        x = -(mVelocity);
    }
    else if (IsEqual(angle, PI_3_4TH))
    {
        y = -(mVelocity);
    }
    else if ((angle > 0.0f && angle < HALF_PI))
    {
        x = mVelocity;
        y = mVelocity;
    }
    else if ((angle > HALF_PI && angle < PI))
    {
        x = -(mVelocity);
        y = mVelocity;
    }
    else if ((angle > PI && angle < PI_3_4TH))
    {
        x = -(mVelocity);
        y = -(mVelocity);
    }
    else if ((angle > PI_3_4TH && angle < TWO_PI))
    {
        x = mVelocity;
        y = -(mVelocity);
    }
    return Vec2D(x, y);
}

void Ship::ResetPosition()
{
    mCircle.MoveTo(Vec2D(App::Singleton().Width() / 2.0f, App::Singleton().Height() / 2.0f));
    mShipTransform.angle = 0.0f;
}