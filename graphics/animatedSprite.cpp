#include "animatedSprite.hpp"

#include "screen.hpp"
#include "spriteSheet.hpp"
#include "../shapes/aaRectangle.hpp"

AnimatedSprite::AnimatedSprite() : mPosition(Vec2D::Zero), mpSpriteSheet(nullptr)
{
}

void AnimatedSprite::Init(const std::string &animationPath, const SpriteSheet &spriteSheet, const Color &color)
{
    mAnimationPlayer.Init(animationPath);
    mpSpriteSheet = &spriteSheet;
    mColor = color;
}

void AnimatedSprite::Update(uint32_t dt)
{
    mAnimationPlayer.Update(dt);
}

void AnimatedSprite::Draw(Screen &screen)
{
    AnimationFrame frame = mAnimationPlayer.GetCurrentAnimationFrame();
    Color frameColor = frame.frameColor;
    if (!frame.frameColorSet)
    {
        frameColor = mColor;
    }
    screen.Draw(*mpSpriteSheet, frame.frame, mPosition + frame.offset, frameColor);
    if (frame.overlay.size() > 0)
    {
        screen.Draw(*mpSpriteSheet, frame.overlay, mPosition, frame.overlayColor);
    }
}

void AnimatedSprite::SetAnimation(const std::string &animationName, bool looped)
{
    mAnimationPlayer.Play(animationName, looped);
}

Vec2D AnimatedSprite::Size() const
{
    return mAnimationPlayer.GetCurrentAnimationFrame().size;
}

void AnimatedSprite::Stop()
{
    mAnimationPlayer.Stop();
}

const AARectangle AnimatedSprite::GetBoundingBox() const
{
    AARectangle bbox = {mPosition, static_cast<unsigned int>(Size().GetX()), static_cast<unsigned int>(Size().GetY())};
    return bbox;
}
