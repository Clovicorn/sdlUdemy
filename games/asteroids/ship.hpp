#ifndef ASTEROIDS_SHIP_H
#define ASTEROIDS_SHIP_H

#include "../../graphics/animationPlayer.hpp"
#include "../../graphics/spriteSheet.hpp"
#include "../../shapes/circle.hpp"
#include "../../graphics/screen.hpp"

class Ship
{
public:
    Ship();
    bool Init(const std::string &animationFilePath, const SpriteSheet &spriteSheet);
    void Draw(Screen &screen);
    void Update(uint32_t dt);
    void MoveForward();
    void RotateLeft();
    void RotateRight();
    inline void SetShowThrusters(bool state) { mShowThrusters = state; }
    inline const Circle &GetCircle() const { return mCircle; }
    void ResetPosition();

private:
    void WrapWorld();
    Vec2D MoveFromNegAngle(float angle);
    Vec2D MoveFromPosAngle(float angle);
    bool mRotationChanged;
    const float mAngle = 0.05235f;
    Vec2D mCurSpeed;
    const float mVelocity = 1.0f;
    DrawTransform mShipTransform;
    SpriteSheet mSpriteSheet;
    AnimationPlayer mShipAnimPlayer;
    bool mShowThrusters;
    AnimationPlayer mThrusterAnimPlayer;
    Circle mCircle;
};

#endif /* ASTEROIDS_SHIP_H */