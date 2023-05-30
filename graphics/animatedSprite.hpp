#ifndef GRAPHICS_ANIMATED_SPRITE_H
#define GRAPHICS_ANIMATED_SPRITE_H

#include "animationPlayer.hpp"
#include "color.hpp"
#include "../utils/vec2d.hpp"
#include "../graphics/screen.hpp"

class AARectangle;
class SpriteSheet;

class AnimatedSprite
{
public:
    AnimatedSprite();
    void Init(const std::string &animationPath, const SpriteSheet &spriteSheet, const Color &color = Color::White());
    void Update(uint32_t dt);
    void Draw(Screen &screen, const DrawTransform &transform = DrawTransform());

    void SetAnimation(const std::string &animationName, bool looped);
    Vec2D Size() const;
    void Stop();
    const AARectangle GetBoundingBox() const;

    inline Vec2D Position() const { return mPosition; }
    inline void SetPosition(const Vec2D &position) { mPosition = position; }
    inline void MoveBy(const Vec2D &delta) { mPosition += delta; }
    inline bool IsFinishedPlaying() { return mAnimationPlayer.IsFinishedPlaying(); }
    inline const Color &GetColor() const { return mColor; }
    const SpriteSheet *GetSpriteSheet() const { return mpSpriteSheet; }
    const AnimationFrame &GetCurrentFrame();

private:
    const SpriteSheet *mpSpriteSheet;
    AnimationPlayer mAnimationPlayer;
    Vec2D mPosition;
    Color mColor;
};
#endif /* GRAPHICS_ANIMATED_SPRITE_H */