#include "ship.hpp"
#include "../../graphics/screen.hpp"
#include "../../app/app.hpp"

Ship::Ship()
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
    mShipAnimPlayer.Play("ship", false);
    return true;
}

void Ship::Draw(Screen &screen)
{
    screen.Draw(mCircle, Color::Red(), false);
    Vec2D circleCenter = mCircle.GetCenterPoint();

    AnimationFrame frame = mShipAnimPlayer.GetCurrentAnimationFrame();
    Vec2D shipTopLeft = Vec2D(circleCenter.GetX() - frame.size.GetX() / 2, circleCenter.GetY() - frame.size.GetY() / 2);
    screen.Draw(mSpriteSheet, frame.frame, shipTopLeft, Color::White(), mTransform);
}

void Ship::Update(uint32_t dt)
{
    mShipAnimPlayer.Update(dt);
    mTransform.point = mCircle.GetCenterPoint();
}

void Ship::MoveForward()
{
}

void Ship::RotateLeft()
{
    mTransform.angle += -(mAngle);
    if (mTransform.angle <= 6.28319f)
    {
        mTransform.angle += 6.28319f;
    }
}

void Ship::RotateRight()
{
    mTransform.angle += mAngle;
    if (mTransform.angle >= 6.28319f)
    {
        mTransform.angle -= 6.28319f;
    }
}
