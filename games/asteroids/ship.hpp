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

private:
    const float mAngle = 0.174533f;
    DrawTransform mTransform;
    SpriteSheet mSpriteSheet;
    AnimationPlayer mShipAnimPlayer;
    Circle mCircle;
};

#endif /* ASTEROIDS_SHIP_H */